#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	// Number of Clusters
	const int MAX_CLUSTERS = 5;
	Scalar colorTab[] =
	{
		Scalar(0, 0, 255),
		Scalar(0, 255, 0),
		Scalar(255, 100, 100),
		Scalar(255, 0, 255),
		Scalar(0, 255, 255)
	};

	Mat img(500, 500, CV_8UC3);
	
	//Random Generator(Constructor) Class from opencv2/core.hpp
	RNG rng(12345);

	for (;;)
	{
		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS);
		int i, sampleCount = rng.uniform(1, 1001);

		Mat points(sampleCount, 1, CV_32FC2), labels;
		// # define MIN ( a, b ) ((a) > (b) ? (b) : (a))

		// Why?
		clusterCount = MIN(clusterCount, sampleCount);
		std::vector<Point2f> centers;

		/* Generate random sample from multi gaussian distribution*/
		// cv::RNG::uniform return uniformly distrubted integer random number from [a,b) range
		// ex : double a = rng.uniform(0.f, 1.f); produce float from [0, 1)
		for (k = 0; k < clusterCount; k++) {
			Point center;
			center.x = rng.uniform(0, img.cols);
			center.y = rng.uniform(0, img.rows);
			
			// Creates a matrix header for the specified row span.
			Mat pointChunk = points.rowRange(k * sampleCount / clusterCount, k == clusterCount - 1 ? sampleCount : (k + 1) * sampleCount / clusterCount);
			/* rng.fill (InputOUtputArray, mat, int distType, inputArray a, inputArray b, bool 
			mat : 2D or N-dimensional matrix
			distType : distribution type - RNG::UNIFORM & RNG::NORMAL
			a : first distribution parameter, this is going to be the mean value in case of normal distribution
			b : second distribution parameter, this is standard deviation (diagonal of the standard deviation matrix or the full standard deviation matrix)*/
			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols * 0.05, img.rows * 0.05));
		}

		// randomly shuffles the specified 1D array by randomly choosing pairs of elements and swwapping them. 
		// The number of such swap operation will be dst.rows*dst.cols*iterFactor. 
		randShuffle(points, 1, &rng);

		/* Points are supposed to be 32 bit Floating points, K is the number of clusters to split the set by
		*  Attempts is the flag to specify the number of times the algorithm is executed using different initial labellings.
		*/
		double compactness = kmeans(points, clusterCount, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

		img = Scalar::all(0);

		for (i = 0; i < sampleCount; i++) {
			int clusterIdx = labels.at<int>(i);
			Point ipt = points.at<Point2f>(i);
			circle(img, ipt, 2, colorTab[clusterIdx], cv::FILLED, LINE_AA);
		}

		for (i = 0; i < (int)centers.size(); ++i) {
			Point2f c = centers[i];
			circle(img, c, 40, colorTab[i], 1, LINE_AA);
		}

		cout << "Compactness : " << compactness << endl;
		imshow("cluster", img);

		///imwrite("cluster_img.png", img);
		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}

	return 0;
}

