## Point Processing - 2

What is the binary image?

- Not gray image
- Binary image refer to 2 colors, black and white

How to make binary image?

* This is very simple, but also very difficult!



---

Based on the threshold value, (Korean : 임계값)

* if pixel value larger than threshold, then 255
* less than threshold, then 0.

How to determine threshold ?

* Using Histogram. 

* `Sometimes, it is very hard to determine threshold with one value. then, use the adaptive threshold.`

* Binarization is also very important in LPR(License Plate Recognition)

Look at the adaptive binarization a new approach to license plate characters segmentation (IEEE 2012).

```c++
# C++ : doulbe threshold(inputArray src, OutputArray dst, double thresh, double maxval, int type)

int main(int, char){
    Mat img = imread("input.jpg");
    Mat gray, binary;
    cvtColor(img, gray, CV_RGB2GRAY);
    threshold(gray, binary, 128, 256, CV_THRESH_BINARY);
}
```

