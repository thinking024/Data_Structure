#include <stdio.h>
#include <iostream>

#pragma region init
using namespace std;

typedef int Elem;
#pragma endregion

typedef struct DNode {
    Elem data;
    struct DNode *prior, *next;
    
}DNode, *DLinkList;

bool insertElem(DLinkList &l, Elem e, int i)
{
    // 插入时要找到第i-1个元素，所以p和j全部往前挪一位
    int j = 0; // [0, i-1]区间
    DNode* p = l; // 从头结点开始

    // 插入在p的后面，所以只要p不为空即可
    while (p && j < (i - 1))
    {
        p = p->next;
        j++;
    }

    if (!p || j > (i - 1))
    {
        cout << "fail to insert" << endl;
        return false;
    }
    DNode* elem = new DNode;
    elem->data = e;

    elem->next = p->next;
    elem->prior = p;

    // p在表尾时，后面没有元素
    // 若是循环列表，表尾指向表头，则不需要做此判断
    if (p->next) 
    {
        p->next->prior = elem;
    }
    
    p->next = elem;
    return true;
}

bool deleteElem(DLinkList &l, int i)
{
    int j = 0;
    DNode* p = l;

    // 删除p后面的元素，所以p后面的元素不为空
    while ((p->next) && j < (i - 1))
    {
        p = p->next;
        j++;
    }

    if (!(p->next) || j > (i - 1))
    {
        cout << "fail to delete" << endl;
        return false;
    }
    DNode* e = p->next;

    p->next = e->next;

    // 待删除元素e在表尾时，后面没有元素
    // 若是循环列表，表尾指向表头，则不需要做此判断
    if (e->next) 
    {
        e->next->prior = p;
    }
    
    delete e;
    return true;
}

int main()
{
    return 0;
}