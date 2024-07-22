/* BellmanFordAlgorithm
*/

#include "BellmanFordAlgorithm.h"

int main()
{
    int V = 5;
    vector<Edge> edges;
    vector<vector<int>> edge_map
    {
        {0, 1, 3},
        {1, 2, 5},
        {1, 3, 10},
        {3, 2, -7},
        {2, 4, 2}
    };

    for (auto& e : edge_map)
    {
        edges.emplace_back(Edge{ e[0], e[1], e[2] });;
    }

    // start
    int start = 0;
    vector<int> distance = BellmanFord(edges, V, start);
    // end

    // -> Actual Time Complexity
    // -> O(V * E) => Theorietical Complexity

    if (distance.empty())
    {
        std::cout << "Negative Cycle" << std::endl;
    }

    for (int i = 0; i < distance.size(); i++)
    {
        if (distance[i] == INT_MAX)
            cout << i << endl;
        else
            cout << i << distance[i] << endl;
    }

    return 0;
}
