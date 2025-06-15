#pragma once
/*
* 	@brief Iterator를 지원하는 이중 연결 리스트 클래스입니다.
*   @details 이 클래스는 이중 연결 리스트를 구현하며, 노드를 순회할 수 있는 반복자(iterator)가 있습니다.
*   @templte param T 저장할 데이터의 타입을 지정합니다.
* 	@note 이 클래스는 C++ 표준 라이브러리의 std::list와 유사한 기능을 제공합니다.
*/

/*
*  제공하는 메서드
* @ Insert() 특정 위치에 데이터를 삽입
* @ push_back() 리스트의 끝에 데이터를 추가
* @ push_front()  리스트의 시작에 데이터를 추가
* @ pop_front() 리스트의 시작 데이터를 제거
* @ pop_back() 리스트의 끝 데이터를 제거
* @ find() 특정 데이터를 찾고 해당 노드를 반환
* @ erase() 특정 노드를 제거
* @ remove() 특정 데이터를 가진 노드 제거
* @ clear() 리스트의 모든 데이터를 제거
* @ size() 리스트의 크기 반환
* @ front() 리스트의 첫 번째 데이터 반환
* @ back() 리스트의 마지막 데이터 반환
* @ empty() 리스트가 비어있는지 확인
*/
template<typename T>
class DoubleLinkedList
{
public:
	//  +-------- + +-------- +
	// | m_head | <-> | m_tail |
	//	+-------- + +-------- +
	DoubleLinkedList()
	{
		m_head.next = &m_tail;
		m_tail.prev = &m_head;
		m_size = 0;
	}
	~DoubleLinkedList() {}

	/*
	* 	@brief 	이중 연결 리스트의 노드를 순회할 수 있는 반복자(iterator) 구조체입니다.
	* 	@details 이 구조체는 이중 연결 리스트의 노드를 순회할 수 있도록 구현되어 있습니다.
	*/
	struct Iterator
	{
		using NodePtr = typename DoubleLinkedList<T>::Node*;
		NodePtr current;
		Iterator(NodePtr node) : current(node) {}
		T& operator*()
		{
			return current->data;
		}
		Iterator& operator++()
		{
			current = current->next;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator temp = *this;
			++(*this);
			return temp;
		}
		bool operator!=(const Iterator& other) const
		{
			return current != other.current;
		}
		void operator =(NodePtr node)
		{
			current = node;
		}
	};

	Iterator begin() { return Iterator(m_head.next); }
	Iterator end() { return Iterator(&m_tail); }

	/*
	* 	@brief 	이중 연결 리스트의 노드를 순회할 수 있는 반복자(Reverse_Iterator) 구조체입니다.
	* 	@details 이 구조체는 이중 연결 리스트의 노드를 거꾸로 순회할 수 있도록 구현되어 있습니다.
	*/
	struct Reverse_Iterator
	{
		using NodePtr = typename DoubleLinkedList<T>::Node*;
		NodePtr current;
		Reverse_Iterator(NodePtr node) : current(node) {}
		T& operator*()
		{
			return current->data;
		}
		Reverse_Iterator& operator++()
		{
			current = current->prev;
			return *this;
		}
		Reverse_Iterator operator++(int)
		{
			Reverse_Iterator temp = *this;
			++(*this);
			return temp;
		}
		bool operator!=(const Reverse_Iterator& other) const
		{
			return current != other.current;
		}
		void operator =(NodePtr node)
		{
			current = node;
		}
	};

	Reverse_Iterator rbegin() { return Reverse_Iterator(m_tail.prev); }
	Reverse_Iterator rend() { return Reverse_Iterator(&m_head); }

	/*
	* 	@brief 데이터가 저장될 노드입니다. 이전, 이후 포인터를 저장합니다.
	*/
	struct Node
	{
		T data;
		Node* next;
		Node* prev;
		Node() : data(0), next(nullptr), prev(nullptr) {}
		Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
	};

private:
	Node m_head; // dummy head (non-data)
	Node m_tail; // dummy tail (non-data)
	int m_size = 0;

public:
	Node* Insert(Node* prevNode, const T& value)
	{
		Node* newNode = new Node(value);
		newNode->prev = prevNode->prev;
		newNode->next = prevNode;
		prevNode->prev->next = newNode;
		prevNode->prev = newNode;
		++m_size;
		return newNode;
	}

	// 리스트가 비어있는지 아닌지에 따라 다르게 처리합니다.
	void push_back(const T& value)
	{
		Insert(&m_tail, value);
	}

	// 찾지 못했다면 end()를 반환합니다.
	Node* find(const T& value)
	{
		Node* current = m_head.next;
		while (current != &m_tail)
		{
			if (current->data == value)
				return current;
			current = current->next;
		}
		return &m_tail; // end()
	}

	Node* erase(Node* node)
	{
		if (node == &m_head || node == &m_tail) return nullptr;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		Node* next = node->next;
		delete node;
		--m_size;
		return next;
	}

	void remove(const T& value)
	{
		Node* node = find(value);
		if (node != nullptr)
		{
			erase(node);
		}
	}

	void clear()
	{
		Node* cur = m_head.next;
		while (cur != &m_tail)
		{
			Node* temp = cur->next;
			delete cur;
			cur = temp;
		}
		m_head.next = &m_tail;
		m_tail.prev = &m_head;
		m_size = 0;
	}

	int size() const
	{
		return m_size;
	}

	T& front() const
	{
		return m_head.next->data;
	}

	T& back() const
	{
		return  m_tail.prev->data;
	}

	void push_front(const T& value)
	{
		Insert(m_head.next, value);
	}

	void push_back(Node* node)
	{
		if (node == nullptr)
		{
			return; // nullptr인 경우 아무것도 하지 않습니다.
		}
		if (m_tail == nullptr)
		{
			m_head = m_tail = node;
			node->next = nullptr;
			node->prev = nullptr;
		}
		else
		{
			m_tail->next = node;
			node->prev = m_tail;
			node->next = nullptr;
			m_tail = node;
		}
		m_size++;
	}

	void pop_front()
	{
		if (empty() == false);
		erase(m_head.next);
	}

	void pop_back()
	{
		if (empty() == false)
			erase(m_tail.prev);
	}

	bool empty() const
	{
		return m_size == 0;
	}

	void splice(Iterator& it, DoubleLinkedList<T>& list)
	{
		if (list.empty()) return;

		Node* pos = it.current;
		Node* first = list.m_head.next;
		Node* last = list.m_tail.prev;

		// 연결
		first->prev = pos->prev;
		pos->prev->next = first;
		last->next = pos;
		pos->prev = last;

		// list를 비움
		list.m_head.next = &list.m_tail;
		list.m_tail.prev = &list.m_head;

		m_size += list.m_size;
	}
};