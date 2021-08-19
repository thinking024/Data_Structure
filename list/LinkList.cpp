#include <stdio.h>
#include <iostream>

#pragma region init
using namespace std;


typedef int Elem;
#pragma endregion

typedef struct LNode {
    Elem data;
    struct LNode *next;
    
}LNode, *LinkList;

// 用不上，在创建链表时就完成初始化
bool initList(LinkList &l)
{
    l = new LNode;
    l->next = NULL;
    return true;
}

// 按位置查找第i个元素，不包含头节点，从1开始
// 考虑链表中无数据，和只有1个数据的情况，就可判断初始条件
bool getElem(LinkList l, Elem &e, int i)
{
    int j = 1; // 用来防止i<=0，代表遍历时走到第j个元素
    LNode* p = l->next; // 用来防止i>链表总长度

    // j=i时找到元素，跳出循环；p=null时代表找到尽头了
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
    {
        return false;
    }
    e = p->data;
    return true;
}

LNode* locateElem(LinkList l, Elem e)
{
    /* LNode* p;
    for (p = l->next;!p;p = p->next)
    {
        if (p->data == e)
        {
            break;
        }
    } */
    LNode* p = l->next;
    while (!p && p->data != e)
    {
        p = p ->next;
    }
    
    return p;
    
}

// 在i-1 i之间插入，成为新的第i个元素
bool insertElem(LinkList &l, Elem e, int i)
{
    // 插入时要找到第i-1个元素，所以p和j全部往前挪一位
    int j = 0; // [0, i-1]区间
    LNode* p = l; // 从头结点开始

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
    LNode* elem = new LNode;
    elem->data = e;
    elem->next = p->next;
    p->next = elem;
    return true;
}

bool deleteElem(LinkList &l, int i)
{
    int j = 0;
    LNode* p = l;

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
    LNode* e = p->next;
    p->next = e->next;
    delete e;
    return true;
}

void createFromHead(LinkList &l, int n)
{
    l = new LNode;
    l->next = NULL;
    int i;
    for (i = 0;i < n; i++)
    {
        /* code */
        LNode* p = new LNode;
        p->data = n - i;
        p->next = l->next;
        l->next = p;
    }
    
}

void createFromTail(LinkList &l, int n)
{
    // l维持头节点不动，q去遍历链表
    l = new LNode;
    l->next = NULL;
    int i;
    LNode* q = l;
    for (i = 0; i < n; i++)
    {
        LNode* p = new LNode;
        p->data = i + 1;
        p->next = NULL;
        q->next = p;
        q = p;
    }
}

void show(LinkList l)
{
    l = l->next;
    while (l)
    {
        cout << l->data << " ";
        l = l->next;
    }
    cout << endl;
}

int main()
{
    LinkList l;
    // int initResult = initList(l);
    // cout << initResult << endl;
    // insertElem(l, 2, 1);
    createFromHead(l, 5);
    insertElem(l, 6, 6);
    show(l);
    int result = deleteElem(l, 2);
    show(l);
    return 0;
}