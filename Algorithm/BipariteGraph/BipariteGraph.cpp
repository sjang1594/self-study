/* BipariteGraph
*  
*  두개의 Vertex 집합과 한 Vertex Group 과 다른 하나의 Vertex Group 끼리의 Edge 는 하나 또는 여러개의 Vertex 와 연결이 된다.
*  하지만 Group 내에서는 Vertex 끼리 연결되면 안된다.
* 
*  예를 들어서, 여러명의 학생 중에서 하나의 학생이 대학 수업을 듣는다고 했을때, 그 대학 수업 두개는 시간이 겹치면 안되는 식으로 표현이 되어야한다. 
*  
*  이런 문제를 Maximum Flow Problem 이라고 하고 (최대 유량 문제) 라고 풀수 있다.
*  방법으로는 으로 할수 있다.
*  1. Ford, Fulkerson's Algorithm
*  2. Dinic Algorithm
*  3. Push, Relabel Algorithm
*  
*  --- 또 다른 예로서는, Netflix 나 Youtube 같은 경우 사용자가 어떤 영화를 시청 했다고하면, Edge 를 연결하는 방식으로 History 를 관리 할수 있다.
* 
*  문제: Graph 가 BipariteGraph 인지 아닌지 판별
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
        cout << endl << "이분 그래프가 맞습니다." << endl;
    else
        cout << endl << "이분 그래프가 아닙니다." << endl;
}