## Graph SLAM 

---

"Computer Vision" -- Udacity

Let's assume that we have the robot's initial position is X<sub>0</sub>, and the robot moves to 10 meter more at X<sub>1</sub>. We can use simple physics equation to figure out the next location by using this formula : X<sub>1<sub> = X<sub>0</sub> + v*t. However, The robot's locations are set or defined by the gaussian. Then the next location estimation would be the formula below.

$\LaTeX$:$\frac{1}{\sqrt{2 * pi * \sigma}}*e^{\frac{-(x_{1}- x_{0} - 10)^2}{2 *\sigma^{2}}}$​​ for X​

$\LaTeX$:$\frac{1}{\sqrt{2 * pi * \sigma}}*e^{\frac{-(y_{1}- y_{0} - 10)^2}{2 *\sigma^{2}}}$ for Y



