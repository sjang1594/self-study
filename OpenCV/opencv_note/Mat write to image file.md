## Mat write to image file

should include ffmeg.dll & imgcodec.dll

``` c++
/* For Image */
// Read Image
Mat img = imread("input.jpg");
vector < Mat > rgbMat(3);

// Split each channels into rgbMat.(order of BGR)
cv::split(img, rgbMat);

namedWindow("img", 0); //Make a window
imshow("img", rgbMat[2]); //show
waitKey(0);

// Save image in different formats.
imwrite("r.jpg", rgbMat[2]);
imwrite("g.bmp", rgbMat[1]);
imwrite("b.tif", rgbMat[0]);

cout << img.channels() << endl;
cout << rgbMat[2].channels() << endl;

/* For Video */
// Load the video
VideoCapture capture("input.avi");
Mat frame;

//Set Properties
int askFileTypeBox = 1; // -1 show box of codec
int Color = 1;
Size S = Size(int)capture.get(CV_CAP_PROP_FRAME_WIDTH, (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT);

//Make output video file
VideoWriter outVideo;
/* Parameters 1. : file that you want to save.
							2. : What codecs 
							3. : FPS (Frame per sec), CV_CAP_PROP_FPS : save it as input fps
							4. : Size of video
							5. : Color, Black & White.
*/
outVideo.open("./outVideo.avi", askFileTypeBox, caputer.get(CV_CAP_PROP_FPS), S, Color);
                              
//check
if (!capther.isOpened()){
  printf("AVI file can not open /n");
  return 0;
}
                              
//Create a window
namedWindow("w");

while(1){
  //Grab frame from file & throw to mat
  caputer >> frame;
  if(frame.empty()){
    break;
  }
  //Processing example
  Sobel(frame, frame, frame.depth(), 1, 0);
  outVideo.wrie(frame);
  //outVideo << frame; this way could be right as well.
  
  //display && delay
  imshow("w", frame);
  if(waitKey(10 > 0))
    break;
}
                             
```



