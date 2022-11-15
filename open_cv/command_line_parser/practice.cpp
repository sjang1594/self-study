#include <iostream>

//For commandline parser
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// @image1 is the input, fruits.jpg is the default.
const char* keys = { "{@image1 | fruits.jpg | input image file}"
                     "{@image2 | fruits.jpg | input image file}"
                     "{N | 1.0 | this is double value}"
                     "{help h ? | | this is help}" };

int main(int argc, char** argv) {
    cv::CommandLineParser parser(argc, argv, String(keys));
    parser.about("This is the program for commandlineparser of opencv ");
    string input_image1 = parser.get<String>(0);
    string input_image2 = parser.get<String>(1);

    cout << "Argument1 is : " << input_image1 << endl;
    cout << "Argument2 is : " << input_image2 << endl;
    cout << "Argument 3 is : " << parser.get<double>("N") << endl;

    if(parser.has("help") == true){
        parser.printMessage();
        return 0;
    }
    String input_image = parser.get<String>("@image1");
    Mat src1 = imread( input_image , IMREAD_GRAYSCALE);
//Mat src2 = imread( samples::findFile( parser.get<String>("@image2") ), IMREAD_GRAYSCALE);

    if (src1.empty()){
        cout << "Could not open or find the image!\n" <<endl;
        cout << "Usage : " << argv[0] << " <Input image> " << endl;
        return -1;
    }
    imshow("source1", src1);
    waitKey(0);


    return 0;
}