#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <list>

// Priority Queue
// O(1)     : 최대 / 최소 원소에 대한 즉각적으로 접근
// O(logN)  : 원소 삽입에 대한 시간 복잡도
// O(logN)  : 최대 원소 삭제에 대한 시간 복잡도

// Complete Binary Tree
// 1. Every Node have two chilren Node except last level. (Left to right)
// 2. Can save the element in an array / list / vector
//		1. save the root node into first element in an array
//		2. In the next level, save left to right 
//    ** Very effective in a way that the pointer don't have to be saved.

// Example: 
//          17
//       /      \
//      15       13
//	  /   \    /  \
//	 5     7  4    3
//  / \   /
// 2   0 6

// Complete Binary Tree Array : [10 9 8 5 7 4 3 2 0 6]
// if I have an index i for representing the parent node, then to find the child node: 2 * i + 1 is child node or 2 * i + 2.
// if I have an index i for representing the child node, then to find the parent node: the parent node for 7(index=4) would be (i - 1)/ 2

// Heaps Invariants
// 1. Access the max element instantaneously (that's why the max element in in the root) -> Max Heap | Min Heap
// 2. which extends to the idea that, the parent node should be bigger than the children node.
// 3. Swap (If we are to insert the last element into last tree level, then we need to compare the value, and update the tree)

// Heap: Insert the element
// Keep swaping if the incoming element is greater than the root node, if not just update the tree

// Heap: Delete the element
// In heap, only the max (element) will be deleted.
// If the max element is deleted, then which one would be replacement for the root !?
// ------------------------------------------------------------------------------
// If the max element is deleted, then the last element in the last level will be swap, then delete the last node.
// if the invariant doesn't satisfied, swap uptil the invariant is stabilized.
// Olog(N)

// Heap: Initialization
// Heapification Algorithm => O(N)

void heapify(int arr[], int N, int i)
{
	int largest = i;
	int left = 2 * i + 1;  // left: 2 * i + 1
	int right = 2 * i + 2; // right: 2 * i + 2

	// If the left child is larger than a root
	if (left < N && arr[left] > arr[largest])
		largest = left;
	
	// If the right child is larger than largest
	if (right < N && arr[right] > arr[largest])
		largest = right;

	// if the root is not a maximum value, then swap
	if (largest != i)
	{
		std::swap(arr[i], arr[largest]);
		heapify(arr, N, largest);
	}
}

void buildHeap(int arr[], int N)
{
	int startIdx = (N / 2) - 1;
	for (int i = startIdx; i >= 0; i--)
	{
		heapify(arr, N, i);
	}
}

void printHeap(int arr[], int N)
{
	std::cout << "Array representation of Heap is:\n";

	for (int i = 0; i < N; ++i)
		std::cout << arr[i] << " ";
	std::cout << "\n";
}

int main()
{
	int arr[] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
	int N = sizeof(arr) / sizeof(arr[0]);
	// buildHeap(arr, N);
	// printHeap(arr, N);

	// std 에서 지원
	// std::make_heap(arr, arr + N);
	//std::make_heap(arr, arr + 10, [](int _t1, int _t2) -> bool {
	//	return (_t1 < _t2); });

	//std::make_heap(arr, arr + 10, std::less<int>()); // Max Heap
	//std::make_heap(arr, arr + 10, std::greater<int>()); // Min Heap

	// list
	// std::array<int, 11> heapArr = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
	// std::make_heap(heapArr.begin(), heapArr.end());

	// vector 
	std::vector<int> heapVec = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
	std::make_heap(heapVec.begin(), heapVec.end());
	for (auto& i : heapVec)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;;
	heapVec.push_back(100);
	std::cout << "Pushing 100 to vector" << std::endl;
	for (auto& i : heapVec)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;
	std::cout << "Heapifying after 100 into vector " << std::endl;
	std::push_heap(heapVec.begin(), heapVec.end(), std::less<int>());
	for (auto& i : heapVec)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;
	std::cout << "After poping heap" << std::endl;
	std::pop_heap(heapVec.begin(), heapVec.end());
	for (auto& i : heapVec)
	{
		std::cout << i << " ";
	}

	std::cout << " " << std::endl;
	int i = heapVec.back();
	heapVec.pop_back();
	
	for (auto& i : heapVec)
	{
		std::cout << i << " ";
	}
	// sort_heap / pop_heap()
	
	return 0;
}
