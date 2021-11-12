#include <iostream>

using namespace std;
typedef char Elem;

typedef struct BSTNode {
    Elem data;
    struct BSTNode *lelfChild, *rightChild;
} BSTNode, *BinarySortTree;

BSTNode* search1(BinarySortTree tree, Elem e)
{
    while (tree != NULL && tree->data != e)
    {
        if (e < tree->data)
        {
            tree = tree->lelfChild;
        }
        else
        {
            tree = tree->rightChild;
        }
    }
    return tree; 
}

BSTNode* search2(BinarySortTree tree, Elem e)
{
    if (tree == NULL || tree->data == e)
    {
        return tree;
    }
    if (e < tree->data)
    {
        return search2(tree->lelfChild, e);
    }
    return search2(tree->rightChild, e);
}

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