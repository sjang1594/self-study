#include <iostream>
#include <vector>
#include <algorithm>

/* Adjacent List 
*  Save the Edges among nodes (ID)
*/

enum class city : int
{
    MOSCOW,
    LONDON,
    SEOUL,
    SEATTLE,
    DUBAI,
    SYDNEY
};

std::ostream& operator<<(std::ostream& os, const city c)
{
    switch (c)
    {
    case city::LONDON:
    {
        os << "London";
        return os;
        break;
    }
    case city::MOSCOW:
    {
        os << "Moscow";
        return os;
        break;
    }
    case city::SEOUL:
    {
        os << "Seoul";
        return os;
        break;
    }
    case city::SEATTLE:
    {
        os << "Seattle";
        return os;
        break;
    }
    case city::DUBAI:
    {
        os << "Dubai";
        return os;
        break;
    }
    case city::SYDNEY:
    {
        os << "Sydney";
        return os;
        break;
    }
    default:
        return os;
    }
}

// [pair<>] [pair<>] [pair<>] 
// [pair<>] [pair<>] [pair<>] 
// [pair<>] [pair<>] [pair<>]
struct graph
{
    std::vector<std::vector<std::pair<int, int>>> data;
    graph(int n)
    {
        data = std::vector<std::vector<std::pair<int, int>>>(n, std::vector<std::pair<int, int>>());
    }

    void addEdge(const city c1, const city c2, int dis)
    {
        std::cout << "Adding Edge: " << c1 << " - " << c2 << "=" << dis << std::endl;
        const int n1 = static_cast<int>(c1);
        const int n2 = static_cast<int>(c2);
        data[n1].push_back({ n1, dis });
        data[n2].push_back({ n2, dis });
    }

    void removeEdge(const city c1, const city c2)
    {
        std::cout << "Deleting Edge: " << c1 << " - " << c2 << std::endl;
        const int n1 = static_cast<int>(c1);
        const int n2 = static_cast<int>(c2);
        std::remove_if(data[n1].begin(), data[n1].end(), [n2](const auto& pair) {return pair.first = n2; });
        std::remove_if(data[n2].begin(), data[n2].end(), [n1](const auto& pair) {return pair.first = n1; });
    }
};

int main()
{
    graph g(6);
    g.addEdge(city::LONDON, city::MOSCOW, 2500);
    g.addEdge(city::LONDON, city::SEOUL, 9000);
    g.addEdge(city::LONDON, city::DUBAI, 5500);
    g.addEdge(city::SEOUL, city::MOSCOW, 6600);
    g.addEdge(city::SEOUL, city::SEATTLE, 8000);
    g.addEdge(city::SEOUL, city::DUBAI, 7000);
    g.addEdge(city::SEOUL, city::SYDNEY, 8000);
    g.addEdge(city::SEATTLE, city::MOSCOW, 8400);
    g.addEdge(city::SEATTLE, city::SYDNEY, 12000);
    g.addEdge(city::DUBAI, city::SYDNEY, 1200);

    g.addEdge(city::SEATTLE, city::LONDON, 8000);
    g.removeEdge(city::SEATTLE, city::LONDON);
    return 0;
}