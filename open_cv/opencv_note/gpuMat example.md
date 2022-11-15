## Mat and gphMat

```c++
#include "opencv2/cuda.hpp"
#include "opencv2/cudaarithm.hpp"
#include "opencv2/cudafilters.hpp"

cuda::GpuMat gpulmg; //gpuImg_out;
Mat img = imread(".jpg");

gpuImg.upload(img); //upload the content(memory) from CPU into GPU memory.
vector<cuda::GpuMat> rgbGpuMat(3);
cuda::split(gpuImg, rgbGpuMat); // cuda processing

//cuda::bitwise_not(gpuimg, gpuImg_out)
Mat r, g, b;
rgbGpuMat[0].download(b); //download
rgbGpuMat[1].download(g);
rgbGpuMat[2].download(r);

namedWindow("r", 0); //make window
imshow("r", r); //show

namedWindow("g", 0);
imshow("g",g);

namedWindow("r", 0);
imshow("r", r);
```





