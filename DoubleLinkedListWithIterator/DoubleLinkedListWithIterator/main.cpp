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
	DoubleLinkedList<int>::Node* pFront = MyList.pop_front();
	std::cout << "pop_front()�� ������ ù ��° ���Ҵ� : " << pFront->data << std::endl;

	// ������ ���Ҹ� pop_back()�� ����
	DoubleLinkedList<int>::Node* pBack = MyList.pop_back();
	std::cout << "pop_back()�� ������ ������ ���Ҵ� : " << pBack->data << std::endl;

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
