// GraphBasics.cpp

/* Tree �� Hierchical Data �� ǥ���ϱ�� ���� ����̿�����,
* ��� ã�� ó��, �ϳ��� ��忡�� �ٸ� ���� �̵��ϴ� ��θ����� �̷������ �ʱ⶧����, ���� �Ǵ� ��ȯ���� ���Ӽ��� ǥ���Ҽ� ����.
* 
* Graph
* [A] <- e1 -> [B]
* Computer Graphics 
* Vertex A 
* [A] < - e1 - > [B] [A] < - e2 - > [C] [A] < - e3 - > [D] [A] < - e4 - > [E]
* 
* | ^ | water |  |
* Graph �� Node Data �Ӹ� �ƴ϶� Node ���̵��� Edge Data �� �����ؾ��Ѵ�.
* ��: ���θ� ���� ���
* Node: ������ ���
* Edge: ������ ��Ҹ� ������ ���ִ� ���� (�� �ٸ� � ��ҵ��� ����Ǿ��ִ���)
* 
* Unweighted Graph vs Weighted Graph (Weight)
* 1. ��� Node �� Edge �� �ִ� Graph �� ����ٰ� ������, Unweighted Graph(���߱׷���) �� ǥ���� ����
* 2. ��� Node �� Edge �� �ְ�, Edge �� ����ġ(ex: �Ÿ�) �� �־, weighted graph (���� �׷�����) ǥ���� ����
*   - �� Node ������ �Ÿ��� Edge �� ǥ���Ѵ�.
*   - ex: �ִ� ��� ã��!
*                                                   
* Undirected Graph vs Directed Graph (Direction)
* 1. ������ ���� Graph, �� Edge �� ����� (��ȣ ��ȯ���� �Ӽ�) A <-> B
* 2. ������ �ִ� Graph �� Edge �� ������ ���� ���� A -> B, B -> A (***)
* 
* Graph �� ��ȯ���� ������ ������ �ֱ� ������, Ư�� ��忡�� �ٸ� ���� �̵��ϴ� ����� �������ϼ� �ֱ� ������, NODE �� ID �� �ο�
* Standard Template Library �� ����ؼ� Graph �� ADT ó�� ���� �����ϴ�.
*/

//   A B C
// A 0 1 0
// B 1 0 1
// C 0 0 0

/* Adjacency Matrix
    Node N �� �� ������, N x N ���� Array �� �迭 ǥ���� �����ϴ�. �׸��� NODE ������ ����ġ�� �дٰ� ������
    data[1][2] �� ��� 1 ���� 2 ���� �մ� Edge �� ����ġ ǥ��, ���� ���� ������ -1.
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
