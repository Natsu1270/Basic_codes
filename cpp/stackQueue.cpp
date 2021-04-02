#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
};

struct list
{
    node *pHead;
    node *next;
};

class stack1
{
private:
    node *top;
    int count;

public:
    stack1()
    {
        top = NULL;
        count = 0;
    }
    void pushStack(int n)
    {
        node *newNode = new node;
        newNode->data = n;
        newNode->next = top;
        top = newNode;
        count++;
    }
    int popStack()
    {
        int data = top->data;
        node *t = top;
        top = t->next;
        delete t;
        count--;
        return data;
    }
    int peekStack()
    {
        return top->data;
    }
    bool isStackEmpty()
    {
        return count == 0;
    }
    void printStack()
    {
        node *run = top;
        cout << "-STACK-"
             << " " << count << " elements" << endl;
        while (count > 0)
        {
            int data = run->data;
            cout << "| " << data << " |" << endl;
            count--;
            run = run->next;
        }
        cout << "|___|" << endl;
        return;
    }
    stack1 *copyStack()
    {
        stack1 *newStack = new stack1();
        newStack->top = this->top;
        newStack->count = this->count;
        return newStack;
    }
};

// ============ STACK ================

struct stack
{
    node *top;
    int count;
};

void pushStack(stack *&s, int n)
{
    node *newNode = new node;
    newNode->data = n;
    if (s->top == NULL)
    {
        newNode->next = NULL;
    }
    else
    {
        newNode->next = s->top;
    }
    s->top = newNode;
    s->count++;
}

void popStack(stack *&s, int &x)
{
    node *t = s->top;
    x = t->data;
    s->top = t->next;
    delete t;
    s->count--;
}

bool isEmptyStack(stack *s)
{
    return s->count == 0;
}

stack *copyStack(stack *source)
{
    stack *temp = new stack;
    stack *res = new stack;
    int x = -1;
    while (!isEmptyStack(source))
    {
        popStack(source, x);
        pushStack(temp, x);
    }
    while (!isEmptyStack(temp))
    {
        popStack(temp, x);
        pushStack(source, x);
        pushStack(res, x);
    }
    return res;
}

void removeNthNode(stack *&s, int n)
{
    if (n < 0 || n > s->count)
    {
        return;
    }
    int pos = s->count - n;
    stack *temp = new stack;
    int x = -1;
    while (pos > 0)
    {
        popStack(s, x);
        pushStack(temp, x);
        pos--;
    }
    popStack(s, x);
    while (!isEmptyStack(temp))
    {
        popStack(temp, x);
        pushStack(s, x);
    }
}

void printStack(stack *s)
{
    node *r = s->top;
    while (r)
    {
        cout << "| " << r->data << " |" << endl;
        r = r->next;
    }
    cout << "|___|" << endl;
}

int topStack(stack *s)
{
    return s->top->data;
}

// ============== QUEUE ================
struct queue
{
    node *front;
    node *rear;
    int count;
};

void enqueue(queue *q, int n)
{
    node *newNode = new node;
    newNode->data = n;
    if (q->count == 0)
    {
        q->front = newNode;
        q->rear = newNode;
        return;
    }
    newNode->next = q->front;
    q->front = newNode;
    q->count++;
}

void dequeue(queue *q, int &x)
{
    node *r = q->front;
    node *rear = q->rear;
    x = rear->data;
    while (r->next->next)
    {
        r = r->next;
    }
    q->rear = r;
    delete rear;
}

void printQueue(queue *q)
{
}

void inverstStack(stack *&s)
{
    stack *temp = new stack;
    int x = -1;
    int y = -1;
    int size = s->count;
    for (int i = 0; i < size; i++)
    {
        popStack(s, x);
        for (int j = i + 1; j < size; j++)
        {
            popStack(s, y);
            pushStack(temp, y);
        }
        pushStack(s, x);
        while (!isEmptyStack(temp))
        {
            popStack(temp, y);
            pushStack(s, y);
        }
    }
}

void decimalToBin(int n)
{
    int x = -1;
    int y = -1;
    stack *res = new stack;
    while (x != 0)
    {
        y = n % 2;
        x = n / 2;
        n = x;
        pushStack(res, y);
    }
    printStack(res);
}

struct point
{
    int x;
    int y;
};

struct Node
{
    point *data;
    Node *next;
};
struct Stack
{
    Node *top;
    int count = 0;
};

void PushStack(Stack *&s, point *&n)
{
    Node *newNode = new Node;
    newNode->data = n;
    if (s->top == NULL)
    {
        newNode->next = NULL;
    }
    else
    {
        newNode->next = s->top;
    }
    s->top = newNode;
    s->count++;
}

void PopStack(Stack *&s, point *&x)
{
    Node *t = s->top;
    x = t->data;
    s->top = t->next;
    delete t;
    s->count--;
}

bool isEmptyStack(Stack *s)
{
    return s->count == 0;
}
bool isGoal(point *p)
{
    return p->x == 2 && p->y == 2;
}

void printPathMatrix(int arr[][3])
{
    Stack *trace = new Stack;
    point *p = new point;
    p->x = 0;
    p->y = 0;
    point *start = new point;
    start->x = 0;
    start->y = 0;
    bool isGoal = false;
    bool isFail = false;
    PushStack(trace, start);
    while (!isGoal && !isFail)
    {
        if (p->x == 2 && p->y == 2)
        {
            isGoal = true;
        }
        else if (p->x < 2 && arr[p->x + 1][p->y] != -1)
        {
            point *newPoint = new point;
            newPoint->x = p->x + 1;
            newPoint->y = p->y;
            p->x = p->x + 1;
            PushStack(trace, newPoint);
        }
        else if (p->y < 2 && arr[p->x][p->y + 1] != -1)
        {
            point *newPoint = new point;
            newPoint->x = p->x;
            newPoint->y = p->y + 1;
            p->y = p->y + 1;
            PushStack(trace, newPoint);
        }
        else if (!isEmptyStack(trace))
        {
            PopStack(trace, p);
            arr[p->x][p->y] = -1;
        }
        else
        {
            isFail = true;
        }
    }
    if (isGoal)
    {
        while (!isEmptyStack(trace))
        {
            PopStack(trace, p);
            cout << "(" << p->x << "," << p->y << ") ";
        }
        return;
    }
    if (isFail)
    {
        cout << "Cannot find any path!" << endl;
    }
    return;
}

int main()
{
    // stack* s = new stack;
    // pushStack(s, 4);
    // pushStack(s, 3);
    // pushStack(s, 2);
    // pushStack(s, 1);
    // printStack(s);

    // inverstStack(s);

    // printStack(s);
    // decimalToBin(10);
    int arr[3][3] = {{0, 1, -1}, {-1, -1, 1}, {-1, 1, 2}};

    printPathMatrix(arr);

    return 0;
}
