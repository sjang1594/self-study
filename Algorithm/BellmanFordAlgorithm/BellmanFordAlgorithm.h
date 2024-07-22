/* BellmanFordAlgorithm
*  
*  Dijkstra Algorithm �� �����
*  ** Weight �� �����̸�, Weight �� ������ �ƹ��� ������, Vertex �� Vertex �� ������ Edge �� Weight �� ����, ������� �ٸ��� ���ð��̴�. (Greedy)
*  
*  �̰��� �ذ��ϴ°�, �ٷ� Bellman-Ford Algorithm
*  Ư�� ���� ����ġ�� ���Ǹ� �ؾ��Ҷ���, �ռ� ���ߵ��� Dijkstra ������ �״��� �ִ� ������ ����� ������ �𸥴�.
*  
*  Bellman-ford �� Greedy ������ (V-1) �� �ݺ��Ѵ�.
*  �׸��� �ｼ ��� Edge ���� Weight �� �ѹ��� üũ �Ѵٴ°�!
*  
*  Time Complexity
*  O(v * e)
*  
* ---------------------------------------------------------------------
*  ���� Cycle �� ���� ���
*  ���� �� ������ -8 + 3 + 3 �̶�� Cycle �� ����ٸ�? 
*  �̷��� �ᱹ��, Code �� ���������δ� ������ ����. ������ ��� ���� �ƴҼ��� �ִ�.
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

