## Linear Algebra Operation ( Solver, eigen value, vector, SVD )

Elementwise matrix operations

``` c++
cv::multiply(Ma, Mb, Mc);
cout << Mc << endl;
Mc = Ma.mul(mb);
cout << Mc << endl;
cv::divide(Ma, Mb, Mc);
cout << Mc << endl;
Mc = Ma + 10; // Ma + 10 = Mc
cout << Mc << endl; 
```

Vector Products

```c++
//Vector products :
double va[] = { 1, 2, 3 };
double vb[] = {0, 0, 1};
double vc[3];

Mat Va(3, 1, CV_64FC1, va);
Mat Vb(3, 1, CV_64FC1, vb);
Mat Vc(3, 1, CV_64FC1, vc);

doulbe res = Va.dot(Vb); // Dot product : Va . Vb -> res
Vc = Va.cross(Vb);       // Cross product : Va x Vb -> Vc
cout << res << " " << Vc <<endl;
```

Single Matrix Operations

``` c++
//Single matrix operations : 
Mc = Mb.t(); //transpose (Ma) -> Mb (cannot transpose onto self)
cout << Mc << endl;
cv::Scalar t = trace(Ma); //trace(Ma) -> t.val[0], Sum of diagnoal value
cout << t.val[0] << endl;

double d = determinant(Ma); //det(Ma) -> d
cout << d << endl;
Mc = Ma.inv();  // inv(Mb) -> Mc
invert(Ma, Mc);
cout << Mc << endl;
```

Inhoogeneous Liinear System Solve

``` c++
//Inhomogeneous linear system solver :
double dm2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
Mat A(3, 3, CV_64FC1, dm2);
Mat x(3, 1, CV_64FC1);
double vvb[] = { 14, 32, 53 };
Mat b(3, 1, CV_64FC1, wb);
cv::solve(A, b, x DECOMP_SVD); //// solve (Ax = b) for x
cout << x << endl;
```

Eigen Analysis

``` c++
//Eigen Analysis
float f11[] = {1, 0.446, -.54, .446, 1, -.239, -.56, .239, 1};
Mat data(3, 3, CV32F, f11);
Mat value, vector;
//eigen function.
eigen(data, value, vector);
cout << "Eigenvalues" << value << endl;
cout << "EigenVector" << vector << endl;

```

Single Vector Decomposition

```c++
float f11[] = {1, 0.446, -.54, .446, 1, -.239, -.56, .239, 1};
Mat data(3, 3, CV32F, f11);

Mat w, u, v;
// decompose data into w, u, v
SVDecomp(data, w, u, v); // A = U* W * V^T
//The flags cause U and V to be retured transposed(does not work well without the transpose flags)
cout << u << endl;
cout << w << endl;
cout << v << endl; 
```

