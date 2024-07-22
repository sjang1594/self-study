/* Welsh Powel Graph Algorithm 
* 차순 별로 정점 삽입
* 
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

template<typename T>
struct Edge
{
    unsigned src;
    unsigned dst;
    T weight;

    // 가중치 비교
    inline bool operator < (const Edge<T>& e) const
    {
        return this->weight < e.weight;
    }

    inline bool operator > (const Edge<T>& e) const
    {
        return this->weight > e.weight;
    }
};

template<typename T>
class Graph
{
public:
    Graph(unsigned N) : V(N) {}

    // Return # of verticies
    unsigned verticies() const { return V; }

    vector<Edge<T>> edges() const { return edge_list; }

    vector<Edge<T>> edges(unsigned v) const
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
            std::cerr << "Error " << std::endl;
    }

    template<typename U>
    friend ostream& operator << (ostream& os, const Graph<U>& g);

private:
    unsigned V; // # of Vertex
    vector<Edge<T>> edge_list;
};

template<typename U>
ostream& operator << (ostream& os, const Graph<U>& g)
{
    for (unsigned i = 1; i < g.verticies(); i++)
    {
        os << i << ":\t";
        auto edges = g.edges(i);
        for (auto& e : edges)
            os << "{" << e.dst << ": " << e.weight << "}, ";
        os << endl;
        
    }

    return os;
}

std::unordered_map<unsigned, std::string> colorMap = {
    {1, "Red"},
    {2, "Blue"},
    {3, "Green"},
    {4, "Yellow"},
    {5, "Black"},
    {6, "White"}
};

template<typename T>
auto welsh_powell_coloring(const Graph<T> g)
{
    unsigned size = g.verticies();
    vector<std::pair<unsigned, size_t>> degrees;

    for (unsigned i = 1; i < size; i++)
        degrees.push_back(std::make_pair(i, g.edges(i).size()));

    // sort the descending order
    std::sort(degrees.begin(), degrees.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

    for (auto const i : degrees)
        cout << "" << i.first << " (" << i.second << ")" << endl;

    vector<unsigned> assigned_colors(size);
    auto color_to_be_assigned = 1;
    while (true)
    {
        for (auto const i : degrees)
        {
            if (assigned_colors[i.first] != 0)
                continue;

            auto outgoing_edges = g.edges(i.first);

            set<unsigned> neighbours;
            for (auto& e : outgoing_edges)
            {
                neighbours.insert(assigned_colors[e.dst]);
            }

            if (neighbours.find(color_to_be_assigned) == neighbours.end())
                assigned_colors[i.first] = color_to_be_assigned;
        }

        color_to_be_assigned++;
        if (find(assigned_colors.begin() + 1, assigned_colors.end(), 0) == assigned_colors.end())
            break;
    }

    return assigned_colors;
}

template <typename T>
void print_colors(vector<T>& colors)
{
    for (auto i = 1; i < colors.size(); i++)
    {
        cout << i << ": " << colorMap[colors[i]] << endl;
    }
}

int main()
{
    using T = unsigned;

    // 그래프 객체 생성
    Graph<T> G(9);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;
    edge_map[1] = { {2, 0}, {5, 0} };
    edge_map[2] = { {1, 0}, {5, 0}, {4, 0} };
    edge_map[3] = { {4, 0}, {7, 0} };
    edge_map[4] = { {2, 0}, {3, 0}, {5, 0}, {6, 0}, {8, 0} };
    edge_map[5] = { {1, 0}, {2, 0}, {4, 0}, {8, 0} };
    edge_map[6] = { {4, 0}, {7, 0}, {8, 0} };
    edge_map[7] = { {3, 0}, {6, 0} };
    edge_map[8] = { {4, 0}, {5, 0}, {6, 0} };

    for (auto& i : edge_map)
        for (auto& j : i.second)
            G.add_edge(Edge<T>{ i.first, j.first, j.second });

    cout << "[입력 그래프]" << endl;
    cout << G << endl;

    auto colors = welsh_powell_coloring<T>(G);
    cout << endl << "[그래프 컬러링]" << endl;
    print_colors(colors);


    return 0;
}