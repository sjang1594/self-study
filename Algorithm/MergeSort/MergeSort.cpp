/* MergeSort
*  를 이야기 하전에, Divide & Conquere 접근 방법: 주어진 문제가 굉장히 규모가 크고 여러개의 스텝으로 쪼갤수 있다고 한다면, 이걸 작은 부분 문제로 인식!
*  
*  1. Divide: 주어진 문제를 동일한 방식으로 해결 할 수 있는 여러 부분 문제로 나눈다.
*  2. Conquer: 각 부분 문제에 대해서 해답을 구한다.
*  3. Combine: 각 부분 문제의 답을 결합해서 전체 문제를 구한다.
* 
*  Sorting Algorithm 구현 관련
*  1. 모든 데이터 타입에 대해서 동작해야한다. 정수, 실수 등의 자료형에 모두 사용할 수 있어야 하고, 심지어 C++ 구조체 또는 클래스에 대해서, 서로 다른 멤버를 기준
*     으로 정렬할 수 있어야 합니다.
* 
*  2. 정렬 알고리즘은 많은 양의 데이터를 처리할 수 있어야합니다. 즉, 컴퓨터의 메인 메모리보다 큰 용량의 데이터에 대해서도 동작해야한다.
* 
*  3. 정렬 알고리즘은 점근적 시간 복잡도 측면이나 실제 동작 시에 빠르게 동작 해야 합니다. 
* 
*  Ex: Quick Sort : std::sort()
*  
*  Merge Sort: 병합 정렬
*  
*  ex: [2][6][7][3][1][9][5][4][8]
*         /                \
*  [2][6][7][3]        [1][9][5][4][8]
*      /     |              |    \     \
*   [2][6] [7][3]       [1][9] [5][4]  [8]
*   /   |   /  |         /   |   /  /    |
* [2]  [6] [7] [3]     [1] [9] [5] [4] [8]
*  \    |   \   |        \   |   \   |   |
*  [2][6]   [3][7]     [1][9]   [4][5] [8]
*     \        |           |        /    /
*   [2][3][6][7]       [1][4][5][8][9]
*          \                /
*      [1][2][3][4][5][6][7][8][9]
*/

#include <iostream>
#include <iterator>
#include <vector>

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

void run_merge_sort_test()
{
    std::vector<int> test_array{ 2, 6, 7, 3, 1, 9, 5, 4, 8 };
    std::vector<int> s1{ 45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7 };
    std::vector<float> s2{ 45.6f, 1.0f, 3.8f, 1.01f, 2.2f, 3.9f, 45.3f, 5.5f, 1.0f, 2.0f, 44.0f, 5.0f, 7.0f };
    std::vector<double> s3{ 45.6, 1.0, 3.8, 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0 };
    std::vector<char> c{ 'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y' };

    print_vector(test_array);
    print_vector(s1);
    print_vector(s2);
    print_vector(s3);
    print_vector(c);
    std::cout << std::endl;
    
    auto sorted_test_array = merge_sort<int>(test_array);
    auto sorted_s1 = merge_sort<int>(s1);
    auto sorted_s2 = merge_sort<float>(s2);
    auto sorted_s3 = merge_sort<double>(s3);
    auto sorted_c = merge_sort<char>(c);

    std::cout << std::endl;
    print_vector<int>(sorted_test_array);
    print_vector<int>(sorted_s1);
    print_vector<float>(sorted_s2);
    print_vector<double>(sorted_s3);
    print_vector<char>(sorted_c);
}

int main()
{
    run_merge_sort_test();
    return 0;
}
