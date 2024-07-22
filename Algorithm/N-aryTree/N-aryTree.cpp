#include <iostream>
#include <vector>

// N Tree can have N chilren Node
struct nTree
{
    int data;
    std::vector<nTree*> children;
};

int main()
{
    std::cout << "Hello World!\n";
}