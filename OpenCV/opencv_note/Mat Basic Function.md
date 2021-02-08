**First Mat use (Continued ...)**

1. Set Value 
2. Vector to Mat & Mat to Vector.
	
		Mat img = imread("*.jpg" ); // imread(".jpg", 0); --> GrayScale, make channel 1.
	
	//namedWindow("Name", 0) // 0 makes resize, 1 is fixed size
	//imshow("Name", img); // imshow string should be same as namedWindow parameter. 

	
	int main ( ){
		Mat img = imread(".jpg");
		bitwise_not(img, img);
		
		// this is not copying the "img" into img_s, img_s will refer to img.
		// With that said, if img is changed, the img_s will be changed as well.
		Mat img_s = img;
		
		// Then how to copy (deep copy)
		Mat img2 = img.clone();
		imshow("img2", img2);
		waitKey();
		
		Rect r(img.cols / 4, img.rows /4, img cols /4 * 2, img.rows / 4 * 2);
		// [314 x 472 from (157, 236)]
		cout << r << endl;
		
		Mat img5 = img(r).clone();
		imshow("img5", img5)
		
		//Member Function : copyTo(). This will be the same as input image.
		Mat cimg;
		img.copyTo(cimg) // copy entire image
		imshow("cimg", cim);
		
		//CopyTo() extended1
		Mat cime2;
		img(r).copyTo(cimg2) // copy rect region from the image.
		
		//CopyTo() extended2 : Copy one image to the other.
		Mat cimg3(Size(img.cols * 2, img.rows), img.type()); //Twice the width
		cimg3.setTo(255); // set to 1
		// Copy all the rows and cols form columns in image
		img.copyTo(cimg3(Range:all(), Range(0, img.cols)) );
		bitwise_not(img2, img2);
		img2.copyTo(cimg3(Range:all(), Range(img2.cols, img2.cols * 2)) );
	
		//Set roi. img : what do you want to copy, r : obtain the roi. 
		Mat roi(img, r);
		
		// Since img changes, roi also changes
		bitwise_not(roi, roi);
		imshow("roi", roia)
	}
	
	