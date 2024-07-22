/* MergeSort
*  �� �̾߱� ������, Divide & Conquere ���� ���: �־��� ������ ������ �Ը� ũ�� �������� �������� �ɰ��� �ִٰ� �Ѵٸ�, �̰� ���� �κ� ������ �ν�!
*  
*  1. Divide: �־��� ������ ������ ������� �ذ� �� �� �ִ� ���� �κ� ������ ������.
*  2. Conquer: �� �κ� ������ ���ؼ� �ش��� ���Ѵ�.
*  3. Combine: �� �κ� ������ ���� �����ؼ� ��ü ������ ���Ѵ�.
* 
*  Sorting Algorithm ���� ����
*  1. ��� ������ Ÿ�Կ� ���ؼ� �����ؾ��Ѵ�. ����, �Ǽ� ���� �ڷ����� ��� ����� �� �־�� �ϰ�, ������ C++ ����ü �Ǵ� Ŭ������ ���ؼ�, ���� �ٸ� ����� ����
*     ���� ������ �� �־�� �մϴ�.
* 
*  2. ���� �˰����� ���� ���� �����͸� ó���� �� �־���մϴ�. ��, ��ǻ���� ���� �޸𸮺��� ū �뷮�� �����Ϳ� ���ؼ��� �����ؾ��Ѵ�.
* 
*  3. ���� �˰����� ������ �ð� ���⵵ �����̳� ���� ���� �ÿ� ������ ���� �ؾ� �մϴ�. 
* 
*  Ex: Quick Sort : std::sort()
*  
*  Merge Sort: ���� ����
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
