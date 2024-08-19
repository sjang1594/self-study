/*
*  Constructing Roads
*  
*  Inputs 
*  * Map from Realtor (Map's width & height)  
*  * The coordinate for each buildings 
*  * Ground Strength for each coordinates.
*  * The number of house you want to build.
*  * String width on line H.
*  * Ground Strength in Intgeer
*  
*  Main Goal: 
*  * 두 집 사이에 도로를 건설 하는데 필요한 비용은 두집을 잇는 경로상의 지반 강도 합과 같습니다.
* 
*  Output 
*  최대한 저렴하게 도로 시스템을 건설
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const char EMPTY_SPACE = '.';
const string roads = "-|/\\";

// Coordinate System
struct Point
{
    Point() : x(0), y(0) {};
    Point(int _x, int _y) : x(_x), y(_y) {};

    bool operator !=(const Point& other) const
    {
        return x != other.x || y != other.y;
    }

    int x, y;
};

// Set Input Parameters 
int H, W, N; // H being Height, W being Width, N for number of houses.
vector<string> grid;
vector<vector<int>> terrain;
vector<vector<int>> cost;
vector<Point> houses;

void ProcessInput()
{
    const int unknown = 1e9;
    cin >> H >> W;
    cin >> N;

    // Set size for grid
    grid.resize(H);
    houses.resize(N);
    terrain.resize(H, vector<int>(W, unknown));
    cost.resize(N, vector<int>(N, unknown));

    // Map Info
    for (int i = 0; i < H; i++)
    {
        cin >> grid[i];
    }

    // Ground Strength
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> terrain[i][j];
        }
    }

    // Coordinate for each houses
    for (int i = 0; i < N; i++)
    {
        cin >> houses[i].x >> houses[i].y;
        grid[houses[i].y][houses[i].x] = char(i + 'A'); // bit 움직여주는 
    }
}

// A ... B
// D ... E
// C ... .

void PrintDebug()
{
    for (int i = 0; i < H; i++)
    {
        cout << grid[i];
    }

    // Ground Strength
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cout << terrain[i][j];
        }
    }
}

bool CheckDirection(Point a, Point b)
{
    if (a.x == b.x) return true; // horizontal
    if (a.y == b.y) return true; // vertical
    if (abs(a.x - b.x) == abs(a.y - b.y)) return true;
    return false;
}

int GetCost(int start, int end)
{
    const int unknown = 1e9;
    Point a = houses[start];
    Point b = houses[end];

    int x_dir = 0;
    int y_dir = 0;
    if (a.x != b.x)
    {
        x_dir = (a.x < b.x) ? 1 : -1;
    }

    if (a.y != b.y)
    {
        y_dir = (a.y < b.y) ? 1 : -1;
    }

    int cost = 0;

    do {
        a.x += x_dir;
        a.y += y_dir;
        cost += terrain[a.y][a.x];
    } while (grid[a.y][a.x] == '.');

    return (a != b) ? unknown : cost;
}

void BuildGraph()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (i == j) continue;

            if (CheckDirection(houses[i], houses[j]))
            {
                cost[i][j] = cost[j][i] = GetCost(i, j);
            }
        }
    }
}

vector<int> GetPath(int start, int end, vector<vector<int>>& next)
{
    vector<int> path = { start };

    do {
        start = next[start][end];

        path.push_back(start);
    } while (next[start][end] != end);

    return path;
}

int GetDirection(int x_dir, int y_dir)
{
    if (y_dir == 0) return 0;
    if (x_dir == 0) return 1;
    if (x_dir == -1)
    {
        return (y_dir == 1) ? 2 : 3;
    }
    return (y_dir == 1) ? 3 : 2;
}

void DrawPath(int start, int end)
{
    Point a = houses[start];
    Point b = houses[end];

    int x_dir = 0;
    int y_dir = 0;

    if (a.x != b.x)
    {
        x_dir = (a.x < b.x) ? 1 : -1;
    }

    if (a.y != b.y)
    {
        y_dir = (a.y < b.y) ? 1 : -1;
    }

    int direction = GetDirection(x_dir, y_dir);
    char mark = roads[direction];

    do {
        a.x += x_dir;
        a.y += y_dir;

        if (grid[a.y][a.x] == EMPTY_SPACE)
        {
            grid[a.y][a.x] = mark;
        }
        else if (!isalpha(grid[a.y][a.x]))
        {
            grid[a.y][a.x] = (mark != grid[a.y][a.x]) ? '+' : mark;
        }
    } while (a != b);
}

void GetShortestPaths()
{
    const int unknown = 1e9;
    vector<vector<int>> dist(N, vector<int>(N, unknown));
    vector<vector<int>> next(N, vector<int>(N, unknown));

    // Dynamic Programming Approach
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            dist[i][j] = cost[i][j];

            if (dist[i][j] != unknown)
            {
                next[i][j] = j;
            }
        }

        dist[i][i] = 0;
        next[i][i] = i;
    }

    std::cout << "Debug" << std::endl;

    // Floyd-warshall
    for (int mid = 0; mid < N; mid++)
    {
        for (int start = 0; start < N; start++)
        {
            for (int end = 0; end < N; end++)
            {
                if (dist[start][end] > dist[start][mid] + dist[mid][end])
                {
                    dist[start][end] = dist[start][mid] + dist[mid][end];
                    next[start][end] = next[start][mid];
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        vector<int> path = GetPath(i, N - 1, next);

        int curr = i;

        for (auto neighbor : path)
        {
            DrawPath(curr, neighbor);
            curr = neighbor;
        }
    }
}

int main()
{
    ProcessInput();
    // PrintDebug();
    BuildGraph();

    // PrintDebug();
    GetShortestPaths();
}