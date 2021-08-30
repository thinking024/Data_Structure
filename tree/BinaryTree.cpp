#include <string.h>
#include <iostream>

using namespace std;
typedef char Elem;

typedef struct BTNode {
    Elem data;
    struct BTNode *lelfChild, *rightChild;
} BTNode, *BinaryTree;

typedef struct QNode
{
    BTNode* data;
    struct QNode* next;
} QNode, *QNodePtr;

#pragma region queue
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

void enQueue(LinkQueue &q, BTNode* e)
{
    QNodePtr newNode = new QNode;
    newNode->next = NULL;
    newNode->data = e;
    q.rear->next = newNode;
    q.rear = newNode;
}

// 删除front后的元素
bool deQueue(LinkQueue &q, BTNode* &e)
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

#pragma endregion

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

void levelOrder(BinaryTree tree)
{
    LinkQueue queue;
    init(queue);
    enQueue(queue, tree);
    while (isEmpty(queue) == false) //队列非空
    {
        BTNode* e;
        deQueue(queue, e);
        cout << e->data << " ";
        if (e->lelfChild)
        {
            enQueue(queue, e->lelfChild);
        }
        if (e->rightChild)
        {
            enQueue(queue, e->rightChild);
        }
    }
}

void preOrder(BinaryTree tree)
{
    BTNode* stack[100];
    int top = -1;
    while (tree || top != -1)
    {
        if (tree)
        {
            cout << tree->data << " "; // 先访问根结点
            stack[++top] = tree; // 将根结点入栈
            tree = tree->lelfChild; // 一直向左走
        }
        else
        {
            // 左子树为空时，将根节点出栈，再一直向右走
            tree = stack[top--];
            tree = tree->rightChild;
        }
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
    cout << endl;
    levelOrder(tree);
    cout << endl;
    preOrder(tree);
    return 0;
}