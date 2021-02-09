## **Background ( Image Structures)** 

![ ](/Users/seunghojang/Desktop/Note.png)

## **Image Reading And Pixel Access in Mat**

1. using 'at' : safety but most slow
2. using 'ptr' : Fster than 'at'
3. using 'data' : Fastest but unsafety
4. Iterator ( like STL)

### 1. using 'at' case.

``` c++
//<cv::Vec3b> Basic data structure 
for (int i = img.rows / 10 * 2; i < img.rows / 10 * 3; ++i){
  for (int j = 0; j < img.cols; ++j){
    
    //Vec3b means uchar 3ch
    unsigned char b = img.at< cv::Vec3b >(i, j)[0];
    unsigned char g = img.at< cv::Vec3b >(i, j)[1];
    unsigned char r = img.at< cv::Vec3b >(i, j)[2];
    
    //printf(%d %d %d \n, b, g, r);
    img.at<cv::Vec3b>(i, j)[0] = unsigned char(255 - b); //b
    img.at<cv::Vec3b>(i, j)[1] = unsigned char(255 - g); //g
    img.at<cv::Vec3b>(i, j)[2] = unsigned char(255 - r); //r
  }
}
```

### 2. using 'ptr' case.

```c++
for (int i = img.rows / 10 * 6; i < img.rows / 10 * 7; i++){
  // Get all i'th rows and recieve them using a ptr. 
  cv::Vec3b *ptr = img.ptr<cv::Vec3b>(i);
  
  for (int j = 0; j < img.cols; j++){
    // More prefered way.
    cv::Vec3b bgr = ptr[j];
    unsigned char b2 = (bgr[0]);
    unsigned char g2 = (bgr[1]);
    unsigned char r2 = (bgr[2]);
    
    //b, g, r also can be accessed or expressed in this way
    unsigned char b = (ptr[j][0]); // Access first channel.
    unsigned char g = (ptr[j][1]); // Access second channel.
    unsigned char r = (ptr[j][2]); // Access third channel.
    
    ptr[j] = cv::Vec3b( 255 - b2, 255 - g2, 255 - r2);
  }
}
```

### 3. using 'iterator' case (STL).

``` c++
cv::Matiterator_<cv::Vec3b> itd = img.begin<cv::Vec3b>(), itd_end = img.end<cv::Vec3b>();

//Flip all the bits. 
for(int i = 0; itd != itd_end; ++itd, ++i){
  cv::Vec3b bgr (*itd);
  
  (*itd)[0] = 255 - bgr[0];
  (*itd)[1] = 255 - bgr[1];
  (*itd)[2] = 255 - bgr[2];
  
}
```

### 4. using 'data' case.

``` c++
for (int i = img.rows /10 * 8; i < img.rows /10 * 9; i++){
  for (int j = 0; j < img.cols; j++){
    unsigned char r, g, b;
    b = img.data[i * img.step + j * img.elemSize() + 0];
    g = img.data[i * img.step + j * img.elemSize() + 1];
    r = img.data[i * img.step + j * img.elemSize() + 2];
    
    img.data[i * img.step + j * img.elemSize() + 0] = unsigned char(255 - b);
    img.data[i * img.setp + j * img.elemSize() + 1] = unsigned char(255 - g);
    img.data[i * img.step + j * img.elemSize() + 2] = unsigned char(255 - r);
  }
}
```

### **Homework**

### 1 . Access ptr, iterator, data for a rect ROI in image ( 90 % )

### 2.  Access ptr, iterator, data for a rect ROI in Video ( 100 % )



## Reference

* http://study.marearts.com/2016/06/opencv-pixel-access-at-ptr-data.html

* https://blog.naver.com/laonple/220770852625