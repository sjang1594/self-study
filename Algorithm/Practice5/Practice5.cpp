/* Practice 5:
* Assume that we would like to process the big maount of DNA sequences.
* To get the similarity, we need sorted DNA sequences, and since those data are quite big, 
*/
#include <iostream>
#include <vector>
#include <algorithm>

struct node
{
	int data;
	int listPosition;
	int dataPosition;
};

std::vector<int> merge(const std::vector<std::vector<int>>& data)
{
	std::vector<node> heap;

	auto comparator = [](const node& left, const node& right) {
		if (left.data == right.data)	
			return left.listPosition > right.listPosition;
		return left.data > right.data; };

	for (int i = 0; i < data.size(); i++)
	{
		heap.push_back({ data[i][0], i, 0 });
		std::push_heap(heap.begin(), heap.end(), comparator);
	}

	std::vector<int> result;
	while (!heap.empty())
	{
		std::pop_heap(heap.begin(), heap.end(), comparator);
		auto min = heap.back();
		heap.pop_back();

		result.push_back(min.data);
		int nextIndex = min.dataPosition + 1;
		if (nextIndex < data[min.listPosition].size())
		{
			heap.push_back({ data[min.listPosition][nextIndex], min.listPosition, nextIndex });
			std::push_heap(heap.begin(), heap.end(), comparator);
		}
	}

	return result;
}

int main()
{
    // list is already sorted.
	std::vector<int> v1 = { 1, 3, 8, 15, 105 };
	std::vector<int> v2 = { 2, 3, 10, 11, 16, 20, 25 };
	std::vector<int> v3 = { -2, 100, 1000 };
	std::vector<int> v4 = { -1, 0, 14, 18 };

	std::vector<int> resultData = merge({ v1, v2, v3, v4 });

	for (auto i : resultData)
		std::cout << i << ' ';
	std::cout << std::endl;

	return 0;
}