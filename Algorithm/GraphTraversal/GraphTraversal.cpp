/*
*  Graph 는 Vertex 의 집합과 Edge 의 집합으로 구성되고, G = <V, E> 수학적으로 표현을 한다.
*  Graph 의 Edge 의 방향성을 가지고 있다면, directed graph, 그렇지 않으면 undirected graph
*  각 Edge 의 weight 정보가 있다면, weighted grapph, 그렇지 않다고 하면 unweighted.
* 
*  Graph 는 자료구조냐? 맞다. (Tree 또는 Link List 처럼 자료구조의 형태를 가지고 있다.)
*  과거에는 이러한 Graph 의 구조를 Finite State Machine 을 통해서, 객체의 형태 또는 객체의 행위등을 표현하기도 했다.
* 
*  Graph Traversal Problem
*  어떤 특정 Vertex 에서 시작해서, 나머지 모든 정점을 방문하는 문제
*  
*  즉 이 문제를 풀기위해서는 Graph Search Problem 의 일부분이다. 예를 들어서 어떤 특정 정점을 찾아야 하기 때문에.
* 
*  BFS (Breadth First Search): 너비 우선 탐색
* 
*  첫 시작점 (Vertex) 로 부터 인접한 Vertex 를 찾는다. 첫 시작점을 방문한 정점으로 두고, 인접한 정점을 다음에 살펴볼 정점이다.
*  그 다음 인접한 정점으로 어떤 순서와 상관 없이 찾아가서, 방문한 정점을 Marking 한다. 물론 같은 Tree Level 에서는 다 방문해야한다.
*  이걸 반복적으로 수행한다.
* 
*  즉 여기서 중요한 부분은 자식을 차례로 돌고, 그다음 GrandChildren 을 돈다는거.
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

        // set 이라는곳에, 지금 현재 Vertex 가 없다고 한다면...
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