/*
*  QuickSort
*  MergeSort 같은 경우는 대용량을 처리하기 위해서 라면, Quick Sort 는 평균 실행시간을 줄이는 것이 목표
*  
*  => 원본 입력 배열을 작은 크기의 부분 배열로 나누고, 각 부분 배열을 정렬한후, 그 결과를 합쳐서 전체 정렬된 배열을 생성
*  
*  QuickSort (Pivot)
* [  [*]  ] 
*  1. 입력 배열을 두개의 배열 L 과 R 로 나눈다. L 은 입력 배열에서 P 보다 작거나 같은 원소를 포함하는 부분 배열, 
      R 은 P 보다 큰 원소를 포함하는 부분 배열
   2. 입력 배열을 L, P, R 과 같은 식으로 구성

   ex) [5][6][7][3][1][9][2][4][8]
   [5] is pivot

   => After quickSort
   [4][2][3][1]*[5]*[9][7][6][8]

   이러한 식으로 진행할때, Pivot 의 위치가 변경되는걸 확인!
   
   1. 입력 배열 A 가 두개 이상의 원소를 가지고 있다면, A 에 분할 연산 수행 => L 과 R 생성
   2. 1 단계 입력으로 L 을 사용하고
   3. 1 단계 입력으로 R 을 사용

   Step 2 와 step 3 는 Recursion Tree 로 빠르게 생성 가능

   ex) 
   [*5*][6][7][3][1][9]
         /            \
   [*5*][1][3]       [*7*][6][9]
     /      \           /     \
   [*3*][1] [5]      [*7*][6]  [9]
      / \    |          /  \    |
   [1]  [3] [5]      [6]   [7] [9]

   Algorithm    |  Best Case  |  Average  |  Worst
   MergeSort    |  O(nlogn)   |  O(nlogn) | O(nlogn)
   QuickSort    |  O(nlogn)   |  O(nlogn) | O(n^2)
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template<typename T>
auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    auto pivot_val = *begin;
    auto left_iter = begin + 1;
    auto right_iter = end;

    while (true)    
    {
        while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
            left_iter++;
        
        while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
            right_iter--;

        if (left_iter == right_iter)
            break;
        else
            std::iter_swap(left_iter, right_iter);
    }

    if (pivot_val > *right_iter)
        std::iter_swap(begin, right_iter);

    return right_iter;
}

template<typename T>
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    if (std::distance(begin, end) >= 1)
    {
        auto partition_iter = partition<T>(begin, end);
        quick_sort<T>(begin, partition_iter - 1);
        quick_sort<T>(partition_iter, end);
    }
}

template<typename T>
void print_vector(std::vector<T> arr)
{
    for (const auto& i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
}

void run_quick_sort_test()
{
    std::vector<int> test_iter{ 5, 6, 7, 3, 1, 9, 2, 4, 8 };
    //std::vector<int> s1{ 45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7 };
    //std::vector<float> s2{ 45.6f, 1.0f, 3.8f, 1.01f, 2.2f, 3.9f, 45.3f, 5.5f, 1.0f, 2.0f, 44.0f, 5.0f, 7.0f };
    //std::vector<double> s3{ 45.6, 1.0, 3.8, 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0 };
    //std::vector<char> c{ 'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y' };

    //print_vector(s1);
    //print_vector(s2);
    //print_vector(s3);
    //print_vector(c);
    std::cout << std::endl;

    quick_sort<int>(test_iter.begin(), test_iter.end() - 1);
    //quick_sort<int>(s1.begin(), s1.end() - 1);
    //quick_sort<float>(s2.begin(), s2.end() - 1);
    //quick_sort<double>(s3.begin(), s3.end() - 1);
    //quick_sort<char>(c.begin(), c.end() - 1);

    std::cout << std::endl;
    //print_vector<int>(s1);
    //print_vector<float>(s2);
    //print_vector<double>(s3);
    //print_vector<char>(c);
    std::cout << std::endl;
}

int main()
{
    run_quick_sort_test();
    return 0;
}