/* Dijkstra's Algorithm
*  
*  주어진 그래프 G = <V, E> 가 있다. V 는 Vertex 의 집합, E 는 Edge 의 집합. 각각의 Edge 는 Weight 를 들고 있고, 
*  시작 정점 (Source Vertex) 과 목적 정점 (Destination Vertex) 주어질때, 시작 정점에서, 목적 정점까지 이어지는 최소 비용 경로를 구하시오
* 
*  Dijkstra's Algorithm 특징
*  1. 음수 가중치가 없는 Graph 에서 동작하고, Prim's MST Algorithm 을 변형한 형태이다.
*  2. Prim's 에서는 최소 거리를 정점의 거리값으로 계산하지만, Dijkstra Algorithm 에서는 시작정점으로 부터의 각 정점까지의 총 거리를 계산
*  3. Dijkstra Algorithm 은 목적 정점까지 나타나면 종료, Prims' 는 모든 Vertex 를 다 순회해야한다.
* 
*  ---------- Algorithm ----------
*  1. 모든 정점의 거리값을 무한대로 초기화, 자기 자신까지의 거리는 0 으로 초기화 
*  2. 최소 힙 H 로 부터 정점을 하나 꺼내고, 이 정점을 U 라고 했을때, U 는 시작 정점에서 가장 가까운정점이고, 만약 U 가 목적 정점이면 알고리즘 종료
*  3. U 와 인접한 모든 정점 V 에 대해, 만약 V 의 거리값이 (U 의 거리갑 + (U, V) Edge Weight) 보다 크면, V 까지 다다르는 더 짧은 은 경로를 찾았으므로, 
*     V 의 거리값을 (U 의 거리갑 + (U, V) Edge weight)
*  4. 방문하지 않은 정점이 남아있다면, 다시 2 단계로 넘어간다.
*  5. 최소 힙 H 에서 꺼낸 정점이 목적 정점이라고 한다고 하면 알고리즘 종료
*/

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <limits>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T>
struct Edge
{
    unsigned src;
    unsigned dst;
    T weight;
};

template <typename T>
class Graph
{
public:
    Graph(unsigned N) : V(N) {}

    auto vertices() const { return V; }

    vector<Edge<T>>& edges() const { return edge_list; }

    vector<Edge<T>> edges(unsigned v) const
    {
        vector<Edge<T>> edges_from_v;
        for (auto& e : edge_list)
        {
            if (e.src == v) edges_from_v.emplace_back(e);
        }

        return edges_from_v;
    }

    void add_edge(Edge<T>&& e)
    {
        if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
            edge_list.emplace_back(e);
        else
            std::cerr << "Error" << std::endl;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Graph<U>& G)
    {
        for (unsigned i = 1; i < G.vertices(); i++)
        {
            os << i << ":\t";
            auto edges = G.edges(i);
            for (auto& e : edges)
                os << "{" << e.dst << ": " << e.weight << "}, ";
            os << std::endl;
        }

        return os;
    }

private:
    unsigned V;
    vector<Edge<T>> edge_list;
};

template<typename T>
Graph<T> create_reference_graph()
{
    Graph<T> G(9);

    std::map<unsigned, std::vector<std::pair<unsigned, T>>> edge_map;
    edge_map[1] = { {2,0}, {5,0} };
    edge_map[2] = { {1,0}, {5,0}, {4,0} };
    edge_map[3] = { {4,0}, {7,0} };
    edge_map[4] = { {2,0}, {3,0}, {5,0}, {6,0}, {8,0} };
    edge_map[5] = { {1,0}, {2,0}, {4,0}, {8,0} };
    edge_map[6] = { {4,0}, {7,0}, {8,0} };
    edge_map[7] = { {3,0}, {6,0} };
    edge_map[8] = { {4,0}, {5,0}, {6,0} };

    for (auto& i : edge_map)
        for (auto& j : i.second)
            G.add_edge(Edge<T>{ i.first, j.first, j.second });
    return G;
}

template<typename T>
struct Label
{
    unsigned ID;
    T distance;
    inline bool operator > (const Label<T>& l) const
    {
        return this->distance > l.distance;
    }
};

template<typename T>
auto dijkstra_shortest_path(const Graph<T>& G, unsigned src, unsigned dst)
{
    priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;

    vector<T> distance(G.vertices(), numeric_limits<T>::max());

    set<unsigned> visited;
    vector<unsigned> parent(G.vertices());

    heap.emplace(Label<T>{src, 0});
    parent[src] = src;

    while (!heap.empty())
    {
        auto current_vertex = heap.top();
        heap.pop();

        // 목적지라면.. 
        if (current_vertex.ID == dst)
        {
            break;
        }

        if (visited.find(current_vertex.ID) == visited.end())
        {
            for (auto& e : G.edges(current_vertex.ID))
            {
                auto neighbor = e.dst;
                auto new_distance = current_vertex.distance + e.weight;

                if (new_distance < distance[neighbor])
                {
                    heap.emplace(Label<T>{neighbor, new_distance});
                    parent[neighbor] = current_vertex.ID;
                    distance[neighbor] = new_distance;
                }
            }

            visited.insert(current_vertex.ID);
        }
    }

    vector<unsigned> shortest_path;
    auto current_vertex = dst;

    while (current_vertex != src)
    {
        shortest_path.push_back(current_vertex);
        current_vertex = parent[current_vertex];
    }

    shortest_path.push_back(src);
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}


int main()
{
    using T = unsigned;
    auto G = create_reference_graph<T>();
    cout << G << endl;

    auto shortest_path = dijkstra_shortest_path<T>(G, 1, 6);
    for (auto& e : shortest_path)
    {
        cout << e << endl;
    }
    return 0;
}
