#pragma once
/*
* 	@brief Iterator�� �����ϴ� ���� ���� ����Ʈ Ŭ�����Դϴ�.
*   @details �� Ŭ������ ���� ���� ����Ʈ�� �����ϸ�, ��带 ��ȸ�� �� �ִ� �ݺ���(iterator)�� �ֽ��ϴ�.
*   @templte param T ������ �������� Ÿ���� �����մϴ�.
* 	@note �� Ŭ������ C++ ǥ�� ���̺귯���� std::list�� ������ ����� �����մϴ�.
*/

/*
*  �����ϴ� �޼���
* @ Insert() Ư�� ��ġ�� �����͸� ����
* @ push_back() ����Ʈ�� ���� �����͸� �߰�
* @ push_front()  ����Ʈ�� ���ۿ� �����͸� �߰�
* @ pop_front() ����Ʈ�� ���� �����͸� ����
* @ pop_back() ����Ʈ�� �� �����͸� ����
* @ find() Ư�� �����͸� ã�� �ش� ��带 ��ȯ
* @ erase() Ư�� ��带 ����
* @ remove() Ư�� �����͸� ���� ��� ����
* @ clear() ����Ʈ�� ��� �����͸� ����
* @ size() ����Ʈ�� ũ�� ��ȯ
* @ front() ����Ʈ�� ù ��° ������ ��ȯ
* @ back() ����Ʈ�� ������ ������ ��ȯ
* @ empty() ����Ʈ�� ����ִ��� Ȯ��
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
	* 	@brief 	���� ���� ����Ʈ�� ��带 ��ȸ�� �� �ִ� �ݺ���(iterator) ����ü�Դϴ�.
	* 	@details �� ����ü�� ���� ���� ����Ʈ�� ��带 ��ȸ�� �� �ֵ��� �����Ǿ� �ֽ��ϴ�.
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
	* 	@brief 	���� ���� ����Ʈ�� ��带 ��ȸ�� �� �ִ� �ݺ���(Reverse_Iterator) ����ü�Դϴ�.
	* 	@details �� ����ü�� ���� ���� ����Ʈ�� ��带 �Ųٷ� ��ȸ�� �� �ֵ��� �����Ǿ� �ֽ��ϴ�.
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
	* 	@brief �����Ͱ� ����� ����Դϴ�. ����, ���� �����͸� �����մϴ�.
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

	// ����Ʈ�� ����ִ��� �ƴ����� ���� �ٸ��� ó���մϴ�.
	void push_back(const T& value)
	{
		Insert(&m_tail, value);
	}

	// ã�� ���ߴٸ� end()�� ��ȯ�մϴ�.
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
			return; // nullptr�� ��� �ƹ��͵� ���� �ʽ��ϴ�.
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

		// ����
		first->prev = pos->prev;
		pos->prev->next = first;
		last->next = pos;
		pos->prev = last;

		// list�� ���
		list.m_head.next = &list.m_tail;
		list.m_tail.prev = &list.m_head;

		m_size += list.m_size;
	}
};