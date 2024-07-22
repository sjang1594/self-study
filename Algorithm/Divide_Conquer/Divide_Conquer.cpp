/*알고리즘 문제에서의 시간복잡도
* 
* 알고리즘에서 결국에는 Polynomial Time 알고리즘을 이용해서, 솔루션을 구한다고 했을때 이러한 문제를 계산하는데에 복잡도를 P 문제라고 한다.
* 
* 1. NP (Non-Deterministic Polynomial Time) 문제는 특정 솔루션을 다항 시간으로 검증 이가능하지만, 알려진 다항 시간 솔루션이 없다.
* 2. EXPTIME (Exponential Time) 문제는 입력크기에 대한 지수 함수 형태의 시간 복잡도 솔루션을 가진다.
* 3. PSPACE (Polynomial Space) 문제는 다항식 크기의 공간이 필요한 문제 이다.
* 
* P 가 결국에는 NP 에 들어가는 문제인지 확인이 주요한 문제
* 
* Devide & Conquer 페러다임
* 결국에는 주어진 문제를 작은 부분 문제로 나눠서, 각 나눠져있는 작은 부분들의 솔루션을 구하고, 
* 각 솔루션을 합치고 전체 문제에 대한 솔루션을 구하는 방식
* 
* 예: Binary Search Tree, Quick Sort, Merge Sort, Matrix Multiplication, Fast Fourier Transform, Skyline Algorithm
*/

/* Binary Search Tree
*  1. Linear 하게, 원소 N 이 같은지 확인 (Linear Search Tree)
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