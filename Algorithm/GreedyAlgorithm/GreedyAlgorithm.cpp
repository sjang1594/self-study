/* GreedyAlgorithm. 
* 
*  '가장 좋아 보이는 해답' 을 선택하는 Algorithm. 
*  즉, 그리디 방법은 지역적인 최적의 해결 방법으로부터 전역적인 최적의 해결 방법을 구성하는 방식
*  예를 들어서 최단경로 찾는 알고리즘 (임의 두 지점을 선택 이후, 두 지점의 최단 이동거리를 구하는 방법
*  또는 하나 하나 Vertex 마다의 최단 거리를 구해서, 하나의 최단 거리를 만들어내는 알고리즘
*  - 출발 지점에서 아직 방문하지 않은 가장 가까운 지점까지 경로를 찾고, 목적 지점까지 다다를때까지 반복 (Dijkstra Algorithm)
* 
*  Greedy Algorithm 을 사용할수 있는 환경
*  1. 최적 부분 구조 속성
*  2. 그리디 선택 속성
*  ==> 즉 이거 일때 알고리즘은 최적 greedy algorithm 이 된다. (단 Greedy 가 항상 맞다는건 아니다 => Dynamic Programming)
*  Ex: Minimum Spanning Tree, Shortest-Job-First Scheduling, knapsack problem (fractional)
* 
*  최단 작업 우선 스케줄링 (Shortest-Job-First Scheduling)
*  -> Story: 대기열에 N 명의 사람의 기다리고 있고, 창구는 한정적인 개수로 되어잇다. 그리고 대기열의 N 명의 사람들은 각각 다른 용무로 왔기 때문에
*  ->        각각 다르다. 그러므로 알고리즘의 목적은 창구들은 효율적으로 사람들의 시간을 고려하며, 평균 대기 시간을 줄여야 한다. 즉 대기 순서를 변경해야한다.
*  
*  Pi   a   b   c    d    e   f    g    h     Person 
*  Ai | 8 | 1 | 2 |  4 |  9 | 2  |  3 | 5  |  Ai 는 Person i 일 처리 시간
*  Wi | 0 | 8 | 9 | 11 | 15 | 24 | 26 | 29 |  Wi 는 Person i 가 기다리는 시간
* 
*  Average Time = 15.25 -> This is Sum(Wi) / # of process(8) => 122 / 8
*  Initial P0, => A0 = 0
* 
*  How to solve this 
*  
*  Order the ascending order for corresponding Ai to Pi.
*  
*  Pi   a   b   c    d    e    f    g    h    
*  Ai | 1 | 2 | 2 |  3 |  4 |  5 |  8 |  9 | 
*  Wi | 0 | 1 | 3 |  5 |  8 | 12 | 17 | 25 |
*  
*  Average Time = 71 / 8 => 8.875
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template<typename T>
auto compute_waiting_times(std::vector<T>& service_times)
{
    std::vector<T> W(service_times.size());
    W[0] = 0;

    for (auto i = 1; i < service_times.size(); i++)
        W[i] = W[i - 1] + service_times[i - 1];
    return W;
}

template<typename T>
void print_vector(std::vector<T>& v)
{
    for (auto& i : v) {
        std::cout.width(2);
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

template<typename T>
void compute_and_print_waiting_times(std::vector<T>& service_times)
{
    auto waiting_times = compute_waiting_times<int>(service_times);

    std::cout << " Process Time: ";
    print_vector<T>(service_times);

    std::cout << " Waiting Time: ";
    print_vector<T>(service_times);

    auto ave_waiting_times = std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();
    std::cout << " Average Waiting Times " << ave_waiting_times;
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    std::vector<int> service_times{ 8, 1, 2, 4, 9, 2, 3, 5 };
    compute_and_print_waiting_times<int>(service_times);

    std::sort(service_times.begin(), service_times.end());

    std::cout << std::endl;
    std::cout << "After Processed" << std::endl;
    compute_and_print_waiting_times(service_times);
    return 0;
}