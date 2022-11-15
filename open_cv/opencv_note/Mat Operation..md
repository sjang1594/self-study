Mat Operation

	// Create a 3x3 matrix filled with ones (64 bits Floating Point)
	Mat m = Mat::ones(3,3, CV_64F); 
	m = m * 3
	cout << m << endl;

	//Create a 3x3 matrix filled with zeros(64 bit Floating Point)
	Mat zero = Mat::zeros(3,3 CV_64F);

	double dm[3][3] = {{1, 2, 1}, {0, 1, 1}, {1, 0, 0}};
	//Put dm into Mat
	Mat m2 = Mat(3,3, CV_64F, dm);

	cout << m2 << endl;
	cout << m+m2 << endl;
	cout << m-m2 << endl;
	//This is matrix multiplication
	cout << m*m2 << endl;

	//Multiply each element in m and m2. 
	cout << m.mul(m2) << endl << endl;
	cout << m/m2 <<endl;

	//Inverse Matrix
	//This doesn't work if the row and col are not same. 
	cout << m2.inv() << endl;

	//transpose Matrix 
	cout << m2.t() << endl; 

	//Since dm is used as reference in Mat m2, the m2 variable changes as well as 	dm.
	m2 = m + m2;
	cout << m2 << endl;

	for (int r = 0; r < 3; ++r){
		for(int c = 0; c < 3; ++c){
			cout <<[dm[r][c] << " ";
		}
		cout << endl;
	}