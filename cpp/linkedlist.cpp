#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next = NULL;
};

void printLinkedList(node* head) {
    node* t = head;
    while(t) {
        cout<<t->data<<" ";
        t=t->next;
    }
    cout<<endl;
}

void printLinkedListRec(node* head) {
    if (head==NULL) {
        cout<<endl;
        return;
    }
    cout<<head->data<<" ";
    printLinkedListRec(head->next);
}

int maxNode(node *head, int maxVal)
{
    if (head == NULL)
        return maxVal;
    int data = head->data;
    if (data > maxVal)
        maxVal = data;
    return maxNode(head->next, maxVal);
}

node* deleteNth(node* head, int n) {
    if (n==0) {
        node* new_head = head -> next;
        head->next=NULL;
        return new_head;
    }
    int r = 0;
    node* temp = head;
    node* prev = head;
    while(r!=n) {
        prev = temp;
        temp=temp->next;
        r+=1;
        if (temp == NULL) return head;
    }

    prev -> next = temp ->next;
    temp -> next = NULL;
    return head;
}

node* deleteNthRec(node* head, int n) {
    if (head == NULL)  return head;
    if (n==0) {
        node* res = head -> next;
        delete(head);
        return res;
    }
    head -> next = deleteNthRec(head->next, n-1);
}

int main() {

    node *a = new node;
    node *b = new node;
    node *c = new node;
    node *head = new node;

    head->data = 3;
    head->next = a;
    a->data = 12;
    a->next = b;
    b->data = 8;
    b->next = c;
    c->data = 6;
    printLinkedList(head);
    node* new_head = deleteNthRec(head, 3);
    printLinkedList(new_head);

    return 0;
}