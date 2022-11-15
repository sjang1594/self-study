## Adaptive Threshold

* One threshold can not binarize in different brightness.
* So we get different thresholds for ***different regions of the same image***.
  - Adaptive thresholding 
  - The algorithm calculate the threshold for a small regions of the image

What do you mean by "**different regions of the same image**", look at following image:

![ada_threshold.jpg](https://docs.opencv.org/3.4/ada_threshold.jpg)

When you do thresholding, you will threshold in each region.

<img src="C:\Users\skcjf\Github_REPO\self-study\OpenCV\images\image-20210316132420316.png" alt="image-20210316132420316" style="zoom: 50%;" />

```c++
void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
```

- Adaptive Method : `ADAPTIVE_THRESH_MEAN_C` and `ADAPTIVE_THRESH_GAUSSIAN_C`

* Threshold Type : `THRESH_BINARY` and `THRESH_BINARY_INV`
* Block Size : 3, 5, 7
* C : used for subtracting the thresholding value to this value. 

<img src="C:\Users\skcjf\Github_REPO\self-study\OpenCV\images\image-20210316214734192.png" alt="image-20210316214734192" style="zoom:50%;" />