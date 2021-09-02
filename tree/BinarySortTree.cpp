#include <string.h>
#include <iostream>

using namespace std;
typedef char Elem;

typedef struct BSTNode {
    Elem data;
    struct BSTNode *lelfChild, *rightChild;
} BSTNode, *BinarySortTree;

void insert(BinarySortTree &tree, Elem e)
{
    if (tree == NULL)
    {
        BSTNode* node = new BSTNode;
        node->data = e;
        node->lelfChild = NULL;
        node->rightChild = NULL;
        tree = node; // 将新插入的结点连接到树中
    }
    if (e < tree->data)
    {
        insert(tree->lelfChild, e);
    }
    else
    {
        insert(tree->rightChild, e);
    }
    
}

void create(BinarySortTree &tree)
{
    tree = NULL;
    Elem e;
    cin >> e;
    while (e != '#')
    {
        insert(tree, e);
        cin >> e;
    }
    
}

int main()
{
    return 0;
}