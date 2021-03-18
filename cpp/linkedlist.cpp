#include <iostream>
#include <cmath>
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

node* convertListToLinkedList(int *arr, int size) {
    node* head = new node;
    head -> data = arr[0];
    node* r = head;
    for (int i = 1; i < size; i++) {
        node* t = new node;
        t->data = arr[i];
        r->next = t;
        r=t;
    }
    return head;
}

node* convertListToLinkedListRec(int *arr, int size, int r) {
    node* t = new node;
    if (r==size-1) {
        t->data=arr[r];
        t->next=NULL;
        return t;
    }
    t->data=arr[r];
    t->next = convertListToLinkedListRec(arr, size, r+1);
    return t;

}

void sortLinkedList(node* head, int size) {
    node* t1= head;
    while(t1->next) {
        int min = t1->data;
        node* minNode = NULL;
        for(node* t2=t1; t2; t2=t2->next) {
            if (t2->data<min) {
                min = t2->data;
                minNode = t2;
            }
        }
        if (minNode) {
            minNode -> data = t1->data;
        }
        t1->data = min;
        t1=t1->next;
    }
}

node* addedPoly(node* p1, node* p2) {
    node* res = new node;
    res->data = p1->data+p2->data;
    p1=p1->next;
    p2=p2->next;
    node* run = res;
    while(p1) {
        int data = p1->data + p2->data;
        node* t = new node;
        t->data = data;
        run->next=t;
        run=t;
        p1=p1->next;
        p2=p2->next;
        
    }
    return res;
}

node* createRandomList(int n) {
    if (n>0) {
        node* head = new node;
        head->data= rand() % 20;
        node* run = head;
        while(n>1) {
            node* t = new node;
            t->data = rand() % 20;
            run->next=t;
            run=t;
            n--;
        }
        return head;
    }
}

void insertTail(node*& head, int newData) {
    node* tail = new node;
    tail->data = newData;
    tail->next = NULL;
    if (head==NULL) {
        head=tail;
        return;
    }
    node* run = head;
    while(run->next) {
        run=run->next;
    }
    run->next=tail;
    return;
}

void insertTailRec(node*& head, int newData) {
    if (head==NULL) {
        node* tail = new node;
        tail->data= newData;
        tail->next = NULL;
        head = tail;
        return;
    }
    if (head->next==NULL) {
        node* tail = new node;
        tail->data= newData;
        tail->next = NULL;
        head->next=tail;
        return;
    }
    insertTailRec(head->next, newData);
}

void insertHead(node*& head, int newData) {
    node* t = new node;
    t->data=newData;
    if(head==NULL) {
        head=t;
        head->next=NULL;
        return;
    }
    t->next=head;
    head=t;
    return;
}

void deleteNodeData(node*& head, int delData) {
    node* run = head;
    node* prev = head;
    while(run) {
        if (head->data==delData) {
            head=run->next;
            delete run;
            return;
            
        }
        if(run->data == delData) {
            prev->next=run->next;
            delete run;
            return;
        }
        prev=run;
        run=run->next;
    }
}

void deleteNodeRec(node*& head, int delData) {
    if (head==NULL) return;
    if (head->data==delData) {
        node* t = head;
        head = t->next;
        delete t;
        return;
    }
    deleteNodeRec(head->next, delData);
}

int sumLinkedList(node* head) {
    if (head==NULL) return 0;
    return head->data+sumLinkedList(head->next);
}

float polyEvalRec(node* head, float x, int size) {
    if (head->next==NULL) {
        return head->data;
    }
    return polyEvalRec(head->next, x, size-1) + pow(x, size-1)*(head->data);
}

float polyEva(node* head, float x) {
    float res = 0;
    while(head) {
        float coeff=1;
        for(node* r=head;r->next;r=r->next) {
            coeff*=x;
        }
        res+=coeff*head->data;
        head=head->next;
    }
    return res;
}

float polyEvaPow(node* head, float x) {
    float res=0;
    node* r = head;
    int coeff = 0;
    while(r) {
        coeff+=1;
        r=r->next;
    }
    while(head) {
        res+= (head->data)*pow(x, coeff-1);
        head=head->next;
        coeff-=1;
    }
}

node* reverseLinkedList(node* root, int& n) {
    if (root->next==NULL) {
        return root;
    }
    root->next=reverseLinkedList(root->next, n);
    return root;
}

int main() {
    // int arr[] = {5,4,3,8,1};
    // // node* head = convertListToLinkedList(arr, 5);
    // node* head = convertListToLinkedListRec(arr, 5, 0);
    // printLinkedList(head);
    // sortLinkedList(head, 5);
    // printLinkedList(head);

    // int poly1[5] = {5, 8, 3, 2, 9};
    // int poly2[5] = {2, 0, 0, 1, 5};
    // node* p1 = convertListToLinkedList(poly1, 5);
    // node* p2 = convertListToLinkedList(poly2, 5);


    // insertTailRec(random, 100);
    // insertHead(random, 100);
    // printLinkedList(p1);
    // deleteNodeRec(p1, 5);
    // printLinkedList(p1);
    // cout<<sumLinkedList(p1)<<endl;

    int arr[] = {2,3,4};
    node* head = convertListToLinkedList(arr,3);
    printLinkedList(head);
    node* nHead = reverseLinkedList(head);
    printLinkedList(nHead);


    return 0;
}