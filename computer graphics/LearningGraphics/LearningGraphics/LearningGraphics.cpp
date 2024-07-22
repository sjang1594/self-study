// GLM

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <directxmath/DirectXMath.h>

using namespace std;

int main()
{
	/* Basics on GLM */

	glm::vec3 a(1.0f, 2.0f, 3.0f);
	glm::vec3 b(7.0f, 8.0f, 9.0f);

	// (6, 6, 6);
	auto c = b - a; // Operator -
	cout << glm::to_string(c) << endl;

	// vector + / -
	cout << " a = " << glm::to_string(a) << endl;
	cout << " b  = " << glm::to_string(b) << endl;
	cout << " b - a = " << glm::to_string(c) << endl;

	// then scalar multiplication
	glm::vec3  d = a * 2.0f;

	cout << " c = a * 2.0f = " << glm::to_string(d) << endl;

	// vector length
	float l = glm::length(d);

	return 0;
} 