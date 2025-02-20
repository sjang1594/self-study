//
//  Shader.metal
//  ConstantBuffer
//
//  Created by Seungho Jang on 2/19/25.
//

#include <metal_stdlib>
using namespace metal;

struct Constants {
    float animatedBy;
};

vertex float4 vertexShader(const device packed_float3 *vertices [[buffer(0)]],
                           constant Constants &constants [[ buffer(1) ]],
                           uint vertexId [[vertex_id]]){
    float4 position = float4(vertices[vertexId], 1);
    position.x += constants.animatedBy;
    position.y -= constants.animatedBy;
    return position;
}

fragment half4 fragmentShader(){
        return half4(1, 0, 0, 1);
}
