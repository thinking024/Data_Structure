#include <stdio.h>
#include <iostream>

#pragma region init
using namespace std;

typedef int Elem;
#pragma endregion

typedef struct QNode
{
    Elem data;
    struct QNode* next;
} QNode, *QNodePtr;

typedef struct {
    QNodePtr front; // 带头结点的链式队列
    QNodePtr rear; // 指向队尾元素
} LinkQueue;

void init(LinkQueue &q)
{
    q.front = q.rear = new QNode; // 初始时，front与rear均指向头结点
    q.front->next = NULL;
}

bool isEmpty(LinkQueue q)
{
    return q.front == q.rear;
}

void enQueue(LinkQueue &q, Elem e)
{
    QNodePtr newNode = new QNode;
    newNode->next = NULL;
    newNode->data = e;
    q.rear->next = newNode;
    q.rear = newNode;
}

// 删除front后的元素
bool deQueue(LinkQueue &q, Elem &e)
{
    if (q.rear == q.front)
    {
        return false;
    }
    QNodePtr deleteNode = q.front->next; // 找到队首元素
    e = deleteNode->data;
    q.front->next = deleteNode->next;
    if (q.rear == deleteNode) // 删除的是队尾元素
    {
        q.rear = q.front;
    }
    delete deleteNode;
    return true;
}

int main()
{
    LinkQueue q;
    init(q);
    enQueue(q, 1);
    Elem e;
    deQueue(q, e);
    cout << e << endl;
    return 0;
}
