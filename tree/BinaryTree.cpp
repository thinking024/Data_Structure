#include <string.h>
#include <iostream>

using namespace std;
typedef char Elem;

typedef struct BTNode {
    Elem data;
    struct BTNode *lelfChild, *rightChild;
} BTNode, *BinaryTree;

// 先序创建二叉树
void create(BinaryTree &tree)
{
    Elem newData;
    cin >> newData;
    if (newData == '#')
    {
        tree = NULL;
    }
    else
    {
        tree = new BTNode;
        tree->data = newData;
        create(tree->lelfChild);
        create(tree->rightChild);
    }
}

void inOrderTraverse(BinaryTree tree)
{
    if (tree)
    {
        inOrderTraverse(tree->lelfChild);
        cout << tree->data << " ";
        inOrderTraverse(tree->rightChild);
    }
}


// 二叉树深度 = max(结点的层次) = max(左、右子树深度)+1
// 深度从1开始计算
int getDepth(BinaryTree tree)
{
    if (tree == NULL)
    {
        return 0; // 空树深度为0
    }
    else
    {
        int leftDepth = getDepth(tree->lelfChild);
        int rightDepth = getDepth(tree->rightChild);
        return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
    }
}

// 结点个数 = 左子树结点个数 + 右子树结点个数 + 1(代表根节点)
int getNodeCount(BinaryTree tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    else
    {
        return getNodeCount(tree->lelfChild) + getNodeCount(tree->rightChild) + 1;
    }
}

int main()
{
    BinaryTree tree;
    create(tree);
    inOrderTraverse(tree);
    cout << " " << getDepth(tree) << " " << getNodeCount(tree);
    return 0;
}