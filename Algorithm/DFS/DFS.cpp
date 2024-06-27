/*
*  DFS 는 Child 의 Child 끝까지, 즉 Leaf Node 를 탐색한다.
*  
*  BFS 와 DFS 의 공통점은 시간복잡도가 O(V+E)
*  BFS 는 모든 근처의 Vertex 를 다 흝어보기 때문에, 많은 메모리가 필요하고, 트리의 길이는 짧다.
*  DFS 는 chilren 의 children 즉 Depth 를 보기 때문에, 트리의 길이는 길고, 상대적으로 적은 메모리를 사용
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
vector<unsigned> depth_first_search(const Graph<T>& G, unsigned start)
{
    stack<unsigned> stack;
    set<unsigned> visited;
    vector<unsigned> visit_order;
    stack.push(start);

    while (!stack.empty())
    {
        auto current_vertex = stack.top();
        stack.pop();

        if (visited.find(current_vertex) == visited.end())
        {
            visited.insert(current_vertex);
            visit_order.emplace_back(current_vertex);

            for (auto& e : G.edges(current_vertex))
            {
                if (visited.find(e.dst) == visited.end())
                {
                    stack.push(e.dst);
                }
            }
        }
    }
    return visit_order;
}

int main()
{
    using T = unsigned;
    auto G = create_reference_graph<T>();
    cout << G << endl;

    auto dfs_visited_order = depth_first_search(G, 1);
    for (auto v : dfs_visited_order)
        cout << v << endl;
    return 0;
}
