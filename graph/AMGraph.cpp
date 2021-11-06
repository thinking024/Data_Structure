#include <iostream>
#include <string.h>

#pragma region init
using namespace std;
#define MAXINT 32767
#define MVNUM 100
typedef char VerTex;
typedef int Arc;
#pragma endregion

typedef struct AMGraph
{
    VerTex vexs[MVNUM];     // 存储顶点的数组
    Arc arcs[MVNUM][MVNUM]; // 存储边的数组
    int vexNum, arcNum;
} AMGraph;

int isVisited[MVNUM] = {0};

#pragma region queue
typedef struct QNode
{
    int data;
    struct QNode* next;
} QNode, *QNodePtr;

typedef struct {
    QNodePtr front; // 带头结点的链式队列
    QNodePtr rear; // 指向队尾元素
} LinkQueue;

void initQueue(LinkQueue &q)
{
    q.front = q.rear = new QNode; // 初始时，front与rear均指向头结点
    q.front->next = NULL;
}

bool isEmpty(LinkQueue q)
{
    return q.front == q.rear;
}

void enQueue(LinkQueue &q, int e)
{
    QNodePtr newNode = new QNode;
    newNode->next = NULL;
    newNode->data = e;
    q.rear->next = newNode;
    q.rear = newNode;
}

// 删除front后的元素
bool deQueue(LinkQueue &q, int &e)
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

// 用于定位顶点在顶点数组中的下标
int getIndex(VerTex vexs[], VerTex vex)
{
    for (size_t i = 0; i < strlen(vexs); i++)
    {
        if (vex == vexs[i])
        {
            return i;
        }
    }
    return -1;
}

void create(AMGraph &graph)
{
    cin >> graph.vexNum >> graph.arcNum;
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        cin >> graph.vexs[i];
    }
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        for (size_t j = 0; j < graph.vexNum; j++)
        {
            graph.arcs[i][j] = MAXINT; // 将邻接矩阵的权值置为无穷大
        }
    }
    for (size_t k = 0; k < graph.arcNum; k++)
    {
        VerTex start, end;
        Arc value;
        cin >> start >> end >> value;
        int i = getIndex(graph.vexs, start);
        int j = getIndex(graph.vexs, end);
        graph.arcs[i][j] = value;
        graph.arcs[j][i] = value; // 无向图的邻接矩阵是对称的
    }
}

#pragma region dfs
// 从vex顶点开始，dfs遍历连通图
void DFSConnected(AMGraph graph, int vex)
{
    cout << graph.vexs[vex] << " ";
    isVisited[vex] = 1;
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        // 访问与之相连且未被访问过的结点
        if (graph.arcs[vex][i] != MAXINT && isVisited[i] == 0)
        {
            DFSConnected(graph, i);
        }
    }
}

// dfs遍历非连通图
void DFSUnconnected(AMGraph graph)
{
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        if (isVisited[i] == 0)
        {
            DFSConnected(graph, i);
        }   
    }
}
#pragma endregion

#pragma region bfs
void BFSConnected(AMGraph graph, int vex)
{
    // 树的层次遍历：先入队，出队时再访问
    // 图的层次遍历：先访问，再入队
    cout << graph.vexs[vex] << " ";
    isVisited[vex] = 1;
    LinkQueue queue;
    initQueue(queue);
    enQueue(queue, vex);
    while (isEmpty(queue) == 0)
    {
        int index;
        deQueue(queue, index);
        
        for (size_t i = 0; i < graph.vexNum; i++)
        {
            if (graph.arcs[index][i] != MAXINT && isVisited[i] == 0)
            {
                cout << graph.vexs[i] << " ";
                isVisited[i] = 1;
                enQueue(queue, i);
            }
        }
    }
    
}

void BFSUnConnected(AMGraph graph)
{
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        if (isVisited[i] == 0)
        {
            BFSConnected(graph, i);
        }
    }
}
#pragma endregion

int main()
{
    AMGraph graph;
    create(graph);
    // DFSUnconnected(graph);
    BFSUnConnected(graph);
    return 0;
}