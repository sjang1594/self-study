/* GraphColoring 
* 
*  주어진 그래프 G 에서 서로 인접한 정점끼리 같은 색을 가지지 않도록 모든 정점에 색상을 지정
*  그림: Page .183
*  
*  예: 택시 예약 Scheduling / Sudoku Puzzle / TimeTable Scheduling
*  
*  그래프 컬러링에 필요한 최소 개수의 색상 수는 -> Greedy 보다는 Dynamic Programming => Chromatic Numbering 
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

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
        std::vector<Edge<T>> edges_from_v;
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
    std::vector<Edge<T>> edge_list;
};

std::unordered_map<unsigned, std::string> colorMap = {
    {1, "Red"},
    {2, "Blue"},
    {3, "Green"},
    {4, "Yellow"},
    {5, "Black"},
    {6, "White"}
};

template<typename T>
auto greedy_coloring(const Graph<T> G)
{
    auto size = G.vertices();
    std::vector<unsigned> assigned_colors(size);

    // [0][1][1][2][1][0][][2]
    // Search 
    for (unsigned i = 1; i < size; i++)
    {
        // Get Edge 
        auto outgoing_edges = G.edges(i);

        // Save incident vertices 
        std::set<unsigned> neighbours;

        for (auto& e : outgoing_edges)
        {
            neighbours.insert(assigned_colors[e.dst]);
        }

        auto smallest = 1;
        for (; smallest <= colorMap.size(); smallest++)
        {
            if (neighbours.find(smallest) == neighbours.end())
                break;
        }
        assigned_colors[i] = smallest;
    }

    return assigned_colors;
}

template<typename T>
void printColors(std::vector<T>& colors)
{
    for (auto i = 1; i < colors.size(); i++)
    {
        std::cout << i << ": " << colorMap[colors[i]] << std::endl;
    }
}

int main()
{
    using T = unsigned;
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
            G.add_edge(Edge<T>{i.first, j.first, j.second});
    std::cout << G << std::endl;

    std::vector<unsigned> colors = greedy_coloring<T>(G);
    printColors(colors);
}