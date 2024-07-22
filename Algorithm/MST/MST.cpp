// MST.cpp

/* 앞서 말한것과 같이, Dynamic Programming 의 Subset 이 바로 Greedy Algorithm 이기 때문에, Greedy Algorithm 이 항상 정답이 아니다.
*  
* 그렇다고 한다면, Greedy Algorithm 을 적용할수 있는 *조건* 이 무엇일까?
* 
* 1. Optimal Substructure (최적 부분 구조): 주어진 문제 P 에 대한 최적의 솔루션이 P 의 부분 문제들의 최적의 솔루션으로 구성될 경우에, 문제 P 가 최적의 
*                                         부분 구조를 가지고 있다.
* 
* 2. Greedy Choice (그리디 선택) : 주어진 문제 P 에 대한 지역적 최적 솔루션을 반복적으로 선택하여 전체 최적 솔루션을 구할 수 있을 경우, 문제 P 가 
*                                 그리디 속성을 가진다.
* 
* MST: Minimum Spanning Tree (최소 신장 트리)
* 
* 정의: 
* "정점 (vertex) 의 집합 V 와 가중치 (weight) 를 가지는 Edge 의 집합 E 로 구성된 그래프 G = <V, E> 가 주어질 때, 모든 정점을 연결하고 연결된
* Edge 의 가중치의 합이 최소인 트리 T 를 구하시요
* 
* 예: 상수도관 네트워크 또는 도로 네트워크 설계
* 왜?! 모든 사람들에게 수돗물이 전달이 되어야하니까, 효율적으로 설계하려면 상수도관의 길이가 최소가 되는게 좋다.
* 도로네트워크는 모든 필요한 지점 또는 Landmark 에 도로가 연결되어있어야하며, 도로의 전체 길이가 최소가 되는게 좋다.
* 
* 문제: 지도상에 여덟 개의 마을이 있고, 서로 연결될수 있도록 도로를 만들려고 한다. 이때 연결된 도로는 Cycle 이 구성되지 않으며, 연결된 도로의 전체 길이는 
* 최소가 되어야한다.
* 
* 알고리즘 순서
* 1. 그래프 G 에 모든 Edge 에 최소 힙 H 를 추가합니다.
* 2. H 로 부터 Edge e 를 꺼낸다, 이떄 Edge e 는 모든 Edge 중에서 가중치가 가장 작은 Edge
* 3. e 의 양 끝 정점이 이미 T 에 있을 경우, e 로 인해서 T 에서 사이클이 발생할수 있다. 그래서 e 를 버리고 다시 step2 로 넘어간다.
* 4. 최소 신장트리 T 에 e 를 추가하고 2 단계로 이동
* 
* 그러면 어떻게 특성이 어떻게 Greedy Algorithm 으로 풀수 있을까?
* 
* Optimal Substructure
* : 귀류법을 사용해서 최소 신장트리가 더 작은 최소 신장 트리의 집합으로 구성되지 않다고 가정
* 1. Graph G 의 정점 구성된 최소 신장 트리 T 가 있다고 가정, T 에서 Edge e 를 하나 선택해서 제거한다. e 를 제거 하면 T가 더작은 트리 T1 과 T2 로 나누어진다.
* 2. T1 보다 더 작은 가중치를 갖는 신장트리 T1' 이 존재해야하며, 이 신장 트리를 T1' 과 T2 를 Edge e 로 연결한 새로운 신장 트리를 T' 이라고 한다.
* 3. T' 의 가중치가 T 의 가중치보다 작기 때문에 처음에 T 가 최소 신장트리라는게 가정의 가설이 틀리다.
* 
* Greedy Substructure
* 정점 v 와 연결된 Edge 중에서, 최소 가중치 Edge 는 최소 신장 트리 T 에 속해야한다.
* 
* 1. 정점 v 와 연결되어 있는 Edge 중에서 최소 가중치를 갖는 Edge 를 가지는 (u,v) 가 존재 가넞ㅇ
* 2. 만약 (u, v) 가 T 에 속해지 않는다고 하면, T 는 v 와 연결되어있는 다른 Edge 를 포함 해야한다고 가정
* 그러면 (x, v) 가 있다고 가정 (u, v) 가 최소 가중치 edge 라고 하면 (x, v) 는 (u, v) 보다 가중치가 더커야한다.
* 3. 근데 T에서 (x, v) 를 제거 한 이후, (u, v) 가 추가 될때, 전체 가중치가 더 작은 트리를 Reterieve 할 수 있다.
*          
* Lecture Source:
* https://ocw.mit.edu/courses/6-046j-design-and-analysis-of-algorithms-spring-2015/pages/lecture-notes/
* 
* -----------------------------------------------------------------------------------------------------------
* Data Structure: Heap & Graph
* 
* Cyclic Implementation: Disjoint-Set or Union-Find
* 
* 각각의 Element 는 Rank 와 Parent 의 Pointer 를 가지고 있고, 숫자 ID 로 표현.
* Disjoin-set 이 Reset 되면 Rank 0 인 N 개의 독립적인 원소가 생성되고, 각각의 원소는 하나의 트리를 나타낸다.
* 
* 연산:
* make-set(x)
* Reset 을 해준다. 즉, Rank 0 인 N 개의 독립적인 원소를 생성하고, 부모의 Pointer 는 자기 자신을 가르친다.
* 
* find(x) 
* 이 연산은 원소 x 에서 시작해서 부모 포인터를 따라 반복적으로 이동하며, 트리의 Root 를 반환한다.
* 
* union(x, y) -> 이 Operation 을 통해서 Cycle 을 방지 할수 있다.
* x 와 y 에 대해서 union() 연산을 수행하면, 먼저 x 와 y 에 대해서 Root 를 찾는다. 
* if 두개가 Root 가 같다면 이미 같은 트리에 있다라는게 표현되므로 아무것도 하지 않는다.
* 부모가 다르다면, 높은 랭크 Root 를 낮은 Rank Root 의 부모로 설정 (ex: 1 -> 2, 5->4)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

class SimpleDisjointSet
{
    struct Node
    {
        unsigned id;
        unsigned rank;
        unsigned parent;

        Node(unsigned _id) : id(_id), rank(0), parent(_id) {}
        bool operator !=(const Node& n) const
        {
            return this->id != n.id;
        }
    };

    vector<Node> nodes;

public:
    SimpleDisjointSet(unsigned N)
    {
        nodes.reserve(N);
    }

    void make_set(const unsigned& x)
    {
        nodes.emplace_back(x);
    }

    unsigned find(unsigned x)
    {
        auto node_it = find_if(nodes.begin(), nodes.end(), [x](auto n) { return n.id == x; });
        unsigned node_id = (*node_it).id;

        while (node_id != nodes[node_id].parent)
        {
            node_id = nodes[node_id].parent;
        }

        return node_id;
    }

    void union_set(unsigned x, unsigned y)
    {
        auto root_x = find(x);
        auto root_y = find(y);
        if (root_x == root_y) return;

        if (nodes[root_x].rank > nodes[root_y].rank)
            swap(root_x, root_y);

        nodes[root_x].parent = nodes[root_y].parent;
        nodes[root_y].rank++;
    }
};

template <typename T>
struct Edge
{
    unsigned src;
    unsigned dst;
    T weight;
    
    inline bool operator <(const Edge<T>& e) const
    {
        return this->weight < e.weight;
    }

    inline bool operator >(const Edge<T>& e) const
    {
        return this->weight > e.weight;
    }
};

template <typename T>
class Graph
{
public:
    Graph(unsigned N) : V(N) {}

    auto vertices() const { return V; };

    auto& edges() const { return edge_list; }

    auto edges(unsigned v) const
    {
        vector<Edge<T>> edges_from_v;
        for (auto& e : edge_list)
        {
            if (e.src == v)
                edges_from_v.emplace_back(e);
        }
        return edges_from_v;
    }

    void add_edge(Edge<T>&& e)
    {
        if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
            edge_list.emplace_back(e);
        else
            cerr << "Error" << std::endl;
    }

    template<typename U>
    friend ostream& operator<<(ostream& os, const Graph<U>& G)
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
Graph<T> minimum_spanning_tree(const Graph<T>& G)
{
    priority_queue<Edge<T>, vector<Edge<T>>, greater<Edge<T>>> edge_min_heap;

    for (auto& e : G.edges())
        edge_min_heap.push(e);

    auto N = G.vertices();
    SimpleDisjointSet dset(N);
    for (unsigned i = 0; i < N; i++)
        dset.make_set(i);

    Graph<T> mst(N);
    while (!edge_min_heap.empty())
    {
        auto e = edge_min_heap.top();
        edge_min_heap.pop();

        if (dset.find(e.src) != dset.find(e.dst))
        {
            mst.add_edge(Edge<T>{e.src, e.dst, e.weight});
            dset.union_set(e.src, e.dst);
        }
    }

    return mst;
}

int main()
{
    using T = unsigned;

    Graph<T> G(9);

    map<unsigned, vector<std::pair<unsigned, T>>> edge_map;
    edge_map[1] = { {2, 2}, {5, 3} };
    edge_map[2] = { {1,2}, {5, 5}, {4, 1} };
    edge_map[3] = { {4,2}, {7, 3} };
    edge_map[4] = { {2,1}, {3,2}, {5,2}, {6,4}, {8,5} };
    edge_map[5] = { {1,3}, {2,5}, {4,2}, {8,3} };
    edge_map[6] = { {4, 4}, {7, 4}, {8,1} };
    edge_map[7] = { {3,3}, {6,4} };
    edge_map[8] = { {4,5}, {5,3}, {6,1} };

    for (auto& i : edge_map)
        for (auto& j : i.second)
            G.add_edge(Edge<T>{i.first, j.first, j.second});
    cout << G << endl;

    Graph<T> mst = minimum_spanning_tree(G);
    cout << mst << endl;
}
