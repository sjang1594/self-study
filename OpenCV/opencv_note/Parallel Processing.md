## Parallel_for

Assumption : if the processing the pixel would not overlap the overall control flow, then you can use parallel processing

Install Prerequisite : **Including build TBB & IPP**.

* void parallel_for_(const Range& range, const ParallelLoopBody& body, double nstrips=-1)
  * Create a body by inheriting the `ParallelLoopBody` class
  * Parallel processing is made by the `range`

 ```c++
class Parallel_process : public cv::ParallelLoopBody{
  private :
  cv::Mat& inImg;
  cv::Mat& outImg;
  int widthStep;
  //int m_stride;
  cv::Scalar scalar; //BGR
  
  public:
  //constructor
  // When parallel_for is called, the parameters are going to come in.
  Parallel_process(cv::Mat& inputImage, Mat& outputImage, Scalar& inScalar)
    : inImg(inputImage), outImg(outImage), scalar(inScalar){
      
      //calculate withStep --> multiply 3 due to three channel
      widthStep = inputImage.size().width * 3;
      //m_stride = inputImage.size().width * 3;
    }
  
  virtual void operator()(const cv::Range& range) const
  {
    //thread - multi threading for height.
    for (int i = range.start; i < range.end; i++){
      
      int s1 = i*widthStep;
      
      // This is going to be process in each thread for all width
      for (int iw = 0; iw < inImg.size().width; iw++){
        int s2 = iw * 3;
        int mc = s1 + s2;
        
        unsigned char B1 = (unsigned char)(inImg.data[mc + 0]);
        unsigned char G1 = (unsigned char)(inImg.data[mc + 1]);
        unsigned char R1 = (unsigned char)(inImg.data[mc + 2]);
        
        int B2 = B1 + scalar[0];
        int G2 = G1 + scalar[1];
        int R2 = R1 + scalar[2];
        
        if(B2 > 255)
          B2 = 255;
        if(G2 > 255)
          G2 = 255;
        if(R2 > 255)
          R2 = 255;
        if(B2 < 0)
          B2 = 0;
        if(G2 < 0)
          G2 = 0;
        if(R2 < 0)
          R2 = 0;
        
        outImg.data[mc + 0] = B2;
        outImg.data[mc + 1] = G2;
        outImg.data[mc + 2] = R2;
      }
    }
  }
}

int main(){
  cv::Mat img, img_parallel;
  
  img_parallel = Mat(img.size(), img.type());
  cv::imread("Input image", img, cv::IMREAD_COLOR);
  
  //Parallel Processing
  cv::parallel_for_(cv::Range(0, img.rows), Parallel_process(img, img_parallel, Scalar(-200, -200, -200)));
}
 ```

