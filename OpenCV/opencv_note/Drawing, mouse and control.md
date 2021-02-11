## LIne, Circle, Rectangle

### Drawing

* Point, Line, Polyline, Circle ...
* Text Out
* drawContours

### Mouse Event

* Basic Event
* Application

### Control 

* Slide

---

## Drawing

### Line 

* void line(InputOutput Array_img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType=LINE_8, intshift = 0)

```c++
Mat img(500, 500, CV_8UC3);
img.setTo(255);

//Line example
cv::Point pt(300, 300);
line(img, Point(10,10), pt, CV_RGB(255, 0, 0), 1);
line(img, Point(300, 10), Point(30, 300), Scalar(255, 0, 0), 3);

imshow("show", img);
waitKey(0);
return 0;
```

### Circle 

* void circle(inputOutput Array img, Point center, int radius, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift =0)

``` c++
//Circle example
circle(img, Point(250, 250), 100, CV_RGB(0, 255, 0), 3);
cv::Point center(400, 400);
circle(img, center, 300, Scalar(255, 255, 0), 10);
// -1 filled.
circle(img, Point(40,40), 10, Scalar(255, 0, 0), -1);
```

### Rectangle

* void rectangle(InputOutput Array img, Point pt1, Point pt2, const Scalar& color, int thickiness =1, int lineType = LINE_8, int shift = 0);

``` c++
//Rectangle example
rectangle(img, Rect(10, 10, 200, 200), CV_RGB(255, 0, 0), 2);
// from (40, 40), draw 400 width and 400 height
rectangle(img, Rect(Point(40, 40), Point(400, 400)), Scalar(255, 0, 0), 10);
```

### Elipse

* void elipse(InputOutput Array img, Point center, Size axes, double angle, double starAngle, double endAngle, const Scalar& color, int thickiness =1, int lineType = LINE_8, int shift = 0);

  ``` c++
  //Ellipse Example
  ellipse(img.Point(100, 100), Size(100, 50), 0, 0, 360, CV_RGB(255, 0, 0));
  
  //Ellipse Example - using roatedRect class
  RotatedRect rRect = RotatedRect(Point2f(300, 300), Size2f(300, 100), 45);
  ellipse(img, rRect, CV_RGB(255, 0, 0));
  
  //Draw rect and inside rect in RoatedRect
  Point2f vertices[4];
  rRect.points(vertices);
  for (int i = 0; i < 4; i++)
    line(img, vertices[i], vertices[(i+1) % 4], Scalar(0, 255, 0));
  
  Rect brect = rRect.boundingRect();
  rectangle(img, brect, Scalar(255, 0, 0));
  ```

### Polyline

* Void polylines(Mat& img, const Point* const *pts, const int* npts, int ncontours, bool isColsed, const Scalar &color, int thickness =1, int lineType = LINE_8, int shift = 0)

``` c++
//Polyline example
vector<Point> contour;
contour.push_back(Point(50, 50));
contour.push_back(Point(300, 50));
contour.push_back(Point(350, 250));
contour.push_back(Point(300, 150));
contour.push_back(Point(150, 350));
contour.push_back(Point(100, 100));

// Casting the type "Mat" for contour
// the address of the data will be casted as Point* put it in pts.
const Point *pts = (const cv::Point*) Mat(countour).data;
int npts = Mat(contour).rows;

cout << "Number of polygon vertices : " << npts << endl;

//draw polygon
// false - don't connect the start and end points. 
// 1 - number of lines.
polylines(img, &pts, &npts, 1, false, Scalar(0, 255, 0));

//polyline example2
contour.clear();
contour.push_back(Point(500, 500));
contour.push_back(Point(250, 250));
contour.push_back(Point(50, 300));

// Casting the type "Mat" for contour
// the address of the data will be casted as Point* put it in pts.
pts = (const cv::Point*) Mat(contour).data;
npts = Mat(contour).rows;
//This is closed polygones.
polylines(img, &pts, &npts, 1, true, Scalar(255, 0, 0));

//polyline example3 - draw 2 lines 
vector<Point> contour2;
contour2.push_back(Point(230, 220));
contour2.push_back(Point(10, 50));
contour2.push_back(Point(50, 200));
contour2.push_back(Point(50, 150));

Point *pts2 = (cv::Point *) Mat(contour2).data;
int npts2 = Mat(contour2).rows;

const Point *n_pts[2] = {pts, pts2};
//n_pts[0] = pts; n_pts[1] = pts2;
int n_npts[2] = {npts, npts2};
polylines(img,n_pts, 2, false, Scalar(0, 255, 0), 2);

//draw polylines with line function.
for (int i = 0; i < contour.size() -1; ++i)
  line(img, contour[i], contour[1], cv::Scalar(0, 255, 0), 2);
line(img, contour[contour.size() - 2], contour[contour.size() - 1], cv::Scalar(0, 255, 0), 2);
```

### fillConvexPoly

* void fillConvexPoly(Mat &img, const Point*pts, int npts, const Scalar& color, int lineType = LINE_8, int shift =0)

``` c++
//fillConvexPoly example
cv::Point pt[4];
pt[0] = cv::Point(100, 100);
pt[1] = cv::Point(150, 200);
pt[2] = cv::Point(300, 300);
pt[3] = cv::Point(400, 100);

cv::fillConvexPoly(img, pt, 4, cv::Scalar(0, 0, 255));
```

---

## PutText, draw Contours, find Contours

### putText

* void putText(iinputOuput Array img, const String& text, Point org, int fontFace, double fontScale, Scalar color, intthickeness =1, int lineType=LINE_8, bool bottomLeftOrigin=false )

``` c++
char TestStr[100];
sprintf(TestStr, "Total time : %lf sec", 0.001);
putText(img, TestStr, Point(10, 250), CV_FONT_NORMAL, 1, Scalar(0, 0, 0), 1, 1); //outimg is Mat class
```

### drawContours

* void drawContours(inputOutput Array image, InputArrayofArrays contours, int contourldx, const Scalar& color, int thinkness =1, int lineType = LINE_8, InputArray hierachy=noArray(), int maxLevel=INT_MAX, Point offset=Point() )
* findContours input is only CV_8UC1
* Note, after processing findContours, SRC is changed

``` c++
//외곽선

//drawContour Example
cvtColor(img, img, CV_RGB2GRAY);
img.setTo(0);
rectangle(img, Rect(10, 10, 200, 200), CV_RGB(255, 255, 255), CV_FILLED);
imshow("show 1", img);
waitKey(0);

// Same size, but channel is three
Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);

vector<vector<Point>> contours;
vector<Vec4i> hierachy;

//It's good practice to use clone because it will change the input image file. 
findContours(img.clone(), contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

//ex 1)
//put all contours (-1) with red color, thickness of 1, line type = 8, hierachy 
drawContours(dst, contours, -1, CV_RGB(255, 0, 0), 1, 8, hierachy);

// if you want to put other color(random) image into contours, then use this. 
//iterate through all the top-level controus.
//draw each connected component with its own random color
int idx = 0;
for (; idx >=0; idx = hierachy[idx][0]){
  Scalar color(rand() & 255, rand() & 255, rand() & 255);
  //drawContour(dst, contours, idx, color, FILLED, 8, hierachy);
  drawContour(dst, contours, idx, color, 1, 8, hierachhy);
}

imshow("contours", dst);

// ex 3) without drawContours.
for (int i =0; i < contours.size(); ++i){
  for (2int j =0; j < contours[i].size() -1; ++j){
    line(dst, contours[i][j], contours[i][j+1], CV_RGB(255, 0, 0), 1);
  }
  
  line(dst, contours[i][0], contours[i][contours[i].size()-1], CV_RGB(255, 0, 0), 1);
}
imshow("contours 2", dst);

// ex 4) 
for (int i = 0; i < contours.size(); ++i){
  Scalar color(rand() & 255, rand() & 255, rand() & 255);
  drawContours(dst, contours, i, color, 1, 8, hierarchy)
}
```

---

## Mouse Event

* you can capture mouse event very easy using callback funtion.
* "setMousCallback" function is that callback funtion settings.
* In order to receive an event, you have to create the callback function. What callback funtion is, user don't call the function, but system calls that function. That means, we have to create the function for system to call that function. 

``` c++
void CallBackFunc(int event, int x, int y, int flags, void* userdata){
  if (event == EVENT_LBUTTONDOWN){
    // use x,y
    printf("Lbuttondown down %d, %d /n", x, y);
    
    circle(*(Mat*)userdata), Point(x, y), 2, CV_RGB(255, 0, 0), 3);
  }
  else if(event == EVENT_RBUTTONDOWN){
    // use x, y
    printf("Rbuttondown down %d, %d /n", x, y);
  }
  else if(event == EVENT_MBUTTONDOWN){
    // use x, y
    printf("Mbuttondown down %d, %d /n", x, y);
  }
  else if(event == EVENT_MOUSEMOVE){
    // use x. y
    printf("Move %d, %d /n", x, y);
  }
  
  //By doing this, this doesn't look clean
  //imshow("img", (*(Mat*)userdata));
}

int main()
{
  // Read image from file
  Mat img = imread(".jpg");
  if (img.empty()){
    cout << "Error loading the image"<<endl;
    return 0;
  }
  
  namedWindow("My window", 1);
  
  //set the callback function for any mouse event
  //setMouseCallback("My window", CallBackFunc, NULL);
  setMouseCallback("My window", CallBackFunc, %img);
  
 	while(1)
  {
    imshow("img", img);
    if(waitKey(10) > 0)
      break;
  }
  //wait untill user press some key
  
  //destroyallwindows.
  return 0;
}
```

### Mouse Event in video

look at the reference & slide.

---

## Trackbar Control

* Very simple
* Create callback function using "createTrackbar" function
* g_slider value captured when value is changed in on_trackbar
* g_slider value can use any line in code, because the variable is global

``` c++
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int g_slider; //slider pos value
itn g_slider_max; //slider max value 

void on_trackbar(int, void*){ 
  if (g_slider % 2 == 0)
    gslider += 1;
  printf("%d,\n", g_slider); 
}

int main(){
  //Read image from files
  Mat img = imread("input.img");
  Mat img2;
  
  //set
  g_slider = 0;
  g_slider_max = 31;
  
  //window name 
  namedWindow("My window", 1);
  
  //make trackbar call back
  createTrackbar("TrackbarName", "My window", &g_slider, g_slider_max, on_trackbar);
  
  while(1){
  	// Image processing
  	Sobel(img, img2, CV_8U, 1, 9, g_slider);
  	imshow("My window", img2);
    
    //Wait until user press some key
    int key = waitKey(10);
    
    if(key > 0)
      break; 
  }
  //show image
}
```

