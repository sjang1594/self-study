// MapReduce.cpp 

// STL Function
// std::binary_search()     : 이진 검색을 이용하여 컨테이너에서 원소를 찾습니다.
// std::search()            : 컨테이너에서 일련의 원소들을 찾습니다.
// std::upper_bound()       : 컨테이너에서 주어진 값보다 큰 원소가 나타나기 시작하는 위치의 Iterator return
// std::lower_bound()       : 컨테이너에서 주어진 값도다 작은 원소가 나타나기 시작하는 위치의 Iterator return
// std::partition()         : 분할 연산을 수행하고, 주어진 Pivot 보다 작은 원소는 Pivtot 왼쪽으로 옮기고, 크면 오른쪽으로 옮김
// std::partition_copy()    : 분할 연산을 수행하고, 그결과를 별도의 두 배열로 반환
// std::is_partitioned()    : 주어진 피벗을 기준으로 분할이 되어있는지 검사
// std::stable_partition()  : 분할 연산을 수행하여, 각 파티션 원소는 원본 순서를 유지
// std::sort()              : 컨테이너 원소를 정렬 (Quick Sort)
// std::stable_sort()       : 위의 내용처럼 정렬은 하지만, 서로 순위가 같은 원소에 대해 원본 순서가 변경되지 않도록 정렬
// std::partial_sort()      : 컨테이너 전체가 아니라 일부 구간에 대해서 정렬
// std::merge()             : 두개의 컨테이너를 합칩니다.
// std::nth_element()       : 컨테이너에서 n 번째로 작은 원소를 반환
// std::accumulate()        : 컨테이너 원소의 누적 합을 계산한다.
// std::transform()         : 컨테이너와 함수가 주어지면, 컨테이너의 모든 원소에대해 값을 수정
// std::reduce()            : 지정한 범위의 원소에 대해 리듀스 연산을 수행하고 결과를 반환

// 어떠한 Map Container C 를 받아서, 모든 원소에 f(x) 만큼을 적용하는 연산
// MapReduce 는 크게 Map() 함수와 Reduce() 함수로 구성되어있고, 이 두 기능을 합친 이름
// * Map 함수는 분활한 데이터를 가공하는 Apply 기능 수행
// * reduce 함수는 map() 함수로 가공한 데이터를 어떤 기준에 따라 데이터를 하나로 다시 병합하는 Combine 역활

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