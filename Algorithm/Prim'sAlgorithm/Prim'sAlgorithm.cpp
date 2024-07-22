/*
*  Prim's Algorithm
*  
*  Minimum Spanning Tree Review
*  정점 집합 V 와 가중치를 갖는 Edge 조합 E 로 구성된 그래프 G = <V, E> 가 주어
*  졌을때, 모든 정점을 연결하고, 연결된 Edge 의 가중치 합이 최소인 트리 T 를 구하시오
* 
*  Kruskal Algorithm 에서 중요했던건, union-find / Disjoint-set
*  즉 사이클을 만들지 않는 최소 가중치 에지 이용
* 
*  Prime's Algorithm => BFS 의 연장
*  설명: 경계를 구성을 하고, 경계를 관통하는 Edge 중에서 가장 가중치가 작은 Edge 선택
*        가장 작은 Edge 중에서, 연결된 정점을 방문 ** 
* 
*  ---- 알고리즘 시작 ----
*  1. 모든 정점의 거리 값을 무한대로 초기화 하고, 시작 정점같은 경우에는 자신까지의 거리를 0 설정
*     그리고 모든 거리의 값을 최소 힙 H 에 추가
*  2. 최소 Heap H 로 부터 정점하나를 꺼내고, 이 정접 U 를 MST 에 추가하고, 경계 업데이트
*  3. 방금 꺼낸 U 와 인접한 모든 정점 V 에 대해, 만약 V 의 거리값이 (U, V) 의 에지 가중치보다 크면, V 의 거리값을 (U, V)의 Edge 가중치로 설정
*  4. 방문 하지 않은 정점이 남아 있다면 2 단계로 이동
* 
*  즉 이 방식이 Greedy 방식이라는거? 왜?
* 
*  priority_queue 가 제공하는게 Binary Heap => O(log N)
*  E * logV
* 
*  Binary Heap 사용했을때
*  시간 복잡도는 O(E log V)
* 
*  Fibonnaci Heap
*  O (E + V*LogV)
* 
*  # of vertex V
*  # of edges E = V * (V - 1) / 2
* 
*  Prim's VS Kruskal
*  Kruskal 은 최소 가중치 를 가지고 있는 Edge 를 정렬 해서 MST 를 구성
*  시간복잡도는 O(ElogV)
*  Edge 의 개수가 많아질때, 시간복잡도가 올라가니까 => Sparse Graph 에 사용
*  
*  Prims 은 아무정점이나 시작해도 되고
*  시간복잡도는 O(ElogV), 다른 Heap 구조를 선택했을때, O(E + VLogV)
*  주로 Edge 의 개수가 많을때, 이제 Dense 에 사용된다.
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

    // distance 값을 모두 Max 로 초기화
    vector<T> distance(G.vertices(), numeric_limits<T>::max());

    set<unsigned> visited;
    vector<unsigned> MST;

    // 초기 src 처음 시작점과 distance = 0 으로 초기화
    heap.emplace(Label<T>{src, 0});

    while (!heap.empty())
    {
        auto current_vertex = heap.top();
        heap.pop();

        // BFS 시작 (Vertex ID 로 접근
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