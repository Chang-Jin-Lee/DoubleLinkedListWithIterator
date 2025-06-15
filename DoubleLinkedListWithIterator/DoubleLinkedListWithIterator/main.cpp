#include "DoubleLinkedList.h"
#include <iostream>
#include <list>

int main()
{
	/*
	* std::list�� ����� ����
	*/
	std::list<int> testList(5, 30);
	for (const auto& item : testList)
	{
		std::cout << item << std::endl;
	}
	testList.clear();
	testList.merge(std::list<int>(5, 10));
	testList.max_size();

	std::list<int> tList(5, 5);
	auto it = testList.begin();
	it++;
	testList.splice(it, tList);

	std::cout << "===============================" << '\n';
	for (const auto& item : testList)
	{
		std::cout << item << std::endl;
	}
	std::cout << "===============================" << '\n';
	for (const auto& item : tList)
	{
		std::cout << item << std::endl;
	}

	constexpr auto _Unsigned_max = static_cast<std::make_unsigned_t<long long>>(-1);
	std::cout << _Unsigned_max << '\n';

	constexpr auto _Unsigned_max2 = static_cast<std::make_unsigned_t<int>>(-1);
	std::cout << _Unsigned_max2 << '\n';

	/*
	* DoubleLinkedList�� ����� ����
	*/
	DoubleLinkedList<int> MyList;
	MyList.push_back(10);
	MyList.push_back(20);
	MyList.push_back(30);
	MyList.push_back(40);
	MyList.push_back(50);

	// ũ�� �׽�Ʈ
	std::cout << "List(10,20,30,40,50) �� ũ���Դϴ�. : " << MyList.size() << std::endl;

	// ù ��° ���� ���
	std::cout << "List�� ù ��° ���Ҵ� : " << MyList.front() << std::endl;

	// ������ ���� ���
	std::cout << "List�� ������ ���Ҵ� : " << MyList.back() << std::endl;

	// ���� �׽�Ʈ
	std::cout << "List�� ������ 30�� �����մϴ�. " << std::endl;
	DoubleLinkedList<int>::Node* pFind = MyList.find(30);
	MyList.erase(pFind);

	// ��ü ����� ���
	std::cout << "List�� ���Ҹ� ��� ����մϴ�. " << std::endl;
	DoubleLinkedList<int>::Iterator iter = MyList.begin();
	for (; iter != MyList.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}

	// ��ü ����� �Ųٷ� ���
	std::cout << "List�� ���Ҹ� �Ųٷ� ��� ����մϴ�. " << std::endl;
	DoubleLinkedList<int>::Reverse_Iterator rIter = MyList.rbegin();
	for (; rIter != MyList.rend(); ++rIter)
	{
		std::cout << *rIter << std::endl;
	}

	// ù ��° ���Ҹ� pop_front()�� ����
	int iFront = MyList.front();
	MyList.pop_front();
	std::cout << "pop_front()�� ������ ù ��° ���Ҵ� : " << iFront << std::endl;

	// ������ ���Ҹ� pop_back()�� ����
	int iBack = MyList.back();
	MyList.pop_back();
	std::cout << "pop_back()�� ������ ������ ���Ҵ� : " << iBack << std::endl;

	// ��� �ִ��� Ȯ��
	if (MyList.empty())
	{
		std::cout << "List�� ��� �ֽ��ϴ�." << std::endl;
	}
	else
	{
		std::cout << "List�� ��� ���� �ʽ��ϴ�." << std::endl;
	}

	// ����Ʈ�� ���ϴ�.
	std::cout << "List�� ���� ����ϴ�." << std::endl;
	MyList.clear();
	if (MyList.empty())
	{
		std::cout << "List�� ��� �ֽ��ϴ�." << std::endl;
	}
	else
	{
		std::cout << "List�� ��� ���� �ʽ��ϴ�." << std::endl;
	}
}
