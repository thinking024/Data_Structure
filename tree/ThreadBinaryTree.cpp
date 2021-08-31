#include <iostream>
using namespace std;
typedef char Elem;

typedef struct ThreadBTNode
{
    Elem data;
    struct ThreadBTNode *lelfChild, *rightChild;
    int leftTag, rightTag; // 0：左右指针指向孩子；1：左右指针指向前驱后继
} ThreadBTNode, *ThreadBinaryTree;

void create(ThreadBinaryTree &tree)
{
    Elem newData;
    cin >> newData;
    if (newData == '#')
    {
        tree = NULL;
    }
    else
    {
        tree = new ThreadBTNode;
        tree->data = newData;
        create(tree->lelfChild);
        create(tree->rightChild);
    }
}

void inOrderThread(ThreadBinaryTree &tree, ThreadBTNode *&preNode)
{
    if (tree)
    {
        inOrderThread(tree->lelfChild, preNode); // 线索化左子树

        // 线索化根节点
        if (tree->lelfChild == NULL)
        {
            tree->lelfChild = preNode;
            tree->leftTag = 1;
        }
        else
        {
            tree->leftTag = 0;
        }

        // 线索化其前驱结点
        if (preNode)
        {
            if (preNode->rightChild == NULL)
            {
                preNode->rightChild = tree;
                preNode->rightTag = 1;
            }
            else
            {
                preNode->rightTag = 0;
            }
        }
        preNode = tree;

        inOrderThread(tree->rightChild, preNode); // 线索化右子树
    }
}

void inOrderThreadWithHead(ThreadBinaryTree &tree, ThreadBTNode* &head)
{
    head = new ThreadBTNode;
    head->lelfChild = tree; // 头结点的左孩子为根
    head->leftTag = 0; // 头结点无前驱

    ThreadBTNode* preNode = head;
    inOrderThread(tree, preNode); // 在此过程中，第一个访问的结点的前驱会指向头结点

    preNode->rightChild = head; // 最后访问的结点的后继为头结点
    preNode->rightTag = 1;

    head->rightChild = preNode; // 头结点的后继为最后访问的结点
    head->rightTag = 1;
}

void inOrderTraverse(ThreadBTNode* head)
{
    ThreadBTNode* node = head->lelfChild; // 头结点的左孩子为根
    // 一直向后继结点遍历，一圈结束后又回到了头结点
    while (node != head)
    {
        //一直往左下方，找到最先开始访问的结点
        while (node->leftTag == 0)
        {
            node = node->lelfChild;
        }
        cout << node->data << " ";

        //通过后继指针一直往后遍历到最后一个结点
        while (node->rightTag == 1 && node->rightChild != head)
        {
            node = node->rightChild;
            cout << node->data << " ";
        }
        
        // 如果没有后继指针，那么就访问其右子树，同样地也能找到其后继结点
        node = node->rightChild;
    }
    
}

int main()
{
    ThreadBinaryTree tree;
    create(tree);
    ThreadBTNode* head;
    inOrderThreadWithHead(tree, head);
    inOrderTraverse(head);
    return 0;
}