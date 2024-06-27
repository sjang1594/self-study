// KnapsackProblem.cpp => Dynamic Programming or Greedy

// 일반적인 Kapsack problem 은 NP Problem 이다. 왜?! 
// 
// 1. Fractional Knapsack Problem (****) => Greedy
// 
// 2. 0/1 Knapsack Problem => Greedy(X)
// 
// 
// 그래서 Greedy 한 답이 정확한 답이 아닐수있다. (2^n)
// 
// Given a set of objects which have both a value and a weight (vi, wi) what is the maximum value we can obtain
// by selecting a subset of these objects such that the sum of the wieghts does not exceed a certain capacity)
// *** But Cannot take fractional items or one item more than once.
// 
// Kapsack 은 도둑이 이제 다이아몬드를 훔치려고 한다. 하지만 가방의 크기는 정해져있고, 내가 너무 많이 가져가게 되면, 가방은 터져 버린다.
// 도둑이 최대한 돈을 많이 벌수 있는 방법은?

// Wiki     :   https://en.wikipedia.org/wiki/Knapsack_problem
// Youtube  :   https://www.youtube.com/watch?v=cJ21moQpofY
//              https://www.youtube.com/watch?v=rhda6lR5kyQ
// 배경설명  :   무게 제한이 있는 (7Kg) 가방에, 최대 Value 는 몇인가 
// Ex)      :   Weight Limit = 7 Kg
//          :   Item    1   2   3   4   5
//          :   value | 2 | 2 | 4 | 5 | 3 |
//          :   weight| 3 | 1 | 3 | 4 | 2 |

// How to solve this naively for optimal substructure
// Items \ Knapsack capcity
//            |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |
// empty      |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
// v1=2,w1=3  |   0   |   0   |   0   |   2   |   2   |   2   |   2   |   2   |
// v2=2,w2=1  |   0   |   2   |   2   |   2   |   4   |   4   |   4   |   4   |
// v3=4,w3=3  |   0   |   2   |   2   |   4   |   6   |   6   |   6   |   6   |
// v4=5,w4=4  |   0   |   2   |   2   |   4   |   6   |   7   |   7   |   9   |
// v5=3,w5=2  |   0   |   2   |   3   |   5   |   6   |   7   |   9   |   10  |

// How to select ?
// Subtract weight
// w5, w4, w2

// Fractional Knapsack problem 은 Greedy 방식으로 해결 가능ㅎ다.
// 결국에는 뭘하냐?
// Price / weight
//                A    B      C   D     E   F     G
// weight       | 1  | 2   |  5 | 9   | 2 | 3   | 4
// price        | 10 | 7   | 15 | 10  | 12| 11  | 5
// price/weight | 10 | 3.5 |  3 | 1.11|  6| 3.67| 1.25

// Weight = 8
// A + E + F + B (1 + 2 + 3 + 2)

#include <iostream>
#include <algorithm>
#include <vector>

struct Object
{
    int id;
    int weight;
    double value;
    double value_per_unit_weight;

    Object(int i, int w, double v) : id(i), weight(w), value(v)
    {
        value_per_unit_weight = v / w;
    }

    inline bool operator <(const Object& obj) const
    {
        return this->value_per_unit_weight < obj.value_per_unit_weight;
    }

    friend std::ostream& operator<<(std::ostream& os, const Object& obj);
};

std::ostream& operator<<(std::ostream& os, const Object& obj)
{
    os << "[" << obj.id << "] price: " << obj.value
        << "\t weight: " << obj.weight << " kg\t price per unit weight: " << obj.value_per_unit_weight;
    return os;
}

auto fill_knapsack(std::vector<Object>& objects, int knapsack_capacity)
{
    std::vector<Object> knapsack_contents;
    knapsack_contents.reserve(knapsack_capacity);

    std::sort(objects.begin(), objects.end());
    std::reverse(objects.begin(), objects.end());

    auto current_object = objects.begin();
    int current_total_weight = 0;
    while (current_total_weight < knapsack_capacity && current_object != objects.end())
    {
        knapsack_contents.push_back(*current_object);
        current_total_weight += current_object->weight;
        current_object++;
    }

    int weight_of_last_obj_to_remove = current_total_weight - knapsack_capacity;
    Object& last_object = knapsack_contents.back();
    if (weight_of_last_obj_to_remove > 0)
    {
        last_object.weight -= weight_of_last_obj_to_remove;
        last_object.value -= last_object.value_per_unit_weight * weight_of_last_obj_to_remove;
    }
    return knapsack_contents;
}

int main()
{
    int num_object = 7;
    std::vector<Object> objects;
    objects.reserve(num_object);
    std::vector<int> weight{ 1, 2, 5, 9, 2, 3, 4 };
    std::vector<double> values{ 10, 7, 15, 10, 12, 11, 5 };
    for (auto i = 0; i < num_object; i++)
    {
        objects.push_back(Object(i + 1, weight[i], values[i]));
    }

    for (auto& output : objects)
        std::cout << output << std::endl;
    std::cout << std::endl;
    
    int knapsack_capacity = 7;
    auto solution = fill_knapsack(objects, knapsack_capacity);
    for (auto& output : solution)
        std::cout << output << std::endl;
    std::cout << std::endl;
}