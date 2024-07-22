/*
*  Prim's Algorithm
*  
*  Minimum Spanning Tree Review
*  ���� ���� V �� ����ġ�� ���� Edge ���� E �� ������ �׷��� G = <V, E> �� �־�
*  ������, ��� ������ �����ϰ�, ����� Edge �� ����ġ ���� �ּ��� Ʈ�� T �� ���Ͻÿ�
* 
*  Kruskal Algorithm ���� �߿��ߴ���, union-find / Disjoint-set
*  �� ����Ŭ�� ������ �ʴ� �ּ� ����ġ ���� �̿�
* 
*  Prime's Algorithm => BFS �� ����
*  ����: ��踦 ������ �ϰ�, ��踦 �����ϴ� Edge �߿��� ���� ����ġ�� ���� Edge ����
*        ���� ���� Edge �߿���, ����� ������ �湮 ** 
* 
*  ---- �˰��� ���� ----
*  1. ��� ������ �Ÿ� ���� ���Ѵ�� �ʱ�ȭ �ϰ�, ���� �������� ��쿡�� �ڽű����� �Ÿ��� 0 ����
*     �׸��� ��� �Ÿ��� ���� �ּ� �� H �� �߰�
*  2. �ּ� Heap H �� ���� �����ϳ��� ������, �� ���� U �� MST �� �߰��ϰ�, ��� ������Ʈ
*  3. ��� ���� U �� ������ ��� ���� V �� ����, ���� V �� �Ÿ����� (U, V) �� ���� ����ġ���� ũ��, V �� �Ÿ����� (U, V)�� Edge ����ġ�� ����
*  4. �湮 ���� ���� ������ ���� �ִٸ� 2 �ܰ�� �̵�
* 
*  �� �� ����� Greedy ����̶�°�? ��?
* 
*  priority_queue �� �����ϴ°� Binary Heap => O(log N)
*  E * logV
* 
*  Binary Heap ���������
*  �ð� ���⵵�� O(E log V)
* 
*  Fibonnaci Heap
*  O (E + V*LogV)
* 
*  # of vertex V
*  # of edges E = V * (V - 1) / 2
* 
*  Prim's VS Kruskal
*  Kruskal �� �ּ� ����ġ �� ������ �ִ� Edge �� ���� �ؼ� MST �� ����
*  �ð����⵵�� O(ElogV)
*  Edge �� ������ ��������, �ð����⵵�� �ö󰡴ϱ� => Sparse Graph �� ���
*  
*  Prims �� �ƹ������̳� �����ص� �ǰ�
*  �ð����⵵�� O(ElogV), �ٸ� Heap ������ ����������, O(E + VLogV)
*  �ַ� Edge �� ������ ������, ���� Dense �� ���ȴ�.
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <limits>

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
    edge_map[1] = { {2,2}, {5,3} };
    edge_map[2] = { {1,2}, {5,5}, {4,1} };
    edge_map[3] = { {4,2}, {7,3} };
    edge_map[4] = { {2,1}, {3,2}, {5,2}, {6,4}, {8,5} };
    edge_map[5] = { {1,3}, {2,5}, {4,2}, {8,3} };
    edge_map[6] = { {4,4}, {7,4}, {8,1} };
    edge_map[7] = { {3,3}, {6,4} };
    edge_map[8] = { {4,5}, {5,3}, {6,1} };

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
vector<unsigned> prim_MST(const Graph<T>& G, unsigned src)
{
    priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;

    // distance ���� ��� Max �� �ʱ�ȭ
    vector<T> distance(G.vertices(), numeric_limits<T>::max());

    set<unsigned> visited;
    vector<unsigned> MST;

    // �ʱ� src ó�� �������� distance = 0 ���� �ʱ�ȭ
    heap.emplace(Label<T>{src, 0});

    while (!heap.empty())
    {
        auto current_vertex = heap.top();
        heap.pop();

        // BFS ���� (Vertex ID �� ����
        if(visited.find(current_vertex.ID) == visited.end())
        {
            MST.push_back(current_vertex.ID);

            for (auto& e : G.edges(current_vertex.ID))
            {
                auto neighbor = e.dst;
                auto new_distance = e.weight;

                if (new_distance < distance[neighbor])
                {
                    heap.emplace(Label<T>{neighbor, new_distance});
                    distance[neighbor] = new_distance;
                }
            }

            visited.insert(current_vertex.ID);
        }
    }

    return MST;
}

int main()
{
    using T = unsigned;
    auto G = create_reference_graph<T>();
    cout << G << endl;

    auto MST = prim_MST(G, 1);

    for (auto& v : MST)
    {
        cout << v << endl;
    }
    return 0;
}