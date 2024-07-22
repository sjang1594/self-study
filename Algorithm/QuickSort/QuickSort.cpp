/*
*  QuickSort
*  MergeSort ���� ���� ��뷮�� ó���ϱ� ���ؼ� ���, Quick Sort �� ��� ����ð��� ���̴� ���� ��ǥ
*  
*  => ���� �Է� �迭�� ���� ũ���� �κ� �迭�� ������, �� �κ� �迭�� ��������, �� ����� ���ļ� ��ü ���ĵ� �迭�� ����
*  
*  QuickSort (Pivot)
* [  [*]  ] 
*  1. �Է� �迭�� �ΰ��� �迭 L �� R �� ������. L �� �Է� �迭���� P ���� �۰ų� ���� ���Ҹ� �����ϴ� �κ� �迭, 
      R �� P ���� ū ���Ҹ� �����ϴ� �κ� �迭
   2. �Է� �迭�� L, P, R �� ���� ������ ����

   ex) [5][6][7][3][1][9][2][4][8]
   [5] is pivot

   => After quickSort
   [4][2][3][1]*[5]*[9][7][6][8]

   �̷��� ������ �����Ҷ�, Pivot �� ��ġ�� ����Ǵ°� Ȯ��!
   
   1. �Է� �迭 A �� �ΰ� �̻��� ���Ҹ� ������ �ִٸ�, A �� ���� ���� ���� => L �� R ����
   2. 1 �ܰ� �Է����� L �� ����ϰ�
   3. 1 �ܰ� �Է����� R �� ���

   Step 2 �� step 3 �� Recursion Tree �� ������ ���� ����

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