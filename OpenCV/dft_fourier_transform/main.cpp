// Author : Seungho Jang
// Reference : https://docs.opencv.org/3.4/d8/d01/tutorial_discrete_fourier_transform.html
// Description : Fourier Analysis for discrete function.
// Note : Please Look at your OpenCV version. I found that samples::findFile doesn't exist in 3.4.0

// OpenCV Library
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

// Standard Library
#include <iostream>

int main(int argc, char** argv) {
	const char* filename = argc >= 2 ? argv[1] : "lena.jpg";

	// Read the Image in the GrayScale
	cv::Mat image = cv::imread(cv::samples::findFile(filename), cv::IMREAD_GRAYSCALE);

	// Input Error Checks
	if (image.empty()) {
		std::cout << "Error Opening image \n";
		return EXIT_FAILURE;
	}

	// Expand input image to optimal size
	cv::Mat padded;

	/* The performance of a DFT is dependent of the image size. it tends to be the fastest for image
	*   sizes that are multiple of the numbers two, three and five.
	*
	*   For that reasons, it is "generally good idea to pad border values to the image to get a size with
	*   such traits. 

	*   The cv::getOptimalDFTSize return this optimal size and use cv::copyMakeBorder function to expand
	*   the borders of an image. (Basically on the border add zero values).
	*/

	int m = cv::getOptimalDFTSize(image.rows);
	int n = cv::getOptimalDFTSize(image.cols);
	cv::copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	/* The result of a Fourier Transform is complex(real & complex). This implies that for each image value the result is two image values.
	* Moreover, the frequency domain range is much larger than its spatial counterpart. Therefore, we store these usually at least in a 
	* float format. Therefore, we'll convert our input image to this type and expand it with another channel to hold the complex values.
	*/

	/*Make place for both the complex and the real values. 
	* CV::Mat_<float> : modifiy the default constructor with float type.
	* CV_32F is float - the pixel can have any values between 0 - 1.0. This has to converted into 8bits to save or 
	* display by multiplying each pixel by 255.

	* CV::Mat::zeros(Size size, int type)
	* This is overloaded member function from zeros(int rows, int cols, int type)
	* returns a zero array of the specified size and type.
	 so this function retruns the size of padded with floating-point matrix. 
	*/

	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat ComplexI;

	// Add to the expanded another palne with zeros
	cv::merge(planes, 2, ComplexI);

	// Make the discrete fourier transform : This way the result may fit in the source matrix.
	cv::dft(ComplexI, ComplexI);

	// Transform the real and complex values to magnitude
	cv::split(ComplexI, planes); //Plane[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	// Take the two arrays input, save the magnitude for each pixels.
	cv::magnitude(planes[0], planes[1], planes[0]); // Planes[0] = magnitude.

	cv::Mat magI = planes[0];

	/* Switch to a logarithmic scale : Since the fourier cofficient is too large to be displayed on the screen,
	* Make a distinct color configuration such as high values to be white points while the small values to be black.
	* In order to use that, we have to use gray scale values for visualization.
	* M = log(1+M).
	*/ 
	magI += cv::Scalar::all(1); // Switch to logarithmic scale
	cv::log(magI, magI);

	/* Crop and rearrange : since we're expanding the image, we have to rearrage the qudrants of the result for visualization purpose.
	* This means that the origin(0, 0) corresponds with the image center, not middle point of image.
	*/

	// Crop the spectrum, if it has an odd number of rows or columns
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;
	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right
	cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, cv::NORM_MINMAX); // Transform the matrix with float values into a
										      // viewable image form (float between values 0 and 1).

	cv::imshow("Input Image", image);    // Show the result
	cv::imshow("spectrum magnitude", magI);
	cv::waitKey();

	return EXIT_SUCCESS;
}