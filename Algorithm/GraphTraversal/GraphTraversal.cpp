/*
*  Graph �� Vertex �� ���հ� Edge �� �������� �����ǰ�, G = <V, E> ���������� ǥ���� �Ѵ�.
*  Graph �� Edge �� ���⼺�� ������ �ִٸ�, directed graph, �׷��� ������ undirected graph
*  �� Edge �� weight ������ �ִٸ�, weighted grapph, �׷��� �ʴٰ� �ϸ� unweighted.
* 
*  Graph �� �ڷᱸ����? �´�. (Tree �Ǵ� Link List ó�� �ڷᱸ���� ���¸� ������ �ִ�.)
*  ���ſ��� �̷��� Graph �� ������ Finite State Machine �� ���ؼ�, ��ü�� ���� �Ǵ� ��ü�� �������� ǥ���ϱ⵵ �ߴ�.
* 
*  Graph Traversal Problem
*  � Ư�� Vertex ���� �����ؼ�, ������ ��� ������ �湮�ϴ� ����
*  
*  �� �� ������ Ǯ�����ؼ��� Graph Search Problem �� �Ϻκ��̴�. ���� �� � Ư�� ������ ã�ƾ� �ϱ� ������.
* 
*  BFS (Breadth First Search): �ʺ� �켱 Ž��
* 
*  ù ������ (Vertex) �� ���� ������ Vertex �� ã�´�. ù �������� �湮�� �������� �ΰ�, ������ ������ ������ ���캼 �����̴�.
*  �� ���� ������ �������� � ������ ��� ���� ã�ư���, �湮�� ������ Marking �Ѵ�. ���� ���� Tree Level ������ �� �湮�ؾ��Ѵ�.
*  �̰� �ݺ������� �����Ѵ�.
* 
*  �� ���⼭ �߿��� �κ��� �ڽ��� ���ʷ� ����, �״��� GrandChildren �� ���ٴ°�.
*/

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>

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
auto breadth_first_search(const Graph<T>& G, unsigned start)
{
    queue<unsigned> queue;
    set<unsigned> visited;
    vector<unsigned> visited_order;
    queue.push(start);

    while (!queue.empty())
    {
        auto current_vertex = queue.front();
        queue.pop();

        // set �̶�°���, ���� ���� Vertex �� ���ٰ� �Ѵٸ�...
        if (visited.find(current_vertex) == visited.end())
        {
            visited.insert(current_vertex);
            visited_order.emplace_back(current_vertex);

            for (auto& e : G.edges(current_vertex))
            {
                if (visited.find(e.dst) == visited.end())
                {
                    queue.push(e.dst);
                }
            }
        }
    }

    return visited_order;
}

int main()
{
    using T = unsigned;
    auto G = create_reference_graph<T>();
    cout << G << endl;

    auto bfs_visited_order = breadth_first_search(G, 1);
    for (auto v : bfs_visited_order)
        cout << v << endl;
    return 0;
}