#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp> // cout 출력을 위한 string_cast()

#include <glm/gtc/matrix_inverse.hpp> // inverseTranspose
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> // translate, rotate, scale

#include <iostream>

// 일반적으로 .cpp 파일에서 using namespace를 사용하는 것은 괜찮습니다.
using namespace std; // cout, endl;
using namespace glm;

int main() {
    /*
     * glm 설치
     * vcpkg install glm:x64-windows
     */

    // glm::mat2 (2x2 column-major matrix)
    mat2 A = mat2(1, 2, 3, 4);

    cout << to_string(A) << endl;
    // mat2x2((1.000000, 2.000000),
    //        (3.000000, 4.000000))
    // 우리가 생각하는 행렬 (column-major)
    // |1 3|
    // |2 4|

    cout << to_string(transpose(A)) << endl;
    // mat2x2((1.000000, 3.000000),
    //        (2.000000, 4.000000))

    cout << to_string(A[1]) << endl;
    // vec2(3.000000, 4.000000)

    mat2 B = mat2(5, 6, 7, 8);

    mat2 C = A + B;

    cout << to_string(C) << endl;

    // mat2x2((6.000000, 8.000000),
    //	      (10.000000, 12.000000))

    cout << to_string(A * B) << endl;
    // mat2x2((23.000000, 34.000000), (31.000000, 46.000000))

    cout << to_string(B * A) << endl;
    // mat2x2((19.000000, 22.000000), (43.000000, 50.000000))

    // glm::mat4 (column-major)
    mat4 m = mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    // mat4x4((1.000000, 2.000000, 3.000000, 4.000000),
    //        (5.000000, 6.000000, 7.000000, 8.000000),
    //        (9.000000, 10.000000, 11.000000, 12.000000),
    //        (13.000000, 14.000000, 15.000000, 16.000000))
    // 우리가 생각하는 행렬 (column-major)
    // |1 5  9 13|
    // |2 6 10 14|
    // |3 7 11 15|
    // |4 8 12 16|

    m *= 10.0f;
    m = 2.0f * m + m;

    mat4 translation = translate(vec3(1.0f, 2.0f, 3.0f));
    // mat4x4((1.000000, 0.000000, 0.000000, 0.000000),
    //        (0.000000, 1.000000, 0.000000, 0.000000),
    //        (0.000000, 0.000000, 1.000000, 0.000000),
    //        (1.000000, 2.000000, 3.000000, 1.000000))
    // 우리가 생각하는 Matrix
    // |1 0 0 0|
    // |0 1 0 0|
    // |0 0 1 0|
    // |1 2 3 1|

    // GLM 에서 해주는건 Column Major
    // |1 0 0 1|
    // |0 1 0 2|
    // |0 0 1 3|
    // |0 0 0 1|

    // Diret-X Row Major
    // |1 0 0 0|
    // |0 1 0 0|
    // |0 0 1 0|
    // |1 2 3 1|


    // 메모리에 어떤 순서로 저장되는지 확인
    // cout << "Transtion Matrix" << endl;
    // for (int i = 0; i < 16; i++) {
    //     cout << ((float *)&translation)[i] << " ";
    // }
    // cout << endl;
    // 출력결과: 1 0 0 0 0 1 0 0 0 0 1 0 1 2 3 1

    cout << to_string(translation) << endl;
    // mat4x4((1.000000, 0.000000, 0.000000, 0.000000),
    //        (0.000000, 1.000000, 0.000000, 0.000000),
    //        (0.000000, 0.000000, 1.000000, 0.000000),
    //        (1.000000, 2.000000, 3.000000, 1.000000))
    // Column-Major (GLM)
    // |1 0 0 1|
    // |0 1 0 2|
    // |0 0 1 3|
    // |0 0 0 1|
    // Row-Major (DX)
    // |1 0 0 0|
    // |0 1 0 0|
    // |0 0 1 0|
    // |1 2 3 1|

    vec4 myPoint = vec4(4, 5, 6, 1);
    vec4 myVector = vec4(4, 5, 6, 0);

    cout << to_string(translation * myPoint) << endl;
    // vec4(5.000000, 7.000000, 9.000000, 1.000000)

    cout << to_string(translation * myVector) << endl;
    // vec4(4.000000, 5.000000, 6.000000, 0.000000)

    cout << to_string(glm::inverse(translation)) << endl;
    // mat4x4((1.000000, -0.000000, 0.000000, -0.000000),
    //        (-0.000000, 1.000000, -0.000000, 0.000000),
    //        (0.000000, -0.000000, 1.000000, -0.000000),
    //        (-1.000000, -2.000000, -3.000000, 1.000000))

    // 회전축 X 에 대해서
    mat4 rotationX = rotate(glm::pi<float>() / 3.0f, vec3(1.0f, 0.0f, 0.0f));
    cout << to_string(rotationX) << endl;
    // mat4x4((1.000000, 0.000000, 0.000000, 0.000000),
    //        (0.000000, 0.500000, 0.866025, 0.000000),
    //        (0.000000, -0.866025, 0.500000, 0.000000),
    //        (0.000000, 0.000000, 0.000000, 1.000000))

    cout << to_string(glm::transpose(rotationX)) << endl;
    // mat4x4((1.000000, 0.000000, 0.000000, 0.000000),
    //        (0.000000, 0.500000, -0.866025, 0.000000),
    //        (0.000000, 0.866025, 0.500000, 0.000000),
    //        (0.000000, 0.000000, 0.000000, 1.000000))

    // 회전 행렬의 전치 행렬은 회전의 역행렬과 동일합니다.
    cout << to_string(glm::transpose(rotationX) * rotationX) << endl;
    // mat4x4((1.000000, 0.000000, 0.000000, 0.000000),
    //        (0.000000, 1.000000, 0.000000, 0.000000),
    //        (0.000000, 0.000000, 1.000000, 0.000000),
    //        (0.000000, 0.000000, 0.000000, 1.000000))

    // 순서 주의: 회전 후 이동
    cout << to_string((translation * rotationX) * vec4(1.0f, 0.0f, 0.0f, 1.0f))
         << endl;
    // vec4(2.000000, 2.000000, 3.000000, 1.000000)

    // 순서 주의: 이동 후 회전
    cout << to_string((rotationX * translation) * vec4(1.0f, 0.0f, 0.0f, 1.0f))
         << endl;
    // vec4(2.000000, -1.598076, 3.232051, 1.000000)

    // Transpose로 row-major로 변경가능
    cout << to_string(vec4(1.0f, 0.0f, 0.0f, 1.0f) *
                      glm::transpose(translation * rotationX))
         << endl;
    // vec4(2.000000, 2.000000, 3.000000, 1.000000)

    cout << to_string(glm::scale(vec3(0.5f, 1.0f, 2.0f))) << endl;
    // mat4x4((0.500000, 0.000000, 0.000000, 0.000000),
    //        (0.000000, 1.000000, 0.000000, 0.000000),
    //        (0.000000, 0.000000, 2.000000, 0.000000),
    //        (0.000000, 0.000000, 0.000000, 1.000000))
}
