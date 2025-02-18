//
//  Shaders.metal
//  MetalRender
//
//  Created by Seungho Jang on 2/18/25.
//

#include <metal_stdlib>
using namespace metal;

struct Vertex {
    float2 position [[attribute(0)]];
    float4 color [[attribute(1)]];
};

struct Fragment {
    float4 position [[position]];
    float4 color;
};

vertex Fragment vertexShader(uint vid [[vertex_id]], constant Vertex* vertices){
    Fragment output;
    output.position = float4(vertices[vid].position, 0.0, 1.0);
    output.color = vertices[vid].color;
    return output;
}

fragment float4 fragmentShader(Fragment input [[stage_in]]) {
    return input.color;
}
