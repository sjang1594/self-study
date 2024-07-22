/*�˰��� ���������� �ð����⵵
* 
* �˰��򿡼� �ᱹ���� Polynomial Time �˰����� �̿��ؼ�, �ַ���� ���Ѵٰ� ������ �̷��� ������ ����ϴµ��� ���⵵�� P ������� �Ѵ�.
* 
* 1. NP (Non-Deterministic Polynomial Time) ������ Ư�� �ַ���� ���� �ð����� ���� �̰���������, �˷��� ���� �ð� �ַ���� ����.
* 2. EXPTIME (Exponential Time) ������ �Է�ũ�⿡ ���� ���� �Լ� ������ �ð� ���⵵ �ַ���� ������.
* 3. PSPACE (Polynomial Space) ������ ���׽� ũ���� ������ �ʿ��� ���� �̴�.
* 
* P �� �ᱹ���� NP �� ���� �������� Ȯ���� �ֿ��� ����
* 
* Devide & Conquer �䷯����
* �ᱹ���� �־��� ������ ���� �κ� ������ ������, �� �������ִ� ���� �κе��� �ַ���� ���ϰ�, 
* �� �ַ���� ��ġ�� ��ü ������ ���� �ַ���� ���ϴ� ���
* 
* ��: Binary Search Tree, Quick Sort, Merge Sort, Matrix Multiplication, Fast Fourier Transform, Skyline Algorithm
*/

/* Binary Search Tree
*  1. Linear �ϰ�, ���� N �� ������ Ȯ�� (Linear Search Tree)
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iterator>
#include <algorithm>

bool linear_search(int N, std::vector<int>& sequence)
{
    for (const auto& i : sequence)
    {
        if (i == N) return true;
    }
    return false;
}

bool binary_search(int N, std::vector<int>& sequence)
{
    std::vector<int>::iterator first = sequence.begin();
    std::vector<int>::iterator last = sequence.end();

    while (true)
    {
        // Vector Size //
        int range_length = std::distance(first, last);
        int mid_element_index = *(first) + std::floor(range_length / 2);
        int mid_element = *(first + mid_element_index);

        if (mid_element == N)
            return true;
        else if (mid_element > N)
            std::advance(last, -mid_element_index);
        else
            std::advance(first, mid_element_index);

        if(range_length == 1)
            return false;
    }
}

void run_small_search_test()
{
    int N = 2;
    std::vector<int> sequence = { 1, 3, 2, 4, 5, 7, 9, 8, 6 };
    std::sort(sequence.begin(), sequence.end());


    if (binary_search(N, sequence))
        std::cout << "Found" << std::endl;
    else
        std::cout << "Not Found " << std::endl;

}

void run_large_search_test(int size, int N)
{
    std::vector<int> sequence;
    std::random_device rd;
    std::mt19937 rand(rd());

    std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

    for (auto i = 0; i < size; i++)
        sequence.emplace_back(uniform_dist(rand));

    std::sort(sequence.begin(), sequence.end());

    //*TIME BLOCK*//
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bool search_result = binary_search(N, sequence);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //***********//

    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution Time : " << diff.count() << std::endl;
}


int main()
{
    /*int N = 2;
    std::vector<int> sequence{ 1, 3, 2, 4, 5, 7, 9, 8, 6 };
    std::sort(sequence.begin(), sequence.end());

    if (binary_search(N, sequence))
        std::cout << "Found" << std::endl;
    else
        std::cout << "Not Found " << std::endl;

    return 0;*/
}