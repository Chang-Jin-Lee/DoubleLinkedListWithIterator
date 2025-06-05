#include "DoubleLinkedList.h"
#include <iostream>
#include <list>

int main()
{
	/*
	* std::list를 사용한 예제
	*/
	std::list<int> testList(5, 30);
	for (const auto& item : testList)
	{
		std::cout << item << std::endl;
	}
	testList.clear();

	/*
	* DoubleLinkedList를 사용한 예제
	*/
	DoubleLinkedList<int> MyList;
	MyList.push_back(10);
	MyList.push_back(20);
	MyList.push_back(30);
	MyList.push_back(40);
	MyList.push_back(50);

	// 크기 테스트
	std::cout << "List(10,20,30,40,50) 의 크기입니다. : " << MyList.size() << std::endl;

	// 첫 번째 원소 출력
	std::cout << "List의 첫 번째 원소는 : " << MyList.front() << std::endl;

	// 마지막 원소 출력
	std::cout << "List의 마지막 원소는 : " << MyList.back() << std::endl;

	// 삭제 테스트
	std::cout << "List의 원소중 30을 제거합니다. " << std::endl;
	DoubleLinkedList<int>::Node* pFind = MyList.find(30);
	MyList.erase(pFind);   

	// 전체 목록을 출력
	std::cout << "List의 원소를 모두 출력합니다. " << std::endl;
	DoubleLinkedList<int>::Iterator iter = MyList.begin();
	for (; iter != MyList.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}

	// 전체 목록을 거꾸로 출력
	std::cout << "List의 원소를 거꾸로 모두 출력합니다. " << std::endl;
	DoubleLinkedList<int>::Reverse_Iterator rIter = MyList.rbegin();
	for (; rIter != MyList.rend(); ++rIter)
	{
		std::cout << *rIter << std::endl;
	}

	// 첫 번째 원소를 pop_front()로 제거
	DoubleLinkedList<int>::Node* pFront = MyList.pop_front();
	std::cout << "pop_front()로 제거한 첫 번째 원소는 : " << pFront->data << std::endl;

	// 마지막 원소를 pop_back()로 제거
	DoubleLinkedList<int>::Node* pBack = MyList.pop_back();
	std::cout << "pop_back()로 제거한 마지막 원소는 : " << pBack->data << std::endl;

	// 비어 있는지 확인
	if (MyList.empty())
	{
		std::cout << "List가 비어 있습니다." << std::endl;
	}
	else
	{
		std::cout << "List가 비어 있지 않습니다." << std::endl;
	}

	// 리스트를 비웁니다.
	std::cout << "List를 전부 지웁니다." << std::endl;
	MyList.clear();
	if (MyList.empty())
	{
		std::cout << "List가 비어 있습니다." << std::endl;
	}
	else
	{
		std::cout << "List가 비어 있지 않습니다." << std::endl;
	}
}
