//
//  definitions.h
//  Bridging Header
//  - Use CPU Data type for sending this to GPU
//  Created by Seungho Jang on 2/18/25.

#ifndef definitions_h
#define definitions_h

#include <simd/simd.h>
struct Vertex {
    vector_float2 position;
    vector_float4 color;
};

#endif /* definitions_h */
