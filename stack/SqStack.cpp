#include <stdio.h>
#include <iostream>

#pragma region init
using namespace std;

#define MAXSIZE 10

typedef int Elem;
#pragma endregion

typedef struct SqStack // 此处的为结构体名称
{
    Elem data[MAXSIZE]; // 静态分配空间，也可动态采用
    int top;
} SqStack; // 此处的为使用typedef对整个结构体重定义后的数据类型名称

void init(SqStack &s)
{
    s.top = -1;
}

bool pop(SqStack &s, Elem &e)
{
    if (s.top == -1)
    {
        return false;
    }
    e = s.data[s.top--];
    return true;
}

bool push(SqStack &s, Elem e)
{
    if (s.top == MAXSIZE - 1)
    {
        return false;
    }
    s.data[++s.top] = e;
    return true;
}

bool isEmpty(SqStack s)
{
    return s.top == -1;
}

bool getTop(SqStack s, Elem &e)
{
    if (s.top == -1)
    {
        return false;
    }
    e = s.data[s.top];
    return true;
}

int main()
{
    SqStack s;
    init(s);
    push(s, 1);
    push(s, 2);

    Elem e;
    pop(s, e);
    getTop(s, e);
    cout << e << endl;
    return 0;
}