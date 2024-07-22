#include <iostream>
#include <exception>

class CustomException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Custom exception";
    }
};

int main()
{
    try
    {
        std::string s;
        s.resize(-1);

        // throw std::runtime_error("Bad thing Happened");
        throw CustomException();
    }
    catch(std::length_error & e)
    {
        std::cerr << "Length Error" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << typeid(e).name() << std::endl;
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}