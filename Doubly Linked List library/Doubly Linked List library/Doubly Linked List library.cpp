#include<iostream>

struct Node
{
	int data{};
	Node* next = nullptr;
	Node* prev = nullptr;

	Node(int data) :data(data) {}
};

class DoublyLinkedList
{
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int length = 0;

public:
	void print() //O(N)time O(1)memory
	{
		std::cout << "null <- ";
		for (Node* node = head; node; node = node->next)
		{
			std::cout << node->data;
			if (node->next)
				std::cout << " <-> ";
		}
		std::cout << " -> null\nLength: " << length << "\n";
	}

	void add_node_back(int data) //O(1)time O(1)memory
	{
		Node* node = new Node(data);

		if (length == 0)
			head = tail = node;

		else if (length == 1)
		{
			head->next = node;
			node->prev = head;
			tail = node;
		}

		else
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
		}

		length++;
	}
	void add_node_front(int data) //O(1)time O(1)memory
	{
		Node* node = new Node(data);

		if (length == 0)
			head = tail = node;

		else if (length == 1)
		{
			tail->prev = node;
			node->next = tail;
			head = node;
		}

		else
		{
			head->prev = node;
			node->next = head;
			head = node;
		}

		length++;
	}

	void delete_front() //O(1)time O(1)memory
	{
		if (length <= 0)
			return;

		if (length == 1)
		{
			delete head;
			head = tail = nullptr;
			length = 0;
			return;
		}

		Node* node = head;
		head = head->next;
		delete node;
		head->prev = nullptr;
		length--;
	}
	void delete_all_nodes_with_key(int value) //O(N)time O(1)memory
	{
		for (Node* node = head; node; node = node->next)
		{
			if (node->data == value)
			{
				if (length == 1)
				{
					head = tail = nullptr;
					delete node;
					length = 0;
					return;
				}
				else if (node == head)
				{
					head = head->next;
					head->prev = nullptr;
					delete node;
					node = head;
				}
				else if (node == tail)
				{
					node = node->prev;
					delete tail;
					tail = node;
					tail->next = nullptr;
				}
				else
				{
					Node* temp = node;
					node = node->prev;
					node->next = temp->next;
					delete temp;
				}
				length--;
			}
		}
	}
	void delete_even_positions() //O(N)time O(1)memory
	{
		Node* node = head;
		Node* adv = nullptr;

		for (; node && node->next; node = node->next)
		{
			Node* temp = node->next;
			adv = temp->next;

			node->next = adv;
			if (adv)
				adv->prev = node;

			delete temp;
			length--;
		}

		tail = node;
		if (adv)
			tail = adv;
	}
	void delete_odd_positions() //O(N)time O(1)memory
	{
		add_node_front(-1);
		delete_even_positions();
		delete_front();
	}

	int find_in_middle()
	{
		Node* start = head;
		Node* end = tail;

		while (start)
		{
			if (start->next == end || start == end)
				return end->data;
			else
			{
				start = start->next;
				end = end->prev;
			}
		}
	}
	int find_in_middle_sll()
	{
		Node* fast = head;
		Node* slow = head;

		while (fast&&fast->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		if (slow)
			return slow->data;
		else
			return 0;
	}

	bool is_palindrome() //O(N)time O(1)memory
	{
		Node* start = head;
		Node* end = tail;
		int len = length / 2;

		while(len--)
		{
			if (start->data != end->data)
				return false;
			start = start->next;
			end = end->prev;
		}
		return true;
	}

	void swap(Node* start,Node* end)
	{
		Node* start_pre = start->prev;
		Node* end_next = end->next;

		if (start->next == end)
		{
			start->next = end_next;
			start->prev = end;
			start_pre->next = end;

			end->next = start;
			end->prev = start_pre;
			end_next->prev = start;
			return;
		}

		Node* start_next = start->next;
		Node* end_pre = end->prev;
		
		start->next = end_next;
		start->prev = end_pre;

		end->next = start_next;
		end->prev = start_pre;
		

		if (start != head)
			start_pre->next = end;
		else
			head = end;
		
		start_next->prev = end;

		if (end != tail)
			end_next->prev = start;
		else
			tail = start;

		end_pre->next = start;
	}
	void swap_forward_with_backward(int k)
	{
		if (k <= 0)
			return;

		if (k * 2 > length)
			return;

		Node* start = head;
		Node* end = tail;
		k--;

		while (k)
		{
			start = start->next;
			end = end->prev;
			k--;	
		}

		swap(start, end);
	}
	void reverse() //O(N)time O(1)memory
	{
		if (length <= 1)
			return;

		
		Node* node = head;
		head = tail;
		tail = node;
		node = head;

		while (node)
		{
			Node* prev = node->next;
			node->next = node->prev;
			node->prev = prev;
			node = node->next;
		}
		
	}

	void insert_after(Node*& node1, Node*& node2) //O(1)time O(1)memory
	{
		Node* temp = node2->next;
		Node* Next = node1->next;

		node2->prev = node1;
		node2->next = node1->next;
		node1->next = node2;

		if (Next)
			Next->prev = node2;
		else
			tail = node2;

		node1 = node2;
		node2 = temp;
	}
	void insert_before(Node* node1, Node*& node2) //O(1)time O(1)memory
	{
		Node* temp = node2->next;
		Node* prev = node1->prev;

		node2->next = node1;
		node2->prev = node1->prev;
		node1->prev = node2;

		if (prev)
			prev->next = node2;
		else
			head = node2;

		node2 = temp;
	}
	void merge_2sorted_lists(DoublyLinkedList& other) //O(n+m)time O(1)memory
	{
		Node* node1 = head;
		Node* node2 = other.head;

		if (!node1)
		{
			head = other.head;
			tail = other.tail;
			length += other.length;
			other.length = 0;
			other.head = nullptr;
			other.tail = nullptr;
			return;
		}

		while (node1 && node2)
		{
			if (node2->data >= node1->data)
				node1 = node1->next;
			else
				insert_before(node1, node2);
		}

		if (node2)
		{
			tail->next = node2;
			node2->prev = tail;
			tail = other.tail;
		}

		
		length += other.length;
		other.length = 0;
		other.head = nullptr;
		other.tail = nullptr;
	}
};

void test()
{
	DoublyLinkedList dll;

	dll.add_node_back(10);
	dll.add_node_back(20);
	dll.add_node_back(30);
	dll.add_node_back(40);
	dll.add_node_back(50);
	dll.print();

	DoublyLinkedList other;
	other.add_node_back(15);
	other.add_node_back(17);
	other.add_node_back(22);
	other.add_node_back(24);
	other.add_node_back(35);
	other.print();

	/*dll.delete_all_nodes_with_key(0);
	dll.print();*/

	/*dll.delete_even_positions();
	dll.print();*/

	/*dll.delete_odd_positions();
	dll.print();*/
	
	/*std::cout<< std::boolalpha<<dll.is_palindrome();*/
	
	/*int data=dll.find_in_middle_sll();
	std::cout << "middle value is: " << data << "\n";*/

	/*dll.swap_forward_with_backward(4);
	dll.print();*/

	/*dll.reverse();
	dll.print();*/

	dll.merge_2sorted_lists(other);
	dll.print();
	other.print();

}

int main(void)
{
	test();
	return 0;
}