#include <stdio.h>
#include <iostream>

#pragma region init
using namespace std;

#define MAXSIZE 10

typedef int Elem;
#pragma endregion

typedef struct SqQueue
{
    Elem *data; //  动态分配空间
    int front;
    int rear;
} SqQueue;

bool init(SqQueue &q)
{
    // 动态分配空间，循环队列，少用1个空间，只能装 MAXSIZE-1 个元素
    q.data = new Elem[MAXSIZE];
    if (!q.data)
    {
        return false;
    }
    q.front = q.rear = 0;
    return true;
}

bool isEmpty(SqQueue q)
{
    // 考虑没有元素的初始情况
    return q.front == q.rear;
}

bool isFull(SqQueue q)
{
    // MAXSIZE-1 个元素进队，没有元素出队
    // 此时 front=0，q.rear=MAXSIZE-1
    return q.front == (q.rear + 1) % MAXSIZE;
}

bool getLength(SqQueue q)
{
    // 通常情况下 rear > front
    // 多次进队出队后，队列为空，front = rear = MAXSIZE-1
    // 此时再进一个元素，rear=0，front=MAXSIZE-1
    return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

bool enQueue(SqQueue &q, Elem e)
{
    if ((q.rear + 1) % MAXSIZE == q.front)
    {
        return false;
    }
    q.data[q.rear] = e; // 数组本身不做循环，一直向后增长，循环变动的是指针
    q.rear = (q.rear + 1) % MAXSIZE; // 尾指针+1
    return true;
}

bool deQueue(SqQueue &q, Elem &e)
{
    if (q.front == q.rear)
    {
        return false;
    }
    e = q.data[q.front];
    q.front = (q.front + 1) % MAXSIZE; // 头指针+1
    return true;
}

int main()
{
    SqQueue q;
    init(q);
    enQueue(q, 1);
    enQueue(q, 2);
    Elem e;
    deQueue(q, e);
    cout << e << endl;
    return 0;
}