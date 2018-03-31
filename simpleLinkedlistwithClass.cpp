#include <iostream>
using namespace std;

struct node {
	int data;
	node* next;
};
class linkedlist {
private:
	node* head;
	node* tail;
public:
	linkedlist() {
		head = NULL;
		tail = NULL;
	}
	void appendNode(int data) {
		node* temp = new node;
		temp->data = data;
		temp->next = NULL;
		if (head == NULL) {
			head = tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}
	void insert(int data) {
		node* temp = new node;
		temp->data = data;
		temp->next = NULL;
		if (head == NULL) {
			head = tail = NULL;
		}
		else {
			temp->next = head;
			head = temp;
		}

	}
	void print() {
		for (node* r = head; r; r = r->next)
		{
			cout << r->data << " ";
		}
		cout << endl;
	}
};
int main() {
	linkedlist a;
	a.appendNode(1);
	a.appendNode(2);
	a.appendNode(3);
	a.insert(100);
	a.print();

	system("pause");
	return 0;

}