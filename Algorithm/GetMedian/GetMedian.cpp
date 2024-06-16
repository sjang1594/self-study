#include <iostream>
#include <queue>
#include <vector>

// std::priority_queue<Type, Struct(Data), Compare Operator>
// default std::priority_queue<int, vector<int>, less<int>> pq

struct median{
    std::priority_queue<int, std::vector<int>, std::less<int>> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    double get()
    {
        /* return the current median value depending on the size of */
        if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) / 2.0;
        if (maxHeap.size() < minHeap.size())
            return minHeap.top();
        return maxHeap.top();
    }

    void insert(int data)
    {
        /* Have to keep track the size of MinHeap & MaxHeap*/
        
        // If root is empty, create maxHeap
        if (maxHeap.size() == 0)
        {
            maxHeap.push(data);
            return;
        }

        // If the both of minHeap and MaxHeap size are same
        if (maxHeap.size() == minHeap.size())
        {
            // compare the current median value, if it's smaller than the data,
            // then push to maxHeap, otherwise minHeap
            if (data <= get())
                maxHeap.push(data);
            else
                minHeap.push(data);
            return;
        }

        /* if minHeap is greater than the maxHeap, then ready to push to maxHeap */
        /* */
        if (maxHeap.size() < minHeap.size())
        {
            // Get the current value, compare the incoming data with median.
            // if the data is bigger, then move min element to maxHeap, and push it to min.
            if (data > get())
            {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(data);
            }
            else
                maxHeap.push(data);
            return;
        }

        // First Iteration
        // if the data is smaller, then swap the maxHeap root to minHeap root
        if (data < get())
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            maxHeap.push(data);
        }
        else
            minHeap.push(data);
    }
};


int main()
{
    median median;

    median.insert(1);
    std::cout << "Insert 1, median value = " << median.get() << std::endl;

    median.insert(5);
    std::cout << "Insert 5, median value = " << median.get() << std::endl;

    median.insert(2);
    std::cout << "Insert 2, median value = " << median.get() << std::endl;

    median.insert(10);
    std::cout << "Insert 10, median value = " << median.get() << std::endl;

    median.insert(40);
    std::cout << "Insert 40, median value = " << median.get() << std::endl;

    return 0;
}