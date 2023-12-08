#include<iostream>
using namespace std;

struct Node
{
	int data;
	Node* next = nullptr;
	Node(int data) :data(data) {}
};

class LinkedList
{
private:
	Node* head{};
	Node* tail{};
	int length = 0;

public:
	int get_length()const
	{
		return length;
	}
	Node* get_previous_node(Node* node) //O(N)time O(1)memroy
	{
		if (node == head)
			return nullptr;

		for (Node* pre = head; pre != tail; pre = pre->next)
		{
			if (pre->next == node)
				return pre;
		}

		return nullptr;
	}
	void print() //O(N)time O(1)memroy
	{
		for (Node* node = head; node; node = node->next)
		{
			cout << node->data << " -> ";
		}
		cout << "null\n";
	}

	void delete_front() //O(1)time O(1)memroy
	{
		if (length == 0)
			return;
		else if (length == 1)
		{
			delete head;
			head = tail = nullptr;
		}
		else if (length == 2)
		{
			delete head;
			head = tail;
		}
		else
		{
			Node* node = head->next;
			delete head;
			head = node;
		}
		length--;
	}
	void delete_end() //O(N)time O(1)memroy
	{
		if (length == 0)
			return;
		else if (length == 1)
		{
			delete head;
			head = tail = nullptr;
		}
		else if (length == 2)
		{
			delete tail;
			tail = head;
		}
		else
		{
			Node* node = head;
			for (int i = 0; i < length - 2; i++)
				node = node->next;

			delete tail;
			tail = node;
			tail->next = nullptr;
		}
		length--;
	}
	void delete_node_with_key(int value)//O(N)time O(1)memory
	{
		if (length == 0)
			return;

		Node* previous = nullptr;
		for (Node* node = head; node; node = node->next)
		{
			if (node->data == value)
			{
				if (head == node)
					delete_front();
				else if (tail == node)
					delete_end();
				else
				{
					previous->next = node->next;
					delete node;
					length--;
				}
				return;
			}
			previous = node;
		}
		return;
	}
	void delete_all_nodes_with_key(int value)//O(N)time O(1)memory
	{
		if (length < 1)
			return;

		Node* pre = head;
		Node* node = nullptr;

		for (node = head; node;)
		{
			if (node->data == value)
			{
				if (node == head)
				{
					node = node->next;
					pre = node;
					delete_front();
				}
				else if (node == tail)
				{
					tail = pre;
					pre->next = nullptr;
					delete node;
					node = nullptr;
					length--;
				}
				else
				{
					pre->next = node->next;
					Node* deleter = node;
					node = node->next;
					delete deleter;
					length--;
				}
			}
			else
			{
				if (node != pre)
					pre = node;
				node = node->next;
			}
		}

	}

	void delete_even_positions() //O(N)time O(1)memroy
	{
		if (head == nullptr)
			return;

		Node* node = head;
		Node* Next = head->next;
		Node* deleter = nullptr;

		while (Next)
		{
			deleter = Next;

			if (Next->next)
			{
				node->next = Next->next;
				node = Next->next;
				Next = node->next;
			}
			else
			{
				node->next = nullptr;
				Next = nullptr;
			}

			delete deleter;
			length--;
		}
	}
	void remove_duplicates() //O(N)time O(1)memory
	{
		if (length <= 1)
			return;

		for (Node* node = head; node; node = node->next)
		{
			Node* Next = node->next;
			Node* pre = node;

			while (Next)
			{
				if (Next->data == node->data)
				{
					pre->next = pre->next->next;
					delete Next;
					Next = pre->next;
					length--;
				}
				else
				{
					pre = Next;
					Next = Next->next;
				}
			}
		}
	}
	bool remove_last_occurence(int val) //O(N)time O(1)memory
	{
		Node* selector = nullptr;

		for (Node* node = head; node; node = node->next)
		{
			if (node->data == val)
				selector = node;
		}

		if (selector == nullptr)
			return false;

		else if (selector == head)
		{
			delete_front();
			return true;
		}

		else if (selector == tail)
		{
			delete_end();
			return true;
		}

		else
		{
			for (Node* node = head; node; node = node->next)
			{
				if (node->next == selector)
				{
					node->next = selector->next;
					delete selector;
					length--;
					return true;
				}
			}
		}
	}
	void remove_all_repeated()
	{
		if (length < 2)
			return;

		Node* pre = head;

		for (Node* node = head->next; node;)
		{
			if (pre->data == node->data)
			{
				int val = node->data;

				if (pre == head)
				{
					delete_all_nodes_with_key(val);
					if (head)
					{
						pre = head;
						node = head->next;
					}
					else
						return;
				}
				else
				{
					pre = get_previous_node(pre);
					node = pre->next;
					delete_all_nodes_with_key(val);
				}
			}
			else
			{
				if (node != pre)
					pre = node;
				node = node->next;
			}
		}
	}

	void insert_front(int value) //O(1)time O(1)memroy
	{
		Node* node = new Node(value);
		if (length == 0)
			head = tail = node;
		else
		{
			node->next = head;
			head = node;
		}
		length++;
	}
	void insert_end(int value) //O(1)time O(1)memory
	{
		Node* node = new Node(value);
		if (length == 0)
			head = tail = node;
		else
		{
			tail->next = node;
			tail = node;
		}
		length++;
	}
	void insert_sorted(int value) //O(N)time O(1)memroy
	{
		if (length == 0)
			insert_front(value);
		else if (length == 1)
			if (head->data >= value)
				insert_front(value);
			else
				insert_end(value);
		else
		{
			if (head->data >= value)
				insert_front(value);
			else
			{
				for (Node* node = head; node; node = node->next)
				{
					Node* Next = node->next;
					if (Next)
					{
						if (Next->data >= value)
						{
							Node* New = new Node(value);
							New->next = Next;
							node->next = New;
							length++;
							return;
						}
					}
					else
					{
						insert_end(value);
						return;
					}
				}
			}

		}
	}
	void insert_after_node(Node* node1, int val) //O(1)time O(1)memroy Dangerous if used improperly 
	{
		if (node1 == nullptr)
			insert_front(val);
		else if (node1 == tail)
			insert_end(val);
		else
		{
			Node* node2 = new Node(val);
			node2->next = node1->next;
			node1->next = node2;
			length++;
		}
	}
	void insert_alternating(LinkedList& ls) //O(N)time O(1)memroy
	{
		Node* node1 = head;
		Node* node2 = ls.head;

		for (; node2; node2 = node2->next)
		{
			insert_after_node(node1, node2->data);
			if (node1 == nullptr)
				node1 = tail;
			else if (node1->next->next == nullptr)
				node1 = node1->next;
			else
				node1 = node1->next->next;
		}
	}

	void swap_pair() //O(N)time O(1)memroy
	{
		for (Node* node = head; node; node = node->next)
		{
			if (node->next)
			{
				swap(node->data, node->next->data);
				node = node->next;
			}
		}
	}
	void swap_head_tail()   //O(1)memory  O(n)time
	{
		if (length == 0 || length == 1)
			return;
		else if (length == 2)
			reverse();
		else
		{
			tail->next = head->next;
			Node* node = head;

			for (int i = 0; i < length - 2; i++)
				node = node->next;

			node->next = head;
			head->next = nullptr;

			node = head;
			head = tail;
			tail = head;
		}

	}
	void reverse() //O(N)time O(1)memroy
	{
		if (length == 0 || length == 1)
			return;
		else if (length == 2)
		{
			tail = head;
			head = head->next;
			head->next = tail;
			tail->next = nullptr;
		}
		else
		{
			Node* previous = head;
			Node* node = head->next;
			Node* Next = node->next;
			tail = head;
			tail->next = nullptr;

			while (Next)
			{
				node->next = previous;
				previous = node;
				node = Next;
				Next = Next->next;
			}
			head = node;
			head->next = previous;
		}
	}
	void left_rotate(int moves) //O(N)time O(1)memroy
	{
		moves %= length;

		if (length <= 1)
			return;

		while (moves)
		{
			tail->next = head;
			head = head->next;
			tail = tail->next;
			tail->next = nullptr;
			moves--;
		}
	}
	void move_to_back(int val) //O(N*M)time O(1)memory
	{
		int counter = 0;

		while (remove_last_occurence(val))
		{
			counter++;
		}

		while (counter)
		{
			insert_end(val);
			counter--;
		}
	}
	void arrange_odd_even()//O(N*M)time O(1)memory
	{
		if (length <= 2)
			return;

		int len = length / 2;
		for (Node* node = head; len; len--)
		{
			insert_end(node->next->data);
			delete_node_with_key(node->next->data);
			node = node->next;
		}
	}
	Node* reverse_sub_linked_list(Node* start, Node* end) //O(1)memory O(
	{
		Node* pre = start;
		Node* node = start->next;
		Node* Next = node->next;

		while (Next != end->next)
		{
			node->next = pre;
			pre = node;
			node = Next;
			Next = Next->next;
		}
		start->next = nullptr;
		end->next = pre;
		return start;
	}
	void reverse_chains(int k)
	{
		if (length <= 1)
			return;
		if (k <= 0)
			return;

		k %= length;

		if (k == 0 || k == 1)
			reverse();
		else if (k == 2)
			swap_pair();
		else
		{
			Node* start = head;
			Node* end = head;
			Node* current_start = nullptr;
			Node* current_end = nullptr;
			bool first_run = true;

			while (current_start || first_run)
			{
				for (int i = 0; i < k - 1; i++)
				{
					end = end->next;
					if (!first_run)
						current_end->next = end;

					if (!end)
					{
						if (!first_run)
							current_end->next = current_start;
						return;
					}

				}

				current_start = end->next;
				current_end = reverse_sub_linked_list(start, end);

				if (first_run)
				{
					head = end;
					first_run = false;
				}

				start = current_start;
				end = current_start;
			}
			tail = current_end;
		}
	}

	int max() //O(N)time O(N^2)memory
	{
		LinkedList ls = *this;
		Node* node = ls.head;
		ls.head = head->next;
		delete node;

		if (ls.head == ls.tail)
			return ls.tail->data;
		else
			return std::max(head->data, ls.max());
	}
	void add_num(LinkedList& ls) //O(N)time O(1)memory
	{
		Node* node1 = head;
		Node* node2 = ls.head;

		for (; node2; node2 = node2->next)
		{
			if (node1 == nullptr)
				insert_end(node2->data);
			else
			{
				int result = node1->data + node2->data;
				node1->data = result % 10;

				if (result / 10)
				{
					if (node1->next != nullptr)
						node1->next->data += result / 10;
					else
						insert_end(result / 10);
				}
				node1 = node1->next;
			}
		}
	}
};

void test()
{
	LinkedList ls;
	ls.insert_end(1);
	ls.insert_end(2);
	ls.insert_end(3);
	ls.insert_end(4);
	ls.insert_end(5);
	ls.insert_end(6);


	ls.print();
	cout << "Length=: " << ls.get_length() << "\n";

	/*ls.remove_all_repeated();*/

	ls.reverse_chains(6);
	ls.print();
	cout << "Length=: " << ls.get_length() << "\n";

	/*ls.insert_end(4);
	ls.insert_end(5);
	ls.insert_end(6);*/

	/*ls.print();*/

	/*ls.delete_node_with_key(1);
	ls.print();

	ls.insert_front(1);
	ls.print();

	ls.delete_node_with_key(4);
	ls.print();

	ls.insert_end(4);
	ls.print();

	ls.delete_node_with_key(2);
	ls.print();*/

	/*ls.swap_pair();*/
	/*ls.reverse();
	ls.print();*/
	/*ls.delete_even_positions();
	ls.print();*/
	/*ls.insert_sorted(3);
	ls.insert_sorted(1);
	ls.insert_sorted(2);*/
	/*ls.insert_sorted(6);
	ls.insert_sorted(5);
	ls.insert_sorted(4);*/
	/*ls.print();
	cout <<"Length=: "<< ls.get_length() << "\n";*/

	/*ls.swap_head_tail();
	ls.print();*/
	/*ls.left_rotate(1);
	ls.print();
	ls.left_rotate(2);
	ls.print();
	ls.left_rotate(3);
	ls.print();
	ls.left_rotate(4);
	ls.print();
	ls.left_rotate(5);
	ls.print();
	ls.left_rotate(6);
	ls.print();
	ls.left_rotate(7);
	ls.print();
	ls.left_rotate(8);
	ls.print();*/


	//ls.insert_end(12);
	//ls.insert_end(22);
	//ls.insert_end(20);
	//ls.insert_end(16);
	//ls.insert_end(15);
	//ls.insert_end(17);
	//ls.insert_end(21);
	//ls.insert_end(10);
	//
	//ls.print();
	//cout << "Length=: " << ls.get_length() << "\n";

	//ls.remove_duplicates();
	//ls.print();
	//cout << "Length=: " << ls.get_length() << "\n";

	//ls.remove_last_occurence(-1);
	//ls.print();
	//cout << "Length=: " << ls.get_length() << "\n";

	//ls.move_to_back(1);
	//ls.print();
	//cout << "Length=: " << ls.get_length() << "\n";

	//cout<<"max value in list is: "<<ls.max();

	/*ls.insert_end(1);
	ls.insert_end(2);
	ls.insert_end(3);
	ls.insert_end(4);
	ls.insert_end(5);
	ls.insert_end(6);
	ls.insert_end(7);
	ls.insert_end(8);


	ls.arrange_odd_even();
	ls.print();*/

	//LinkedList ls1, ls2;
	//ls1.insert_end(-9);
	//ls1.insert_end(-9);
	//ls1.insert_end(-9);
	//
	//ls2.insert_end(9);
	//ls2.insert_end(9);
	//ls2.insert_end(9);
	//

	//ls1.insert_alternating(ls2);
	//cout << "Length=: " << ls1.get_length() << "\n";
	//ls1.print();*/

	//ls1.add_num(ls2);
	//cout << "Length=: " << ls1.get_length() << "\n";
	//ls1.print();
}

int main(void)
{

	test();

	return 0;
}