# Graph SLAM 

---
1. Linear Graph SLAM

**"Computer Vision" -- Udacity**

## Introduction

Let's assume that we have the robot's initial position is X<sub>0</sub>, and the robot moves to 10 meter more at X<sub>1</sub>. We can use simple physics equation to figure out the next location by using this formula : X<sub>1</sub> = X<sub>0</sub> + v*t. However, The robot's locations are set or defined by the gaussian. Then the next location estimation would be the formula below.

$\LaTeX$:$\frac{1}{\sqrt{2 * pi * \sigma}}*e^{\frac{-(x_{1}- x_{0} - 10)^2}{2 *\sigma^{2}}}$​​ for X​

$\LaTeX$:$\frac{1}{\sqrt{2 * pi * \sigma}}*e^{\frac{-(y_{1}- y_{0} - 10)^2}{2 *\sigma^{2}}}$ for Y

The product of these two Gaussians is now our constraints. We wish to maximize the likelihood of the position X<sub>1</sub>, given that the position X<sub>0</sub>

## So what does GraphSALM do?
It defines our probabilities using a sequence of such constraints.

For example, if we have a roboot that moves in some space, and each location is now characterized by vectors. Then we'll graph some collects its initial location.(**Initial Location Constraints**)
Then, importantly, the lots of relative constraints that relate each robot pose to the previous world pose. (**Relative Motion Constraints**). Suppose we have a landmark in spepcific location, and the landmark is being seen from the robot with some relative measurement from each location.(**Z**, **Relative Measurement Constraints**). One such constraint very time the robot sees a landmark. Finally, GraphSLAM collets those constraints(**Initial Location Constraint, Relative Motion Constraint, Relative Measurement Constraints**), relax this the set of rubber bands to find the most likely configuration of robot path along with the location of landmarks, and this is called "Mapping Process."

### Quiz 
`For a series of robot motions and landmark locations, how many constraints will there for 6 total poses and 8 landmarks`

`Answer : 14`

**Why it is 14 ?**

### Constraints
For our 6 poses, we have:
* 1 initial location constraint
* 5 additional, relative motion constraints, and finally, 
* 8 relative measurement constraints for the 8 landmark locations

Adding all of these up gives us a total of **14** constraints.

Now, with 4 poses (including the inital location `X0`) and one landmark, We can use this same math and say that there are 5 total constraints for the given image, but in practice there are usually many more measurements and motions!

## Constraints Matrix
Next, we have to observe how to implement the relationships between robot poses and landmark locations. These matrix works like a **weight** in convolutional kernels, only these weights imply how much a pose or landmark should be weighted in a set of equations. 

Once you fill out the matrix by looking at those three contstraints, this will tell you the best estimate of robot's location. 

Then, what we have to do is invert that matrix(omega) times the corresponding vecotr (xi), then you  will get mu. The matrix is square and labelled with all the robot poses(xi) and all the landmarks(Li). Every time you make an observation, for example, as you move between two posses by some distance `dx` and can relate those two positions, you can represent this as a numerical relationship in these matrices. 

