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
    float2 textureCoordinate [[attribute(2)]];
};

struct VertexOut {
    float4 position [[position]]; // tell fragmentShader which attribute is the position (like a label)
    float4 color;
    float2 textureCoordinate;
};

// [[stage_in]] qualifier to look at the buffer using the pipeline descriptor,
// this means, we don't really need to index all the vertex by the id
vertex VertexOut vertexShader(const VertexIn vertexIn [[stage_in]]){
    VertexOut out;
    out.position = vertexIn.position;
    out.color = vertexIn.color;
    out.textureCoordinate = vertexIn.textureCoordinate;
    return out;
}

fragment half4 fragmentShader(VertexOut vertexIn [[stage_in]]){
    // return the interpolated data.
    return half4(vertexIn.color);
}

fragment half4 texturedFragmentShader(VertexOut vertexIn [[stage_in]],
                                     sampler sampler2d [[sampler(0)]],
                                     texture2d<float> texture [[texture(0)]]) {
    float4 color = texture.sample(sampler2d, vertexIn.textureCoordinate);
    return half4(color.r, color.g, color.b, 1);
}
