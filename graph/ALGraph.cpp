#include <iostream>
#include <string.h>

#pragma region init
using namespace std;
#define MVNUM 100
typedef char VerTex;
typedef int Arc;
#pragma endregion

// 存储弧的信息
typedef struct ArcNode
{
    Arc value; //  该弧的权值
    int endIndex; // 该弧指向的终点 在结点数组VexNode中的下标
    struct ArcNode* next; // 该弧的起点 的下一条弧
} ArcNode;

//所有顶点构成的数组
typedef struct VexNode
{
    VerTex data; // 该顶点信息
    ArcNode* first; // 以该顶点 作为起点的弧
} VexNode, List[MVNUM];

typedef struct ALGraph
{
    List vertex;
    int vexNum, arcNum;
} ALGraph;

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
int getIndex(List vexs, VerTex vex)
{
    for (size_t i = 0; i < MVNUM; i++)
    {
        if (vex == vexs[i].data)
        {
            return i;
        }
    }
    return -1;   
}

void create(ALGraph &graph)
{
    cin >> graph.vexNum >> graph.arcNum;
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        cin >> graph.vertex[i].data;
        graph.vertex[i].first = NULL;
    }

    for (size_t k = 0; k < graph.arcNum; k++)
    {
        VerTex start, end;
        Arc value;
        cin >> start >> end >> value;
        int i = getIndex(graph.vertex, start);
        int j = getIndex(graph.vertex, end);

        ArcNode* node = new ArcNode;
        node->value = value;
        node->endIndex = j;

        // 把新生成的结点插入表头
        node->next = graph.vertex[i].first;
        graph.vertex[i].first = node;

        // 无向图还需将i j互换再做一次
    }
}

#pragma region dfs
void DFSConnected(ALGraph graph, int vex)
{
    VexNode node = graph.vertex[vex];
    cout << node.data << " ";
    isVisited[vex] = 1;
    ArcNode* arc = node.first;
    while (arc)
    {
        int endIndex = arc->endIndex;
        if (isVisited[endIndex] == 0)
        {
            DFSConnected(graph, endIndex);
        }
        arc = arc->next;
    }
}

// dfs遍历非连通图
void DFSUnconnected(ALGraph graph)
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
void BFSConnected(ALGraph graph, int vex)
{
    // 树的层次遍历：先入队，出队时再访问
    // 图的层次遍历：先访问，再入队
    cout << graph.vertex[vex].data << " ";
    isVisited[vex] = 1;
    LinkQueue queue;
    initQueue(queue);
    enQueue(queue, vex);
    while (isEmpty(queue) == false)
    {
        int index;
        deQueue(queue, index);
        ArcNode* arc = graph.vertex[index].first;
        while (arc)
        {
            int endIndex = arc->endIndex;
            if (isVisited[endIndex] == 0)
            {
                cout << graph.vertex[endIndex].data << " ";
                isVisited[endIndex] = 1;
                enQueue(queue, endIndex);
            }
            arc = arc->next;
        }
    }
}

void BFSUnconnected(ALGraph graph)
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
    ALGraph graph;
    create(graph);
    // DFSUnconnected(graph);
    BFSUnconnected(graph);
    return 0;
}