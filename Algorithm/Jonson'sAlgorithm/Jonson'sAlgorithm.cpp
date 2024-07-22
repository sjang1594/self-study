/* Jonson's Algorithm
* 
*  Dijsktra 의 장점(빠르기) 와 BellmanFord 의 장점 (음수 가중치) 를 섞은 알고리즘
*  1. 전체 Edge 의 가중치를 음수가 아닌형태로 변경
*  2. Dummy 정점을 추가해서, 나머지 모든 정점사이에 가중치가 0 인 Edge 를 연결한다.
*  3. 이후에는 Bellman Ford 를 사용해서 더미 정점과 나머지 정점들 사이의 최단 경로를 찾는다.
*  
*  Dummy 정점
*  1. Dummy 정점을 연결함으로써, 모든 최단거리 값이 0 보다 클수 가 없다.
*  2. 그래프의 모든 정점에 대한 연결을 통해 거리 값이 모든 가능한 순회 경로에서 일정한 관계유지
*  3. Edge 의 Weight 와 최단 거리의 합 연산이 간단해진다.
*  4. 결국 전체의 합은 첫번째 정점과 마지막 정점의 거리 값 차와 같다. 
*  
*  W(u,v) = w(u,v) + d[s, u] - d[s, v]
*  AB -> (-7) + 0 - (-7) = 0
*  BC -> (-2) + (-7) - (-9) = 0
*  CA -> 10 + (-9) - 0 = 1
*  AD -> (-5) + 0 - (-5) = 0
*  DE -> 4 + (-5) - (-1) = 0
* 
*  W(AB) + W(BC) + W(CA) + W(AD) + W(DE) + d[s, A] - d[s, E]
*  
*  항상 d[s, u] + weight(u, v) >= d[s, v] 조건이 있기때문에 변환된 가중치는 음수가 될수 없다.
*  
*  즉 w(u, v) + d[s,u] - d[s, v] 값은 무조건 0 보다 같거나 큰수이다.
*/

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

struct Edge
{
	int src;
	int dst;
	int weight;
};

const int UNKNOWN = INT_MAX;

bool HasNegativeCycle(const vector<Edge>& edges, vector<int> distance)
{
	for (auto& e : edges)
	{
		if (distance[e.src] == UNKNOWN)
			continue;

		if (distance[e.dst] > distance[e.src] + e.weight)
			return true;
	}

	return false;
}

vector<int> BellmanFord(vector<Edge> edges, int V)
{
	vector<int> distance(V + 1, UNKNOWN);

	int s = V;
	for (int i = 0; i < V; i++)
	{
		edges.push_back(Edge{ s, i, 0 });
	}

	distance[s] = 0;

	// 정점 개수가 V + 1개 이므로 V번 반복
	for (int i = 0; i < V; i++)
	{
		for (auto& e : edges)
		{
			// 에지의 시작 정점의 거리 값이 UNKNOWN이면 스킵
			if (distance[e.src] == UNKNOWN)
				continue;

			// 인접한 정점의 거리 값이 새로운 경로에 의한 거리 값보다 크면
			// 거리 값을 업데이트함.
			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				distance[e.dst] = distance[e.src] + e.weight;
			}
		}
	}

	// 음수 가중치 사이클이 있는 지 검사
	if (HasNegativeCycle(edges, distance))
	{
		cout << "음수 가중치 사이클 발견!" << endl;
		return {};
	}

	return distance;
}

int GetMinDistance(vector<int>& distance, vector<bool>& visited)
{
	int minDistance = UNKNOWN;
	int minIndex = -1;

	for (int i = 0; i < distance.size(); i++)
	{
		if (!visited[i] && distance[i] <= minDistance)
		{
			minDistance = distance[i];
			minIndex = i;
		}
	}

	return minIndex;
}

vector<int> Dijkstra(vector<Edge> edges, int V, int start)
{
	vector<int> distance(V, UNKNOWN);
	vector<bool> visited(V, false);

	distance[start] = 0;

	for (int i = 0; i < V - 1; i++)
	{
		// 방문하지 않은 정점 중에서 최소 거리 정점을 찾음
		int curr = GetMinDistance(distance, visited);

		visited[curr] = true;

		for (auto& e : edges)
		{
			// 인접한 정점만 고려
			if (e.src != curr)
				continue;

			// 이미 방문했으면 무시
			if (visited[e.dst])
				continue;

			if (distance[curr] != UNKNOWN &&
				distance[e.dst] > distance[curr] + e.weight)
			{
				distance[e.dst] = distance[curr] + e.weight;
			}
		}
	}

	return distance;
}

void Johnson(vector<Edge> edges, int V)
{
	// 더미 정점을 추가한 그래프에서 최단 거리를 계산
	vector<int> h = BellmanFord(edges, V);

	if (h.empty())
		return;

	// 에지 가중치 재설정
	for (auto& e : edges)
	{
		e.weight += (h[e.src] - h[e.dst]);
	}

	// 모든 정점들 사이의 최단 거리를 저장
	vector<vector<int>> shortest(V);

	for (int i = 0; i < V; i++)
	{
		shortest[i] = Dijkstra(edges, V, i);
	}

	// 가중치 변환 수식을 역으로 적용하여 최단 거리를 출력
	for (int i = 0; i < V; i++)
	{
		cout << i << ":\n";

		for (int j = 0; j < V; j++)
		{
			if (shortest[i][j] != UNKNOWN)
			{
				shortest[i][j] += h[j] - h[i];

				cout << "\t" << j << ": " << shortest[i][j] << endl;
			}
		}
	}
}

int main()
{
	int V = 5;              // 정점 개수
	vector<Edge> edges;     // 에지 포인터의 벡터

	vector<vector<int>> edge_map{ // {시작 정점, 목표 정점, 가중치}
		{0, 1, -7},
		{1, 2, -2},
		{2, 0, 10},
		{0, 3, -5},
		{0, 4, 2},
		{3, 4, 4}
	};

	for (auto& e : edge_map)
	{
		edges.emplace_back(Edge{ e[0], e[1], e[2] });
	}

	Johnson(edges, V);
}