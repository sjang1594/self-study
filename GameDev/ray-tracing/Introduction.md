## What is Ray Tracing

In order to define the ray tracing, we need to define what is 'Ray'.
The `Ray` is defined by two things, it has origin in some point in space (xyz) and a direction.

<p align="center">
  <img src="./images/ray.JPG" width="400" height="350">
</p>

`Ray Casting` is taking the idea of taking that ray and shooting it out in that direction and finding
what gets hit.

<p align="center">
  <img src="./images/ray_casting.JPG" width="400" height="350">
</p>

This isn't the rendering algorithm. This is just the a bsic tool in the toolbox. You can also use `ray casting` between two points so you may say.

<p align="center">
  <img src="./images/ray_casting.JPG" width="400" height="350">
</p>

### Human Eye Perspective

<p align="center">
  <img src="./images/ray_casting.JPG" width="400" height="350">
</p>

### Distribution(Stochastic) Ray Tracing
- Allow shadow rays to go to a random point on area light
- Allow specular rays to be perturbed specularly around the ideal reflection.
- Shoot sometime during the frame for motion blur

Instead of shooting just a single reflection ray, you're shooting a bunch or instead of shotting one shadow ray, you're shooting a bunch to try to get
a soft shadow.

### Kajiya-Style Diffuse Interreflection -> The Rendering Equation
- Path tracing: shoot each ray and follow it along a series of interreflections.

What if we say the sky is the limit, we're just going to shoot rays out from the eye and we're going to have each ray hit something.
we don't necessarily know which way it's going to reflect. If it's a mirror we know sure it'll reflect in the mirror direction.
But say it's something like unglazed pottery, then you don't know which way the lights are coming from. all kinds of different directions.
So, you shoot more rays in different directions, but with path tracing you shoot just one ray in one direction and follow it along a path.

### Rasterization versus Ray Tracing
Rasterization loop look at the object, then look at each pixels. But Ray Tracing is for each pixel and look at each object.

**Triangle versus Point ?**

The benefit of rasterization as compared to `Ray Tracing` is following
- Hierarchical frustum culling (also using a BVH)
- Level-of-detail culling and simplification
- Occlusion culling in various forms
- Hierarchical Z-buffering

**The Bounding Volume Hierarchy(BVH)**
This scheme mostly won the efficiency data structure war. So, what this does is we shoot the rays once it hits we open the circle up, then look at the children
whether they hit. If they don't we simply discard it.

### BVH Algorithm
Use the Bounding Boxes. (Looking at the box of subboxes)

### Ray Tracing Hardware
