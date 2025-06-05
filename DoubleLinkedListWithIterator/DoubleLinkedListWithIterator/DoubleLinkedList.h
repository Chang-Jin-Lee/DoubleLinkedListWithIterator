#pragma once
/*
* 	@brief Iterator�� �����ϴ� ���� ���� ����Ʈ Ŭ�����Դϴ�.
*   @details �� Ŭ������ ���� ���� ����Ʈ�� �����ϸ�, ��带 ��ȸ�� �� �ִ� �ݺ���(iterator)�� �ֽ��ϴ�.
*   @templte param T ������ �������� Ÿ���� �����մϴ�.
* 	@note �� Ŭ������ C++ ǥ�� ���̺귯���� std::list�� ������ ����� �����մϴ�.
*/

/*
*  �����ϴ� �޼��� 
* @ Insert() �޼��带 ����Ͽ� Ư�� ��ġ�� �����͸� ����
* @ push_back() �޼��带 ����Ͽ� ����Ʈ�� ���� �����͸� �߰�
* @ push_front() �޼��带 ����Ͽ� ����Ʈ�� ���ۿ� �����͸� �߰�
* @ pop_front() �޼��带 ����Ͽ� ����Ʈ�� ���ۿ��� �����͸� �����ϰ� ��ȯ
* @ pop_back() �޼��带 ����Ͽ� ����Ʈ�� ������ �����͸� �����ϰ� ��ȯ
* @ find() �޼��带 ����Ͽ� Ư�� �����͸� ã�� �ش� ��带 ��ȯ
* @ erase() �޼��带 ����Ͽ� Ư�� ��带 ����
* @ remove() �޼��带 ����Ͽ� Ư�� �����͸� ����
* @ clear() �޼��带 ����Ͽ� ����Ʈ�� ��� �����͸� ����
* @ size() �޼��带 ����Ͽ� ����Ʈ�� ũ�⸦ ��ȯ
* @ front() �޼��带 ����Ͽ� ����Ʈ�� ù ��° �����͸� ��ȯ
* @ back() �޼��带 ����Ͽ� ����Ʈ�� ������ �����͸� ��ȯ
* @ empty() �޼��带 ����Ͽ� ����Ʈ�� ����ִ��� Ȯ��
*/
template<typename T>
class DoubleLinkedList
{
public:
	DoubleLinkedList() {}
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

	Iterator begin() { return Iterator(m_head); }
	Iterator end() { return Iterator(m_tail->next); }

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

	Reverse_Iterator rbegin() { return Reverse_Iterator(m_tail); }
	Reverse_Iterator rend() { return Reverse_Iterator(m_head->prev); }

	/*
	* 	@brief �����Ͱ� ����� ����Դϴ�. ����, ���� �����͸� �����մϴ�.
	*/
	struct Node
	{
		T data;
		Node* next;
		Node* prev;
		Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
	};

	Node* m_head = nullptr;
	Node* m_tail = nullptr;
	int m_size = 0;

	Node* Insert(Node* prevNode, const T& value)
	{
		Node* newNode = new Node(value);
		// prevNode�� ����ִ��� �ƴ����� ���� �ٸ��� ó���մϴ�.
		if (prevNode == nullptr) 
		{
			newNode->next = m_head;
			if (m_head != nullptr) m_head->prev = newNode;
			m_head = newNode;
			if (m_tail == nullptr) m_tail = newNode; 
		}
		else
		{
			newNode->next = prevNode->next;
			newNode->prev = prevNode;
			prevNode->next = newNode;
			if (newNode->next != nullptr)
			{
				newNode->next->prev = newNode;
			}
			if (m_tail == prevNode) 
			{
				m_tail = newNode;
			}
		}
		return newNode;
	}

	// ����Ʈ�� ����ִ��� �ƴ����� ���� �ٸ��� ó���մϴ�.
	void push_back(const T& value)
	{
		if (m_tail == nullptr)
		{
			m_head = m_tail = new Node(value);
		}
		else
		{
			m_tail = Insert(m_tail, value);
		}
		m_size++;
	}

	// ã�� ���ߴٸ� end()�� ��ȯ�մϴ�.
	Node* find(const T& value)
	{
		Node* current = m_head;
		while (current != nullptr)
		{
			if (current->data == value)
			{
				return current;
			}
			current = current->next;
		}
		return m_tail->next;
	}

	Node* erase(Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->prev != nullptr)
		{
			node->prev->next = node->next;
		}
		if (node->next != nullptr)
		{
			node->next->prev = node->prev;
		}
		if (m_head == node)
		{
			m_head = node->next;
		}
		if (m_tail == node)
		{
			m_tail = node->prev;
		}
		delete node;
		m_size--;
		return m_head;
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
		Node* current = m_head;
		while (current != nullptr)
		{
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
		m_size = 0;
		m_head = m_tail = nullptr;
	}

	int size() const
	{
		return m_size;
	}

	T& front()
	{
		if (m_head == nullptr)
		{
			m_tail->next;
		}
		return m_head->data;
	}

	T& back()
	{
		if (m_tail == nullptr)
		{
			m_head->next;
		}
		return m_tail->data;
	}

	void push_front(const T& value)
	{
		if (m_head == nullptr)
		{
			m_head = m_tail = new Node(value);
		}
		else
		{
			Node* newNode = new Node(value);
			newNode->next = m_head;
			m_head->prev = newNode;
			m_head = newNode;
		}
		m_size++;
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

	Node* pop_front()
	{
		if (m_head == nullptr)
		{
			return m_tail->next; // ����Ʈ�� ��������� �ƹ��͵� ���� �ʽ��ϴ�.
		}
		Node* temp = m_head;
		m_head = m_head->next;
		if (m_head != nullptr)
		{
			m_head->prev = nullptr;
		}
		else
		{
			m_tail = nullptr; // ����Ʈ�� ����ְ� �Ǹ� tail�� nullptr�� �����մϴ�.
		}
		m_size--;
		return temp;
	}

	Node* pop_back()
	{
		if (m_tail == nullptr)
		{
			return nullptr; // ����Ʈ�� ��������� �ƹ��͵� ���� �ʽ��ϴ�.
		}
		Node* temp = m_tail;
		m_tail = m_tail->prev;
		if (m_tail != nullptr)
		{
			m_tail->next = nullptr;
		}
		else
		{
			m_head = nullptr; // ����Ʈ�� ����ְ� �Ǹ� head�� nullptr�� �����մϴ�.
		}
		m_size--;
		return temp;
	}

	bool empty() const
	{
		return m_size == 0;
	}
};
