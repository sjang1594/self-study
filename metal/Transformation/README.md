### Transformation
* It is simply important to understand that when we load the texture, it seemd to be fit into iphone's screen size (x range from -1, 1, y range from -1, 1), so called Normalized Coordinates (or NDC) But sometimes, we want to rotate, scale, or translate the texture, such that it looks much more natural. 

* Note: metal is column-major order, which means the matrix is stored in the memory as a column-wise order.
* which means in the Metal Shader, the multiplication order is from right to left. For instance, projection * view * model * vertex. in this order. 
* When we send the whole data from cpu, those calculation must be done as the same order as the shader.

### Metals NDC (Normalized Device Coordinates)
* x range from -1, 1 (from left to right)
* y range from -1, 1 (from bottom to top)
* z range from 0, 1  (from near to far)

### Texture Coordinates
* x range from 0, 1 (from left to right)
* y range from 0, 1 (from bottom to top)

### View Matrix
* This matrix is used to transform the world coordinates to the camera coordinates.

For example, if we translate view matrix to be 0, 0, 4, then the camera is looking at the origin point (0, 0, 0) from the positive z-axis. which also means, setting the object to be 4 units away from the camera. For Instance, if you want the camera location to be -4, then you will set translation(0, 0, -4) for the view matrix, then you are setting the camera to be (0, 0, -4). In this case, you won't be able to see the texture. because it's basically out of the scene. But if you use `inverse` view matrix, it means you basically flip the coordinate, which in this case, you will put the object into the positive-z direction for 4 unit away from camera.

It's more clear that I have `lookedAt` vector to clear things out.
### Keywords
* Model Transformation
* View Transformation
* Projection Transformation

### Output

![Alt text](<../asset/gif/rotate.gif>)
