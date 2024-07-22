// MST.cpp

/* �ռ� ���ѰͰ� ����, Dynamic Programming �� Subset �� �ٷ� Greedy Algorithm �̱� ������, Greedy Algorithm �� �׻� ������ �ƴϴ�.
*  
* �׷��ٰ� �Ѵٸ�, Greedy Algorithm �� �����Ҽ� �ִ� *����* �� �����ϱ�?
* 
* 1. Optimal Substructure (���� �κ� ����): �־��� ���� P �� ���� ������ �ַ���� P �� �κ� �������� ������ �ַ������ ������ ��쿡, ���� P �� ������ 
*                                         �κ� ������ ������ �ִ�.
* 
* 2. Greedy Choice (�׸��� ����) : �־��� ���� P �� ���� ������ ���� �ַ���� �ݺ������� �����Ͽ� ��ü ���� �ַ���� ���� �� ���� ���, ���� P �� 
*                                 �׸��� �Ӽ��� ������.
* 
* MST: Minimum Spanning Tree (�ּ� ���� Ʈ��)
* 
* ����: 
* "���� (vertex) �� ���� V �� ����ġ (weight) �� ������ Edge �� ���� E �� ������ �׷��� G = <V, E> �� �־��� ��, ��� ������ �����ϰ� �����
* Edge �� ����ġ�� ���� �ּ��� Ʈ�� T �� ���Ͻÿ�
* 
* ��: ������� ��Ʈ��ũ �Ǵ� ���� ��Ʈ��ũ ����
* ��?! ��� ����鿡�� �������� ������ �Ǿ���ϴϱ�, ȿ�������� �����Ϸ��� ��������� ���̰� �ּҰ� �Ǵ°� ����.
* ���γ�Ʈ��ũ�� ��� �ʿ��� ���� �Ǵ� Landmark �� ���ΰ� ����Ǿ��־���ϸ�, ������ ��ü ���̰� �ּҰ� �Ǵ°� ����.
* 
* ����: ������ ���� ���� ������ �ְ�, ���� ����ɼ� �ֵ��� ���θ� ������� �Ѵ�. �̶� ����� ���δ� Cycle �� �������� ������, ����� ������ ��ü ���̴� 
* �ּҰ� �Ǿ���Ѵ�.
* 
* �˰��� ����
* 1. �׷��� G �� ��� Edge �� �ּ� �� H �� �߰��մϴ�.
* 2. H �� ���� Edge e �� ������, �̋� Edge e �� ��� Edge �߿��� ����ġ�� ���� ���� Edge
* 3. e �� �� �� ������ �̹� T �� ���� ���, e �� ���ؼ� T ���� ����Ŭ�� �߻��Ҽ� �ִ�. �׷��� e �� ������ �ٽ� step2 �� �Ѿ��.
* 4. �ּ� ����Ʈ�� T �� e �� �߰��ϰ� 2 �ܰ�� �̵�
* 
* �׷��� ��� Ư���� ��� Greedy Algorithm ���� Ǯ�� ������?
* 
* Optimal Substructure
* : �ͷ����� ����ؼ� �ּ� ����Ʈ���� �� ���� �ּ� ���� Ʈ���� �������� �������� �ʴٰ� ����
* 1. Graph G �� ���� ������ �ּ� ���� Ʈ�� T �� �ִٰ� ����, T ���� Edge e �� �ϳ� �����ؼ� �����Ѵ�. e �� ���� �ϸ� T�� ������ Ʈ�� T1 �� T2 �� ����������.
* 2. T1 ���� �� ���� ����ġ�� ���� ����Ʈ�� T1' �� �����ؾ��ϸ�, �� ���� Ʈ���� T1' �� T2 �� Edge e �� ������ ���ο� ���� Ʈ���� T' �̶�� �Ѵ�.
* 3. T' �� ����ġ�� T �� ����ġ���� �۱� ������ ó���� T �� �ּ� ����Ʈ����°� ������ ������ Ʋ����.
* 
* Greedy Substructure
* ���� v �� ����� Edge �߿���, �ּ� ����ġ Edge �� �ּ� ���� Ʈ�� T �� ���ؾ��Ѵ�.
* 
* 1. ���� v �� ����Ǿ� �ִ� Edge �߿��� �ּ� ����ġ�� ���� Edge �� ������ (u,v) �� ���� ������
* 2. ���� (u, v) �� T �� ������ �ʴ´ٰ� �ϸ�, T �� v �� ����Ǿ��ִ� �ٸ� Edge �� ���� �ؾ��Ѵٰ� ����
* �׷��� (x, v) �� �ִٰ� ���� (u, v) �� �ּ� ����ġ edge ��� �ϸ� (x, v) �� (u, v) ���� ����ġ�� ��Ŀ���Ѵ�.
* 3. �ٵ� T���� (x, v) �� ���� �� ����, (u, v) �� �߰� �ɶ�, ��ü ����ġ�� �� ���� Ʈ���� Reterieve �� �� �ִ�.
*          
* Lecture Source:
* https://ocw.mit.edu/courses/6-046j-design-and-analysis-of-algorithms-spring-2015/pages/lecture-notes/
* 
* -----------------------------------------------------------------------------------------------------------
* Data Structure: Heap & Graph
* 
* Cyclic Implementation: Disjoint-Set or Union-Find
* 
* ������ Element �� Rank �� Parent �� Pointer �� ������ �ְ�, ���� ID �� ǥ��.
* Disjoin-set �� Reset �Ǹ� Rank 0 �� N ���� �������� ���Ұ� �����ǰ�, ������ ���Ҵ� �ϳ��� Ʈ���� ��Ÿ����.
* 
* ����:
* make-set(x)
* Reset �� ���ش�. ��, Rank 0 �� N ���� �������� ���Ҹ� �����ϰ�, �θ��� Pointer �� �ڱ� �ڽ��� ����ģ��.
* 
* find(x) 
* �� ������ ���� x ���� �����ؼ� �θ� �����͸� ���� �ݺ������� �̵��ϸ�, Ʈ���� Root �� ��ȯ�Ѵ�.
* 
* union(x, y) -> �� Operation �� ���ؼ� Cycle �� ���� �Ҽ� �ִ�.
* x �� y �� ���ؼ� union() ������ �����ϸ�, ���� x �� y �� ���ؼ� Root �� ã�´�. 
* if �ΰ��� Root �� ���ٸ� �̹� ���� Ʈ���� �ִٶ�°� ǥ���ǹǷ� �ƹ��͵� ���� �ʴ´�.
* �θ� �ٸ��ٸ�, ���� ��ũ Root �� ���� Rank Root �� �θ�� ���� (ex: 1 -> 2, 5->4)
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
