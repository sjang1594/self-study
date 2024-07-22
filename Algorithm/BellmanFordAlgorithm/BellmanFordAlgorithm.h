/* BellmanFordAlgorithm
*  
*  Dijkstra Algorithm 의 취약점
*  ** Weight 가 음수이면, Weight 의 총합이 아무리 적더라도, Vertex 와 Vertex 의 사이의 Edge 의 Weight 에 따라서, 결과값이 다르게 나올것이다. (Greedy)
*  
*  이것을 해결하는게, 바로 Bellman-Ford Algorithm
*  특히 음수 가중치를 정의를 해야할때는, 앞서 말했듯이 Dijkstra 에서는 그다음 최대 총합을 계산을 할지를 모른다.
*  
*  Bellman-ford 는 Greedy 선택을 (V-1) 번 반복한다.
*  그말은 즉슨 모든 Edge 들의 Weight 를 한번씩 체크 한다는것!
*  
*  Time Complexity
*  O(v * e)
*  
* ---------------------------------------------------------------------
*  음수 Cycle 이 생길 경우
*  예를 들어서 총합이 -8 + 3 + 3 이라는 Cycle 이 생긴다면? 
*  이러면 결국엔, Code 의 로직상으로는 문제가 없다. 하지만 결과 값은 아닐수도 있다.
*  
*/

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Edge
{
    int src;
    int dst;
    int weight;
};

bool isNegativeCycle(std::vector<int>& vec, std::vector<Edge>& edges)
{
    for (auto& e : edges)
    {
        if (vec[e.src] == INT_MAX)
            continue;
        if (vec[e.dst] > vec[e.src] + e.weight)
        {
            return true;
        }
    }
    return false;
}

vector<int> BellmanFord(vector<Edge> edges, int V, int start)
{
    vector<int> distance(V, INT_MAX);
    distance[start] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        for (auto& e : edges)
        {
            if (distance[e.src] == INT_MAX)
                continue;

            if (distance[e.dst] > distance[e.src] + e.weight)
            {
                distance[e.dst] = distance[e.src] + e.weight;
            }
        }
    }

    if (isNegativeCycle(distance, edges))
    {
        return {};
    }
    return distance;
}

