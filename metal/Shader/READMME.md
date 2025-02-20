### Shader Programming 
* The structure of project is the same as ConstantBuffer, but this time, the shader input / output is changed as well as `VertexDescriptor` are changed. 
* What this will do send `Vertex` struct from cpu to gpu, then gpu takes Vertex Struct including attributes.
* Use this qualifier `[[stage_in]]` to pass the data from `Vertex` struct to `VertexOut` struct. Then `VertexOut` struct is used in `fragmentShader` to return the color.

### Note
* Note that I changed the directory name to `ShaderImpl`, it's because the descriptor cannot find the shader file if the file name or directory name is `Shader`.
* from fragmentShader, all colors are interpolated for each corner in the screen and returned as a color.

### Output
![Alt text](<../asset/img/shader.png>)