What about Mat ? 

1. Matrix Class
2. Image, values, ... Think of all the data in a <u>Matrix!</u>
3. Let's use a Mat simply



First Mat use

1. Creation
2. Set Value
3. cout 

`int main(int char){`
`Mat mtx(3, 3, CV_32F); // make a 3x3 (rows x cols) 32bits floating points matrix`
` Mat cmtx(10, 1 CV_64FC2) // make a 10x1, "C" represents 2 channels, floating point matrix` 
`mat img(Size(5,3), CV_8UC3) `

`/* make a 3-channel(Color) image of 1920. U = Unsigned Character. coloums and 1080 rows. Size(width.img, height.img) */` 

`// Create and Set Mat`
`Mat mtx2; mtx2 = Mat(3, 3, CV_32F);`
`Mat cmtx2; cmtx2 = Mat(10, 1, CV_54FC1) //default channel is 1`

`// Create a point`
`Mat* mtx3 = new Mat(3,3, CV_32F);`
`delete mtx3` 
`//value set and print` 
`mtx.setTo(10)`
`cout << ptx << endl;`
`cmtx2.setTo(11);`
`cout << cmtx2 << endl;` 