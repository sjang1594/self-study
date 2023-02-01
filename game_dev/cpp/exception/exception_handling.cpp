#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int firstFindChar(const char* string, char ch)
{
    for (std::size_t index = 0; index < strlen(string); ++index)
        if (string[index] == ch)
            return index;
    return -1; // no match
}

double divide(int x, int y, bool& success)
{
    if (y == 0)
    {
        success = false;
        return 0.0;
    }

    success = false;
    return static_cast<double>(x) / y;
}

int main()
{
    // This is convention
    /*bool success;
    double result = divide(5, 3, success);
    if (!success)
        std::cerr << "An error occured" << std::endl;
    else
        std::cout << "Result is " << result << std::endl;

    std::ifstream input_file("temp.text");
    if (!input_file)
        std::cerr << "Cannot open file" << std::endl;*/
    
    // try, catch, throw
    double x;
    cin >> x;
    try
    {
        if (x < 0.0) throw std::string("Negative input");
        cout << std::sqrt(x) << endl;
    }
    catch (int x)
    {
        cout << x << endl;
    }
    catch (std::string error_message)
    {
        // do something to respond
        cout << error_message;
    }
    
    return 0;
}