// ������ ����!
// 
// Directed Graph vs Undirected Graph
// ���࿡ ���� ū �׷����� �������� �ִٰ� ����, �׸��� �̰� �� �и��ؼ� �������� ã�� �ʹٰ� ����.
// Directed Graph �� �ϳ��� ū �׷��� �ȿ� �������� �������� Graph �� ������ ����������� ������, ���������� �������� �ʴ´�.
// �ֳ��ϸ�, "����" Graph �� �ٸ� Graph ���� ���̿��� Edge �� �����Ҽ� ���⶧����, �������� ǥ���ϱⰡ ���� �ʱ� �����̴�.

// �ݸ鿡, Directed Graph ���� ����, �� "������" �Ǵ� "���缺" �� Strong Connected Component �� ǥ���Ҽ� ������, 
// �� �̸��� �ｼ ��� Edge �� ���� �� Graph �� ����Ǿ��ִ� ��°� ǥ���Ҽ� �ִ�.
//
// Strong Connected Component 
// 
// 1  ->  0 -> 3
// ^           |
// |   /	   4
// 2 <
// Kosaraju's Algorithm
// - DFS �� �ι� ���� (�ѹ��� �Է� Graph �� ���ؼ� DFS ���� | �ι�°�� �Է� �׷����� "��ġ(Transpose)" ���Ѽ� ����

// Graph �� ��ġ��? => ���� ���ؼ� Edge �� ������ �ٲ�����ٴ� ��
// 1. DFS �� �����ϸ鼭, Visited �� Stack �� ��� Update �Ѵ�.
// 2. Stack ���� �ϳ��� �����鼭, ��ġ�� Graph ���� Strongly Connected Component �� ã�´�.

// Kosaraji's �� �ᱹ Strongly Connected Component �� ã���鼭, ������ �������� ǥ���ϱ� ���ؼ� ���ȴ�.

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

	cout << "���� ���� ��� ����: " << connectedComponents.size() << endl;

	for (int i = 0; i < connectedComponents.size(); i++)
	{
		cout << "[" << i + 1 << "] ";

		for (auto node : connectedComponents[i])
			cout << node << " ";

		cout << endl;
	}
}