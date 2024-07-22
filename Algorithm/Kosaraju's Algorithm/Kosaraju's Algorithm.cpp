// 별개의 내용!
// 
// Directed Graph vs Undirected Graph
// 만약에 정말 큰 그래프가 여러개가 있다고 하자, 그리고 이걸 잘 분리해서 연관성을 찾고 싶다고 하자.
// Directed Graph 는 하나의 큰 그래프 안에 독립적인 여러개의 Graph 로 연관을 묶어버릴수는 있으나, 연관성과는 적합하지 않는다.
// 왜냐하면, "독립" Graph 는 다른 Graph 들의 사이에서 Edge 를 연결할수 없기때문에, 연관성을 표현하기가 쉽지 않기 때문이다.

// 반면에, Directed Graph 같은 경우는, 이 "연관성" 또는 "유사성" 을 Strong Connected Component 로 표현할수 있으며, 
// 즉 이말은 즉슨 모든 Edge 가 각각 의 Graph 가 연결되어있다 라는걸 표현할수 있다.
//
// Strong Connected Component 
// 
// 1  ->  0 -> 3
// ^           |
// |   /	   4
// 2 <
// Kosaraju's Algorithm
// - DFS 를 두번 수행 (한번은 입력 Graph 에 대해서 DFS 수행 | 두번째는 입력 그래프를 "전치(Transpose)" 시켜서 수행

// Graph 의 전치란? => 쉽게 말해서 Edge 의 방향을 바꿔버린다는 점
// 1. DFS 를 실행하면서, Visited 와 Stack 을 계속 Update 한다.
// 2. Stack 에서 하나씩 꺼내면서, 전치된 Graph 에서 Strongly Connected Component 를 찾는다.

// Kosaraji's 는 결국 Strongly Connected Component 를 찾으면서, 노드들의 연관성을 표현하기 위해서 사용된다.

#include <vector>
#include <stack>
#include <iostream>
using namespace std;

void FillStack(int node, vector<bool>& visited, vector<vector<int>>& adj, stack<int>& stack)
{
	visited[node] = true;
	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			FillStack(next, visited, adj, stack);
		}
	}
	stack.push(node);
}

void CollectConnectedComponents(int node, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& component)
{
	visited[node] = true;
	component.emplace_back(node);

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			CollectConnectedComponents(next, visited, adj, component);
		}
	}
}

vector<vector<int>> Transpose(int V, vector<vector<int>> adj)
{
	vector<vector<int>> transpose(V);
	for (int i = 0; i < V; i++)
	{
		for (auto next : adj[i])
		{
			transpose[next].emplace_back(i);
		}
	}
	return transpose;
}


vector<vector<int>> kosaraju(int V, vector<vector<int>> adj)
{
	vector<bool>visited(V, false);
	stack<int> stack;
	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			FillStack(i, visited, adj, stack);
		}
	}

	vector<vector<int>> transpose = Transpose(V, adj);
	fill(visited.begin(), visited.end(), false);

	vector<vector<int>> connectedComponent;

	while (!stack.empty())
	{
		int node = stack.top();
		stack.pop();

		if (!visited[node])
		{
			vector<int> component;
			CollectConnectedComponents(node, visited, transpose, component);
			connectedComponent.emplace_back(component);
		}
	}

	return connectedComponent;
}

int main()
{
	int V = 9;

	vector<vector<int>> adj =
	{
		{ 1, 3 },
		{ 2, 4 },
		{ 3, 5 },
		{ 7 },
		{ 2 },
		{ 4, 6 },
		{ 7, 2 },
		{ 8 },
		{ 3 }
	};

	vector<vector<int>> connectedComponents = kosaraju(V, adj);

	cout << "강한 연결 요소 개수: " << connectedComponents.size() << endl;

	for (int i = 0; i < connectedComponents.size(); i++)
	{
		cout << "[" << i + 1 << "] ";

		for (auto node : connectedComponents[i])
			cout << node << " ";

		cout << endl;
	}
}