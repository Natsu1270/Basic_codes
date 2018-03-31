#include <iostream>
using namespace std;

typedef struct node {
	int data;
	node* next;
}Node;

Node* createNode(int n) {
	node *newNode = new Node();
	newNode->data = n;
	newNode->next = NULL;
	return newNode;
}
Node* appendNode(Node* pHead, int n) {
	Node* cur = pHead;
	while (cur) {
		if (cur->next == NULL) {
			cur->next = createNode(n);
			return cur->next;
		}
		cur = cur->next;
	}
	return cur;
}
void printNodes(Node* pHead) {
	Node* cur = pHead;
	while (cur) {
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}

Node *deleteNode(Node **phead) {
	Node* temp = *phead;
	*phead = temp->next;
	delete temp;
	return *phead;
}
Node *insertFront(Node** phead,int data) {
	Node* newNode = createNode(data);
	newNode->next = *phead;
	*phead = newNode;
	return *phead;
}

Node* x(Node *head, int data) {
	Node* newNode = createNode(data);
	newNode->next = head;
	head = newNode;
	return head;
}

int main() {
	Node* head = createNode(100);
	appendNode(head, 20);
	appendNode(head, 25);
	appendNode(head, 33);
	printNodes(head);
	head = insertFront(&head, 111);
	head = deleteNode(&head);
	printNodes(head);
	head = x(head, 333);
	printNodes(head);
	system("pause");
	return 0;

}