// LinearTimeSelection.cpp : This file contains the 'main' function. Program execution begins and ends there.


// Statement: 정렬되지 않은 원소의 집합 S 가 주어졌을때, i 번째로 작은 원소를 찾아야한다.
// 1. 입력 벡터 V 로 주어지면, 여기서 i 번째로 작은 원소를 찾는다.
// 2. 입력 벡터 V 를 v1, v2, v3, .. vn/5 로 분활을 한한다. 각 부분 벡터 Vi 는 다섯개의 Element 를 가지고 있고, 마지막 Vn/5 는 다섯개 이하의
//    원소를 가질수도 있다.
// 3. 각각의 Vi 를 정렬
// 4. 각각 Vi 에서의 중앙갑 mi 를 구하고, 이를 모아서 집합 M 을 생성
// 5. 집합 M 에서 중앙값 q 를 찾고
// 6. q 를 Pivot 으로 삼아서, V 를 L 과 R 로 분리


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
auto find_median(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last)
{
    // quick sort
    quick_sort<T>(begin, last);
    
    // find the median and return that middle iterator
    return begin + (std::distance(begin, last) / 2);
}

template<typename T>
auto partition_using_given_pivot(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end,
    typename std::vector<T>::iterator pivot)
{
    auto left_iter = begin;
    auto right_iter = end;

    while (true)
    {
        while (*left_iter < *pivot && left_iter != right_iter)
            left_iter++;
        while (*right_iter >= *pivot && left_iter != right_iter)
            right_iter--;

        if (left_iter == right_iter)
            break;
        else
            std::iter_swap(left_iter, right_iter);
    }

    if (*pivot > *right_iter)
        std::iter_swap(pivot, right_iter);
    return right_iter;
}

template<typename T>
typename std::vector<T>::iterator linear_time_select(
    typename std::vector<T>::iterator begin,
    typename std::vector<T>::iterator last,
    size_t i)
{
    auto size = std::distance(begin, last);
    if (size > 0 && i < size)
    {
        auto num_Vi = (size + 4) / 5;
        size_t j = 0;

        std::vector<T> M;
        for (; j < size / 5; j++)
        {
            auto b = begin + (j * 5);
            auto l = begin + (j * 5) + 5;
            std::cout << *l << std::endl;
            M.push_back(*find_median<T>(b, l));
        }

        if (j * 5 < size)
        {
            auto b = begin + (j * 5);
            auto l = begin + (j * 5) + (size % 5);
            M.push_back(*find_median<T>(b, l));
        }

        for (const auto& m : M)
        {
            std::cout << m << std::endl;
        }
        auto median_of_medians = (M.size() == 1) ? M.begin() : linear_time_select<T>(M.begin(), M.end() - 1, M.size() / 2);
        auto partition_iter = partition_using_given_pivot<T>(begin, last, median_of_medians);
        auto k = std::distance(begin, partition_iter) + 1;
        if (i == k)
            return partition_iter;
        else if (i < k)
            return linear_time_select<T>(begin, partition_iter - 1, i);
        else if (i > k)
            return linear_time_select<T>(partition_iter + 1, last, i - k);
    }
    else
    {
        return begin;
    }
}


template <typename T>
std::vector<T> merge(std::vector<T>& arr1, std::vector<T>& arr2)
{
    std::vector<T> merged;
    // std::vector<T>::iterator
    auto iter1 = arr1.begin();
    auto iter2 = arr2.begin();

    while (iter1 != arr1.end() && iter2 != arr2.end())
    {
        if (*iter1 < *iter2)
        {
            merged.emplace_back(*iter1);
            iter1++;
        }
        else
        {
            merged.emplace_back(*iter2);
            iter2++;
        }
    }

    // Happend if the size of either left or right vector is smaller than the opposite vector 
    if (iter1 != arr1.end())
    {
        for (; iter1 != arr1.end(); iter1++)
        {
            merged.emplace_back(*iter1);
        }
    }
    else
    {
        for (; iter2 != arr2.end(); iter2++)
        {
            merged.emplace_back(*iter2);
        }
    }

    return merged;
}

template<typename T>
std::vector<T> merge_sort(std::vector<T> arr)
{
    if (arr.size() > 1)
    {
        auto mid = size_t(arr.size() / 2);
        auto left_half = merge_sort<T>(std::vector<T>(arr.begin(), arr.begin() + mid));
        auto right_half = merge_sort<T>(std::vector<T>(arr.begin() + mid, arr.end()));
        return merge<T>(left_half, right_half);
    }

    return arr;
}

template<typename T>
void print_vector(std::vector<T> arr)
{
    for (const auto& i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
}

void run_linear_select_test()
{
    //std::vector<int> s1{ 45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7 };
    //std::cout << "Input Vector: " << std::endl;
    //print_vector<int>(s1);

    //std::cout << "Sorted Vector : " << std::endl;
    //print_vector<int>(merge_sort<int>(s1));
    
    std::vector<int> s1{ 1, 4, 8, 10, 12, 14, 16 };
    std::cout << *linear_time_select<int>(s1.begin(), s1.end() - 1, 3) << std::endl;

    //std::cout << " Third Element: " << *linear_time_select<int>(s1.begin(), s1.end() - 1, 3) << std::endl;
    //std::cout << " Fifth Element: " << *linear_time_select<int>(s1.begin(), s1.end() - 1, 5) << std::endl;
    //std::cout << " Eleventh Element: " << *linear_time_select<int>(s1.begin(), s1.end() - 1, 11) << std::endl;
}

int main()
{
    run_linear_select_test();
    return 0;
}