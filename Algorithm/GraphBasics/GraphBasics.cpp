// GraphBasics.cpp

/* Tree 는 Hierchical Data 로 표현하기는 좋은 방법이였지만,
* 경로 찾기 처럼, 하나의 노드에서 다른 노드로 이동하는 경로만으로 이루어지지 않기때문에, 원형 또는 순환적인 종속성을 표현할수 없다.
* 
* Graph
* [A] <- e1 -> [B]
* Computer Graphics 
* Vertex A 
* [A] < - e1 - > [B] [A] < - e2 - > [C] [A] < - e3 - > [D] [A] < - e4 - > [E]
* 
* | ^ | water |  |
* Graph 는 Node Data 뿐만 아니라 Node 사이들의 Edge Data 도 저장해야한다.
* 예: 도로망 같은 경우
* Node: 각각의 장소
* Edge: 각각의 장소를 연결을 해주는 도로 (즉 다른 어떤 장소들이 연결되어있는지)
* 
* Unweighted Graph vs Weighted Graph (Weight)
* 1. 모든 Node 와 Edge 가 있는 Graph 를 만든다고 했을때, Unweighted Graph(비가중그래프) 로 표현이 가능
* 2. 모든 Node 와 Edge 가 있고, Edge 에 가중치(ex: 거리) 를 주어서, weighted graph (가중 그래프로) 표현이 가능
*   - 즉 Node 사이의 거리를 Edge 에 표현한다.
*   - ex: 최단 경로 찾기!
*                                                   
* Undirected Graph vs Directed Graph (Direction)
* 1. 방향이 없는 Graph, 즉 Edge 가 양방향 (상호 교환적인 속성) A <-> B
* 2. 방향이 있는 Graph 즉 Edge 가 개별로 따로 있은 A -> B, B -> A (***)
* 
* Graph 는 순환적인 구조를 가질수 있기 때문에, 특정 노드에서 다른 노드로 이동하는 방법도 여러개일수 있기 때문에, NODE 에 ID 가 부여
* Standard Template Library 를 사용해서 Graph 를 ADT 처럼 구현 가능하다.
*/

//   A B C
// A 0 1 0
// B 1 0 1
// C 0 0 0

/* Adjacency Matrix
    Node N 개 가 있으면, N x N 으로 Array 로 배열 표혀이 가능하다. 그리고 NODE 끼리의 가중치를 둔다고 했을때
    data[1][2] 는 노드 1 에서 2 까지 잇는 Edge 의 가중치 표현, 연결 되지 않으면 -1.
*/

#include <iostream>
#include <vector>

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

struct graph
{
    std::vector<std::vector<int>> data;

    graph(int n)
    {
        data.reserve(n); // int arr[size]
                         // int arr[size] = {0, }
        std::vector<int> row(n);
        std::fill(row.begin(), row.end(), -1);
        for (int i = 0; i < n; i++)
        {
            data.push_back(row);
        }
    }

    void addEdge(const city c1, const city c2, int dis)
    {
        std::cout << "Adding Edge: " << c1 << " - " << c2 << "=" << dis << std::endl;
        const int n1 = static_cast<int>(c1);
        const int n2 = static_cast<int>(c2);
        data[n1][n2] = dis;
        data[n2][n1] = dis;
    }

    void removeEdge(const city c1, const city c2)
    {
        std::cout << "Deleting Edge: " << c1 << " - " << c2 << std::endl;
        const int n1 = static_cast<int>(c1);
        const int n2 = static_cast<int>(c2);
        data[n1][n2] = -1;
        data[n2][n1] = -1;
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
