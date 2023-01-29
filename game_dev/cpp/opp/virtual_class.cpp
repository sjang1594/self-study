#include <iostream>
using namespace std;

class PoweredDevice
{
public:
    int m_i;

    PoweredDevice(int power)
    {
        cout << "PowerDevice:" << power << endl;
    }
};

class Scanner : virtual public PoweredDevice
{
public:
    Scanner(int scanner, int power)
        : PoweredDevice(power)
    {
        cout << "Scanner" << scanner << endl;
    }
};

class Printer : virtual public PoweredDevice
{
public:
    Printer(int printer, int power)
        : PoweredDevice(power)
    {
        cout << "Printer" << printer << endl;
    }
};

class Copier : public Printer, public Scanner
{
public:
    Copier(int scanner, int printer, int power)
        : Scanner(scanner, power), Printer(printer, power), PoweredDevice(power)
    {
        cout << "Copier" << scanner << printer << endl;
    }
};

int main()
{
    Copier cop(1, 2, 3);
    cout << &cop.Scanner::PoweredDevice::m_i << endl;
    cout << &cop.Printer::PoweredDevice::m_i << endl;
    return 0;
}