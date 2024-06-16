#include <iostream>
#include <queue>

// Chapter 2: 비선형인 구조 (Container: 선형적으로 데이터들을 저장, 순회하는 방법은 역방향, 순방향)
// Stack, queue, priority queue (abstrat)
// Tree, Heap, Graph (std::vector, std::list, ... )
// B-Tree (Database), Huffman Tree (Data Encoding / Compression), Graph Coloring, 
// Assignment Problem, Minimum Distance Problem

// 계층적 구조 -> Tree 
// 순환적 구조 (종속성) Graph Problem

using namespace std;

//   Node (std::string)
//  /    \
// left  right

struct Node
{
	std::string position;	// ex: CTO / Tech Lead / CFO
	Node* left;				// left
	Node* right;			// right
};

//       CEO
//    /      \
// nullptr nullptr

struct orgTree
{
	Node* root;

	static orgTree createOrgStructure(const std::string& pos)
	{
		orgTree tree;
		tree.root = new Node{ pos, nullptr, nullptr };
		return tree;
	}

	// find the element (value) in the root
	static Node* find(Node* root, const std::string& value)
	{
		if (root == nullptr) return nullptr;
		// attempt to find the root
		if (root->position == value) return root;

		// attempt to find the left element
		Node* firstFound = orgTree::find(root->left, value);
		if (firstFound != nullptr) return firstFound;

		// attempt to find the right element
		return orgTree::find(root->right, value);
	}

	// add subordinate
	bool addSubordinate(const std::string& manager, const std::string& subordinate)
	{
		Node* managerNode = orgTree::find(root, manager);
		if (!managerNode)
		{
			std::cout << manager << " Can't be found in the Organization Tree" << endl;
			return false;
		}

		// if managerNode has its own children, do not add
		if (managerNode->left && managerNode->right)
		{
			std::cout << manager << " Can't be added into the Organization Tree" << std::endl;
			return false;
		}

		// but if managernode's children is empty, then add
		if (!managerNode->left)
			managerNode->left = new Node{ subordinate, nullptr, nullptr };
		else
			managerNode->right = new Node{ subordinate, nullptr, nullptr };

		return true;
	}

	// Preorder (root node -> left node -> right node)
	static void preOrder(Node* node)
	{
		if (node == nullptr) return; // if(!root)
		std::cout << node->position << ", ";
		preOrder(node->left);
		preOrder(node->right);
	}

	// In-order (left node -> root node -> right node)
	static void inOrder(Node* node)
	{
		if (node == nullptr) return; // if(!root)
		inOrder(node->left);
		std::cout << node->position << ", ";
		inOrder(node->right);
	}

	// Post order  (left node -> right node-> root node)
	static void PostOrder(Node* node)
	{
		if (node == nullptr) return;
		PostOrder(node->left);
		PostOrder(node->right);
		std::cout << node->position << ", ";
	}

	static void levelOrder(Node* node)
	{
		if (node == nullptr) return;
		std::queue<Node*> q;

		while (!q.empty())
		{
			int size = q.size();
			for (int i = 0; i < size; i++)
			{
				Node* current = q.front();
				q.pop();

				std::cout << current->position << ", ";
				if (current->left)
					q.push(current->left);
				if (current->right)
					q.push(current->right);
				std::cout << std::endl;
			}
		}
	}
	// Level 0 : CEO
	// Level 1 : Technial Lead | Hr Coordinator
	// Level 2 : Team Lead
	// Level 3 : Engineer

};


int main()
{
	orgTree tree = orgTree::createOrgStructure("CEO");
	tree.addSubordinate("CEO", "Technical Lead");
	tree.addSubordinate("Techincal Lead", "Team Lead");
	tree.addSubordinate("Team Lead", "Engineeer");
	tree.addSubordinate("CEO", "Hr Coordinator");

	orgTree::preOrder(tree.root);

	return 0;
}