#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

void goodBye(const string& s)
{
	cout << "Good Bye " << s << endl;
}

class Object
{
public:
	void hello(const string& s)
	{
		cout << "Hello " << s << endl;
	}
};

int main()
{
	// lambda -introducer
	// lambda-parameter-declaration
	// lambda-return-type-clause
	// compound-statement
	auto func = [](const int& i) -> void {cout << "Hello, World!" << endl; };
	// func = [](const int& i) -> void {cout << "Hello, World!" << endl; }();
	func(123);

	{
		string name = "JackJack";
		[&name]() {std::cout << name << endl; }();
	}

	vector<int> v;
	v.push_back(1);
	v.push_back(2);

	auto func2 = [](int val) {cout << val << " "; };
	for_each(v.begin(), v.end(), func2);
	cout << endl;
	cout << []() -> int {return 1; }() << endl;

	std::function<void(int)> func3 = func2;
	func3(123);

	std::function<void()>func4 = std::bind(func3, 456);
	func4();

	{
		Object instance;
		auto f = std::bind(&Object::hello, &instance, std::placeholders::_1);

		f(string("World"));

		auto f2 = std::bind(&goodBye, std::placeholders::_1);
		f2(string("World"));
	}
	return 0;
}