#include <iostream>

using namespace std;

 struct node1 {
	int data;
	node1* next;
};
 typedef node1 node;
 struct list1 {
	node* phead;
	node* ptail;
 };
 typedef list1 list;

//khoi tao danh sach
void init(list &l) {
	l.phead = l.ptail = NULL;
}

//nhap 1 node p
node* getNode(int data) {
	node* p = new node;
	if (p == NULL) {
		return NULL;
	}
	p->data = data;
	p->next = NULL;
}

//them 1 node vao dau
void addHead(list &l, node* p) {
	if (l.phead = NULL) {
		l.phead = l.ptail = p;
	}
	else {
		p->next = l.phead;
		l.phead = p;
	}

}

//them 1 node vao cuoi
void addTail(list &l, node* p) {
	if (l.phead == NULL) {
		l.phead = l.ptail = p;
	}
	else {
		l.ptail->next = p;
		l.ptail = p;
	}
}

//Nhap du lieu cho danh sach
void pushNode(list &l) {
	int n;
	cout << "How many nodes: ";
	cin >> n;
	init(l); //khoi tao danh sach
	for (int i = 1; i <= n; i++) {
		int data;
		cout << "Nhap vao data: ";
		cin >> data;
		node* p = getNode(data);
		addTail(l, p);
	}
}

//display list
void displayList(list l) {
	for (node* pRun = l.phead; pRun; pRun = pRun->next) {
		cout << pRun->data << " ";
	}
}

void findMax(list l) {
	int max = l.phead->data;
	for(node* pRun=l.phead->next;pRun;pRun=pRun->next){
		if (pRun->data > max) max = pRun->data;
	}
	cout << max << endl;
}
void swap(int a, int b) {
	int t = a;
	a = b;
	b = t;
}
void sorting(list &l) {
	for (node* p = l.phead; p != l.ptail; p = p->next) {
		for (node* q = p->next; q; q = q->next) {
			if (p->data > q->data) {
				swap(p->data, q->data);
			}
		}
	}
}

//them node p vao sau node q

void addNode(list &l, node* p, node* q) {
	for (node* k = l.phead; k; k = k->next) {
		if (k->data == q->data) {
			node* g = k->next;
			k->next = p;
			p->next = g;
		}
	}
}

//xoa node dau

void deleteHead(list &l) {
	node* p = l.phead;
	l.phead = l.phead->next;
	delete p;
}

void deleteTail(list &l) {
	node* p = NULL;
	for (node* run = l.phead; run; run = run->next) {
		if (run == l.ptail) {
			l.ptail = p;
			l.ptail->next = NULL;
			delete run;
			return;
		}
		p = run;
	}
}

//xoa node g nam sau node q

void deleteAfterNode(list &l, node* q) {
	node* g = NULL;
	for(node* run=l.phead;run;run=run->next){
		if (run->data == q->data) {
			g = run->next;
			run->next = g->next;
			delete g;
			return;
	}
		
	}
}

void deletAnode(list &l, int data) {
	if (l.phead->data == data) {
		deleteHead(l);
		return;
	}
	else if (l.ptail->data == data) {
		deleteTail(l);
		return;
	}
	else {
		node* g;
		for (node* run = l.phead->next; run!=l.ptail; run = run->next) {
			if (run->data == data) {
				deleteAfterNode(l, g);
			}
			g = run;
		}
	}
}

int main() {
	list l;
	pushNode(l);
	displayList(l);
	cout << endl;
	deleteTail(l);
	displayList(l);
	int q;
	cout << "\nData q: ";
	cin >> q;
	node* Q = getNode(q);

	deleteAfterNode(l,Q);
	displayList(l);
	cout << "\n";
	system("pause");
	return 0;

}