/* BipariteGraph
*  
*  �ΰ��� Vertex ���հ� �� Vertex Group �� �ٸ� �ϳ��� Vertex Group ������ Edge �� �ϳ� �Ǵ� �������� Vertex �� ������ �ȴ�.
*  ������ Group �������� Vertex ���� ����Ǹ� �ȵȴ�.
* 
*  ���� ��, �������� �л� �߿��� �ϳ��� �л��� ���� ������ ��´ٰ� ������, �� ���� ���� �ΰ��� �ð��� ��ġ�� �ȵǴ� ������ ǥ���� �Ǿ���Ѵ�. 
*  
*  �̷� ������ Maximum Flow Problem �̶�� �ϰ� (�ִ� ���� ����) ��� Ǯ�� �ִ�.
*  ������δ� ���� �Ҽ� �ִ�.
*  1. Ford, Fulkerson's Algorithm
*  2. Dinic Algorithm
*  3. Push, Relabel Algorithm
*  
*  --- �� �ٸ� ���μ���, Netflix �� Youtube ���� ��� ����ڰ� � ��ȭ�� ��û �ߴٰ��ϸ�, Edge �� �����ϴ� ������� History �� ���� �Ҽ� �ִ�.
* 
*  ����: Graph �� BipariteGraph ���� �ƴ��� �Ǻ�
*/

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>

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

template <typename T>
auto create_bipartite_reference_graph()
{
    Graph<T> G(10);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;
    edge_map[1] = { {2, 0} };
    edge_map[2] = { {1, 0}, {3, 0} , {8, 0} };
    edge_map[3] = { {2, 0}, {4, 0} };
    edge_map[4] = { {3, 0}, {6, 0} };
    edge_map[5] = { {7, 0}, {9, 0} };
    edge_map[6] = { {4, 0} };
    edge_map[7] = { {5, 0} };
    edge_map[8] = { {2, 0}, {9, 0} };
    edge_map[9] = { {5, 0}, {8, 0} };

    for (auto& i : edge_map)
        for (auto& j : i.second)
            G.add_edge(Edge<T>{ i.first, j.first, j.second });

    return G;
}

template<typename T>
bool biparite_check(const Graph<T>& G)
{
    stack<unsigned> stack;
    set<unsigned> visited;
    stack.push(1);

    enum class colors { NONE, BLACK, RED };
    colors current_color = colors::BLACK;

    vector<colors> vertex_colors(G.vertices(), colors::NONE);

    while (!stack.empty())
    {
        auto current_vertex = stack.top();
        stack.pop();

        if (visited.find(current_vertex) == visited.end())
        {
            visited.insert(current_vertex);
            vertex_colors[current_vertex] = current_color;

            if (current_color == colors::BLACK)
            {
                current_color = colors::RED;
            }
            else if (current_color == colors::RED)
            {
                current_color = colors::BLACK;
            }

            for (auto e : G.edges(current_vertex))
                if (visited.find(e.dst) == visited.end())
                    stack.push(e.dst);
        }
        else if (vertex_colors[current_vertex] != colors::NONE && vertex_colors[current_vertex] != current_color)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    using T = unsigned;

    auto BG = create_bipartite_reference_graph<T>();
    cout << BG << endl;

    if (biparite_check<T>(BG))
        cout << endl << "�̺� �׷����� �½��ϴ�." << endl;
    else
        cout << endl << "�̺� �׷����� �ƴմϴ�." << endl;
}