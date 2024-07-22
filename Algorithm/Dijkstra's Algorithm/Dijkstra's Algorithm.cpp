/* Dijkstra's Algorithm
*  
*  �־��� �׷��� G = <V, E> �� �ִ�. V �� Vertex �� ����, E �� Edge �� ����. ������ Edge �� Weight �� ��� �ְ�, 
*  ���� ���� (Source Vertex) �� ���� ���� (Destination Vertex) �־�����, ���� ��������, ���� �������� �̾����� �ּ� ��� ��θ� ���Ͻÿ�
* 
*  Dijkstra's Algorithm Ư¡
*  1. ���� ����ġ�� ���� Graph ���� �����ϰ�, Prim's MST Algorithm �� ������ �����̴�.
*  2. Prim's ������ �ּ� �Ÿ��� ������ �Ÿ������� ���������, Dijkstra Algorithm ������ ������������ ������ �� ���������� �� �Ÿ��� ���
*  3. Dijkstra Algorithm �� ���� �������� ��Ÿ���� ����, Prims' �� ��� Vertex �� �� ��ȸ�ؾ��Ѵ�.
* 
*  ---------- Algorithm ----------
*  1. ��� ������ �Ÿ����� ���Ѵ�� �ʱ�ȭ, �ڱ� �ڽű����� �Ÿ��� 0 ���� �ʱ�ȭ 
*  2. �ּ� �� H �� ���� ������ �ϳ� ������, �� ������ U ��� ������, U �� ���� �������� ���� ����������̰�, ���� U �� ���� �����̸� �˰��� ����
*  3. U �� ������ ��� ���� V �� ����, ���� V �� �Ÿ����� (U �� �Ÿ��� + (U, V) Edge Weight) ���� ũ��, V ���� �ٴٸ��� �� ª�� �� ��θ� ã�����Ƿ�, 
*     V �� �Ÿ����� (U �� �Ÿ��� + (U, V) Edge weight)
*  4. �湮���� ���� ������ �����ִٸ�, �ٽ� 2 �ܰ�� �Ѿ��.
*  5. �ּ� �� H ���� ���� ������ ���� �����̶�� �Ѵٰ� �ϸ� �˰��� ����
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

        // ���������.. 
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
