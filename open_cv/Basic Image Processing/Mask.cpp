//
// Created by Seungho on 1/28/2021.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(){
    String file_path = "C:\\Users\\skcjf\\Github_REPO\\self-study\\OpenCV\\images\\gromit.jpg";
    Mat img = imread(file_path, COLOR_BGR2GRAY);
    imshow("img", img);
    Mat img_mask = img.clone();
    img_mask = Mat::zeros(img.size(), img.type());
    bitwise_and()

    imshow("Mask Image", img_mask);
    waitKey();
}
