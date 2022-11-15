## Also called, pixel processing

* Constant Operation
* Operation between frames(images)
* Other operation
  *  and, or, xor
  * Noise generation

 ## Constant Operation

### +, -, /, * operation by constant

* add 
  *  void add(inputArray src1, inputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);
  *  cuda::add..
* subtract
  * void subtract(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);
  * cuda::subtract
* absdiff
  * void absdiff(InputArray src1, InputArray src2, OutputArray dst);
  * Cuda::absdiff
* *, /
  * multiply, divide function. 
  * A = A * Scalar, B = B / Scalar

---

## Operation

```c++
// For cuda
#include "opencv2/cuda.hpp"
#include "opencv2/cudaarithm.hpp"

int main(int, char){
  
  Mat img = imread("input.img");
  imshow("input img", img);
  
  //Add Example
  // if the pixel value is larger than 255, then it's 255
 	Mat img_add, img_sub, img_mul, img_div;
  add(img, Scalar(200, 200, 200), img_add); // Values in between 0 and 255
  // or img_add = img + Scalar(200, 200, 200)
  
  //Add Example using cuda
  cuda::GpuMat gimg;
  cuda::GpuMat gout1, gout2;
 	//upload it to gpu
  gimg.upload(img);
  cuda::add(gimg, Scalar(200, 200, 200), gout1);
  //bring it into cpu world
  gout1.download(img_add);
  imshow("img_add", img_add);
  
  // Subtract Example 
  // if the pixel value is smaller than 0, then it's 0.
  subtract(img, Scalar(200, 200, 200), img_sub); // Values in between 0 and 255.
  // or img_sub = img - Scalar(200, 200, 200)
  imshow("img_sub", img_sub);
  
  //Interestingly, if the values in Scalar are negative, it will treated as subtract in add.
  
  // Subtract Example using cuda
  cuda::subtract(gimg, Scalar(200, 200, 200), gout1);
  gout1.download(img_sub);
  imshow("img_sub", img_sub);
 
  // Multiply & Divide Example
  // if the pixel value is bigger than 255, it will start over from 0. 
  multiply(img, 20, img_mul);
  // or img_mul = img * 20;
  divide(img, 20, img_div);
  // or img_div = img / 20;
  
  imshow("img_mul", img_mul);
  imshow("img_div", img_div);
  
  //absdiff
  Mat img_absdiff;
  absdiff(img, Scalar9(255, 255, 255), img_absdiff);
  imshow("Absolute Image", img_absdiff);
  
  waitKey(0)
}
```

---



