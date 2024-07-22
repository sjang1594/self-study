// MapReduce.cpp 

// STL Function
// std::binary_search()     : ���� �˻��� �̿��Ͽ� �����̳ʿ��� ���Ҹ� ã���ϴ�.
// std::search()            : �����̳ʿ��� �Ϸ��� ���ҵ��� ã���ϴ�.
// std::upper_bound()       : �����̳ʿ��� �־��� ������ ū ���Ұ� ��Ÿ���� �����ϴ� ��ġ�� Iterator return
// std::lower_bound()       : �����̳ʿ��� �־��� ������ ���� ���Ұ� ��Ÿ���� �����ϴ� ��ġ�� Iterator return
// std::partition()         : ���� ������ �����ϰ�, �־��� Pivot ���� ���� ���Ҵ� Pivtot �������� �ű��, ũ�� ���������� �ű�
// std::partition_copy()    : ���� ������ �����ϰ�, �װ���� ������ �� �迭�� ��ȯ
// std::is_partitioned()    : �־��� �ǹ��� �������� ������ �Ǿ��ִ��� �˻�
// std::stable_partition()  : ���� ������ �����Ͽ�, �� ��Ƽ�� ���Ҵ� ���� ������ ����
// std::sort()              : �����̳� ���Ҹ� ���� (Quick Sort)
// std::stable_sort()       : ���� ����ó�� ������ ������, ���� ������ ���� ���ҿ� ���� ���� ������ ������� �ʵ��� ����
// std::partial_sort()      : �����̳� ��ü�� �ƴ϶� �Ϻ� ������ ���ؼ� ����
// std::merge()             : �ΰ��� �����̳ʸ� ��Ĩ�ϴ�.
// std::nth_element()       : �����̳ʿ��� n ��°�� ���� ���Ҹ� ��ȯ
// std::accumulate()        : �����̳� ������ ���� ���� ����Ѵ�.
// std::transform()         : �����̳ʿ� �Լ��� �־�����, �����̳��� ��� ���ҿ����� ���� ����
// std::reduce()            : ������ ������ ���ҿ� ���� ���ེ ������ �����ϰ� ����� ��ȯ

// ��� Map Container C �� �޾Ƽ�, ��� ���ҿ� f(x) ��ŭ�� �����ϴ� ����
// MapReduce �� ũ�� Map() �Լ��� Reduce() �Լ��� �����Ǿ��ְ�, �� �� ����� ��ģ �̸�
// * Map �Լ��� ��Ȱ�� �����͸� �����ϴ� Apply ��� ����
// * reduce �Լ��� map() �Լ��� ������ �����͸� � ���ؿ� ���� �����͸� �ϳ��� �ٽ� �����ϴ� Combine ��Ȱ

// Input / Output : each a set of key/value pairs
// map (key_, value_) - > list (out_key, intermediate_value)


#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

template<typename T>
void print_vector(std::vector<T> arr)
{
    for (const auto& i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
}

void transform_test(std::vector<int> S)
{
    std::vector<int> Tr;
    print_vector(S);

    std::transform(S.begin(), S.end(), std::back_inserter(Tr), [](int x) { return std::pow(x, 2.0); });
    print_vector(Tr);

    /*std::for_each(S.begin(), S.end(), [](int& x) { x = std::pow(x, 2.0); });
    print_vector(S);*/
}

void reduce_test(std::vector<int> S)
{
    print_vector(S);

    auto ans = std::accumulate(S.begin(), S.end(), 0, [](int acc, int x) { return acc + x; });
    std::cout << ans << std::endl;
}

int main()
{
    std::vector<int> S{ 1, 10, 4, 7, 3, 5, 6, 9, 8, 2 };
    transform_test(S);
    reduce_test(S);
    return 0;
}