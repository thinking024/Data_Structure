#include <stdio.h>
#include <iostream>
using namespace std;

typedef int Elem;

typedef struct StackNode {
    struct StackNode* next;
    Elem data;
} StackNode, *LinkStack;

void init(LinkStack &s)
{
    s = NULL;
}

void push(LinkStack &s, Elem e)
{
    StackNode* node = new StackNode;
    node->data = e;
    node->next = s;
    s = node;
}

bool pop(LinkStack &s, Elem &e)
{
    if (s == NULL)
    {
        return false;
    }
    e = s->data;
    StackNode* node = s;
    s = s->next;
    delete node;
    return true;
}

bool getTop(LinkStack s, Elem &e)
{
    if (s == NULL)
    {
        return false;
    }
    e = s->data;
    return true;
}

int main()
{
    LinkStack s;
    init(s);
    push(s, 1);
    Elem e = getTop(s, e);
    cout << e << endl;
    return 0;
}