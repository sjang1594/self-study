/* C++ Hash Table 
*  ���ڿ��� ��� ���ڿ� ���� ASCII �ڵ尪�� ��� ���� �Ŀ� ���� ����
*  �׷��� ���⼭�� ���ڷ� ������ ���ڿ��� �������� �Ǹ�, �浹�� �������� rehasing �� ���� �ȴ�.
*  
*  C++ ���ڿ��κ��� �ؽ� ���� �����ϴ� �뵵�� std::hash<std::string>(std::string) �Լ� ��ü�� �����Ѵ�.
*  �� ��ü ���ο����� Hash �Լ� �˰����� ���� �Ǿ��ִ�.
* 
*  unordered_set �� Key �� ���� | unordered_map �� Key �� Value �� ����
*  �� �����̳ʴ� ��� ü�̴��� ����ϴ� HashTable ���·� �����Ǿ�����
*  ���� 1 �� �������� �����Ƿ�, ���� �ؽ� ���̺� ũ�⺸�� ���� ������ �������� �Ǹ�, ��ٷ� HashTable �� ũ�⸦ Ű���
*  Rehasing �� ��Ŵ, �׷��� load factor �� 1 ���� ���� �������� ����
* 
*  unordered_map ���� ��� Key �� Value �� ������ ������ �ϰ�, [] �����ڸ� ���ؼ� Ű�� �̿���, ��(Value) �� ������ �ü� �ִ�.
*  [] �����ڴ� Reference �� ��ȯ�ϱ� ������ ����Ȱ��� ���浵 �����ϴ�.
* 
*  etc: rehash(), bucket_count()
*  
*  Std::vector
*  [] -> [] -> [] (std::list) => Bucket
*  []
*  []
*  []
*  std::unordered_set & std::unordered_map �� �ߺ�Ű ������� ����, ���࿡ �ߺ��� ����ϰ� �ʹٸ�, std::unordered_multiset �Ǵ�
*  std::unordered_multimap �� �̿�. �� �� Container �� �Լ��� �־��� Ű�� �̹� �����ϴ����� �˻����� ����
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