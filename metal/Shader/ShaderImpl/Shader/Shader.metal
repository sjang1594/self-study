//
//  Shader.metal
//  Shader
//
//  Created by Seungho Jang on 2/20/25.
//

#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float4 position [[attribute(0)]]; // attribute qualifier
    float4 color [[attribute(1)]];
};

struct VertexOut {
    float4 position [[position]]; // tell fragmentShader which attribute is the position (like a label)
    float4 color;
};

// [[stage_in]] qualifier to look at the buffer using the pipeline descriptor,
// this means, we don't really need to index all the vertex by the id
vertex VertexOut vertexShader(const VertexIn vertexIn [[stage_in]]){
    VertexOut out;
    out.position = vertexIn.position;
    out.color = vertexIn.color;
    return out;
}

fragment half4 fragmentShader(VertexOut vertexIn [[stage_in]]){
    // return the interpolated data.
    return half4(vertexIn.color);
}
