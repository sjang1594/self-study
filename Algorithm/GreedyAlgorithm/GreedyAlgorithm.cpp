/* GreedyAlgorithm. 
* 
*  '���� ���� ���̴� �ش�' �� �����ϴ� Algorithm. 
*  ��, �׸��� ����� �������� ������ �ذ� ������κ��� �������� ������ �ذ� ����� �����ϴ� ���
*  ���� �� �ִܰ�� ã�� �˰��� (���� �� ������ ���� ����, �� ������ �ִ� �̵��Ÿ��� ���ϴ� ���
*  �Ǵ� �ϳ� �ϳ� Vertex ������ �ִ� �Ÿ��� ���ؼ�, �ϳ��� �ִ� �Ÿ��� ������ �˰���
*  - ��� �������� ���� �湮���� ���� ���� ����� �������� ��θ� ã��, ���� �������� �ٴٸ������� �ݺ� (Dijkstra Algorithm)
* 
*  Greedy Algorithm �� ����Ҽ� �ִ� ȯ��
*  1. ���� �κ� ���� �Ӽ�
*  2. �׸��� ���� �Ӽ�
*  ==> �� �̰� �϶� �˰����� ���� greedy algorithm �� �ȴ�. (�� Greedy �� �׻� �´ٴ°� �ƴϴ� => Dynamic Programming)
*  Ex: Minimum Spanning Tree, Shortest-Job-First Scheduling, knapsack problem (fractional)
* 
*  �ִ� �۾� �켱 �����ٸ� (Shortest-Job-First Scheduling)
*  -> Story: ��⿭�� N ���� ����� ��ٸ��� �ְ�, â���� �������� ������ �Ǿ��մ�. �׸��� ��⿭�� N ���� ������� ���� �ٸ� �빫�� �Ա� ������
*  ->        ���� �ٸ���. �׷��Ƿ� �˰����� ������ â������ ȿ�������� ������� �ð��� ����ϸ�, ��� ��� �ð��� �ٿ��� �Ѵ�. �� ��� ������ �����ؾ��Ѵ�.
*  
*  Pi   a   b   c    d    e   f    g    h     Person 
*  Ai | 8 | 1 | 2 |  4 |  9 | 2  |  3 | 5  |  Ai �� Person i �� ó�� �ð�
*  Wi | 0 | 8 | 9 | 11 | 15 | 24 | 26 | 29 |  Wi �� Person i �� ��ٸ��� �ð�
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