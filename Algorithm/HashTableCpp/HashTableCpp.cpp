/* C++ Hash Table 
*  문자열의 모든 문자에 대한 ASCII 코드값을 모두 더한 후에 모듈로 연산
*  그러나 여기서의 문자로 구성된 문자열이 많아지게 되면, 충돌이 많아져서 rehasing 이 많이 된다.
*  
*  C++ 문자열로부터 해시 값을 생성하는 용도로 std::hash<std::string>(std::string) 함수 객체가 존재한다.
*  이 객체 내부에서는 Hash 함수 알고리즘이 구현 되어있다.
* 
*  unordered_set 은 Key 만 저장 | unordered_map 은 Key 와 Value 로 저장
*  두 컨테이너는 모두 체이닝을 사용하는 HashTable 형태로 구현되어있음
*  쵀대 1 의 부하율을 가지므로, 만약 해시 테이블 크기보다 원소 개수가 많아지게 되면, 곧바로 HashTable 의 크기를 키우고
*  Rehasing 을 시킴, 그러면 load factor 을 1 보다 적게 가져갈수 있음
* 
*  unordered_map 같은 경우 Key 와 Value 를 쌍으로 저장을 하고, [] 연산자를 통해서 키를 이용해, 값(Value) 를 가지고 올수 있다.
*  [] 연산자는 Reference 로 반환하기 때문에 저장된값을 변경도 가능하다.
* 
*  etc: rehash(), bucket_count()
*  
*  Std::vector
*  [] -> [] -> [] (std::list) => Bucket
*  []
*  []
*  []
*  std::unordered_set & std::unordered_map 은 중복키 허용하지 않음, 만약에 중복을 허용하고 싶다면, std::unordered_multiset 또는
*  std::unordered_multimap 을 이용. 이 두 Container 의 함수는 주어진 키가 이미 존재하는지를 검사하지 않음
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>

void print(const std::unordered_set<int>& container)
{
	for (const auto& elem : container)
		std::cout << elem << std::endl;
	std::cout << std::endl;
}

void print(const std::unordered_map<int, int>& container)
{
	for (const auto& elem : container)
		std::cout << elem.first << ": " << elem.second << std::endl;
	std::cout << std::endl;
}

void find(const std::unordered_set<int>& container, const int elem)
{
	if (container.find(elem) != container.end())
		std::cout << elem << " Search Succesed " << std::endl;
	else
		std::cout << elem << " Search Failed " << std::endl;
}

void find(const std::unordered_map<int, int>& container, const int elem)
{
	auto iter = container.find(elem);
	if (iter == container.end())
		std::cout << elem << " Search Failed " << std::endl;
	else
		std::cout << elem << " Search Success " << std::endl;
}

int main()
{
	std::cout << " std::unordered_set " << std::endl;
	std::unordered_set<int> set1{ 1, 2, 3, 4 };
	std::cout << " set1 initial value ";
	print(set1);

	set1.insert(2);
	std::cout << " insert 2 ";
	print(set1);

	set1.insert(10);
	set1.insert(300);
	std::cout << " insert 10, 300";
	print(set1);

	find(set1, 4);
	find(set1, 100);

	set1.erase(2);
	std::cout << " remove 2";
	print(set1);

	find(set1, 2);

	std::cout << " std::unordered_map " << std::endl;
	std::unordered_map<int, int> squareMap;
	squareMap.insert({ 2, 4 });
	squareMap[3] = 9;
	std::cout << " insert 2^2 and 3^2 ";
	print(squareMap);

	squareMap[20] = 400;
	squareMap[30] = 900;
	std::cout << " insert 20^2 and 30 ^2 ";

	find(squareMap, 10);
	find(squareMap, 20);
	print(squareMap);

	return 0;
}