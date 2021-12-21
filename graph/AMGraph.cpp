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
    Arc arcs[MVNUM][MVNUM]; // 存储边的数组，无向图主对角线为0，有向图主对角线为无穷
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
        // graph.arcs[j][i] = value; // 无向图的邻接矩阵是对称的
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

#pragma region prim for connected undirected
// 记录与生成树相连的n-1条最小权值的边
struct 
{
    VerTex adjVex; // 边的一个顶点
    Arc weight;
} closeEdge[MVNUM];

void prim(AMGraph graph, VerTex vex)
{
    // 初始化与生成树相连的边
    int index = getIndex(graph.vexs, vex);
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        closeEdge[i].adjVex = vex;
        closeEdge[i].weight = graph.arcs[index][i];
    }
    closeEdge[index].weight = 0;

    // 生成n-1条边
    for (size_t i = 1; i < graph.vexNum; i++)
    {
        // 从剩下还未划分进生成树的顶点中，找到权值最小的边
        int minWeight = MAXINT;
        int minIndex;
        for (size_t j = 0; j < graph.vexNum; j++)
        {
            if (closeEdge[j].weight != 0 && closeEdge[j].weight < minWeight)
            {
                minIndex = j;
                minWeight = closeEdge[j].weight;
            }
        }

        // 得到这条最小边的两个顶点
        closeEdge[minIndex].weight = 0;
        VerTex start = closeEdge[minIndex].adjVex;
        VerTex end = graph.vexs[minIndex];
        cout << start << "--"<< end << " ";

        // 新顶点归入生成树后，重新计算生成树到各个顶点的距离
        for (size_t j = 0; j < graph.vexNum; j++)
        {
            if (graph.arcs[minIndex][j] < closeEdge[j].weight)
            {
                closeEdge[j].weight = graph.arcs[minIndex][j];
                closeEdge[j].adjVex = graph.vexs[minIndex];
            }
        }
    }
}
#pragma endregion

#pragma region kruskal for connected undirected
struct edge
{
    int startIndex; // 边的两个顶点
    int endIndex;
    Arc weight;
} edges[MVNUM];

int vexSet[MVNUM]; // 每个顶点所属的连通分量

// 初始化edges数组，并对其进行排序
void initEdges(AMGraph graph)
{
    int index = 0;
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        for (size_t j = 0; j <= i; j++)
        {
            if (graph.arcs[i][j] != MAXINT)
            {
                edges[index].startIndex = j;
                edges[index].endIndex = i;
                edges[index].weight = graph.arcs[i][j];
                index++;
            }
        }
    }

    for (size_t i = 0; i < graph.arcNum - 1; i++)
    {
        int min = i;
        for (size_t j = i + 1; j < graph.arcNum; j++)
        {
            if (edges[j].weight < edges[min].weight)
            {
                min = j;
            }
        }
        
        if (min != i)
        {
            struct edge temp = edges[i];
            edges[i] = edges[min];
            edges[min] = temp;
        }
    }
}

void kruskal(AMGraph graph)
{
    initEdges(graph);
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        vexSet[i] = i;
    }

    for (size_t i = 0; i < graph.arcNum; i++)
    {
        int startIndex = edges[i].startIndex;
        int endIndex = edges[i].endIndex;
        int set1 = vexSet[startIndex];
        int set2 = vexSet[endIndex];

        // 边的两个顶点不属于同一个连通分量，即加入该边后不会构成回路
        if (set1 != set2)
        {
            cout << graph.vexs[startIndex] << "--" << graph.vexs[endIndex] << " ";
            
            // 将两个连通分量合并
            for (size_t j = 0; j < graph.vexNum; j++)
            {
                if (vexSet[j] == set2)
                {
                    vexSet[j] = set1;
                }
            }
        }
    }
}
#pragma endregion

#pragma region dijkstra for directed net
int sure[MVNUM]; // 判断是否找到了源点到每个顶点最短路径
int path[MVNUM]; // 源点到终点的最短路径上的前驱
int dis[MVNUM];

void dijkstra(AMGraph graph, int vexIndex)
{
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        sure[i] = 0;
        dis[i] = 0;
        dis[i] = graph.arcs[vexIndex][i];
        if (dis[i] != MAXINT)
        {
            path[i] = vexIndex;
        }
        else
        {
            path[i] = -1;
        }
    }
    
    sure[vexIndex] = 1;
    dis[vexIndex] = MAXINT;
    for (size_t i = 0; i < graph.vexNum - 1; i++)
    {
        // 从剩下未确定的顶点中，找到距离最小的
        int minIndex = vexIndex;
        for (size_t j = 0; j < graph.vexNum; j++)
        {
            if (sure[j] == 0 && dis[j] < dis[minIndex])
            {
                minIndex = j;
            }
        }
        
        // 归入路径后，将剩下未确定的路径都更新一次
        sure[minIndex] = 1;
        for (size_t j = 0; j < graph.vexNum; j++)
        {
            if (sure[j] == 0 && dis[minIndex] + graph.arcs[minIndex][j] < dis[j])
            {
                path[j] = minIndex;
                dis[j] = dis[minIndex] + graph.arcs[minIndex][j];
            }
        }
    }

    // 输出路径
    for (size_t i = 0; i < graph.vexNum; i++)
    {
        if (sure[i] == 1)
        {
            cout << dis[i] << "=";
            int j = i;
            while (j != vexIndex)
            {
                cout << graph.vexs[j] << "<-";
                j = path[j];
            }
            cout << graph.vexs[vexIndex] << endl;
        }
    }
}

#pragma endregion

int main()
{
    AMGraph graph;
    create(graph);
    // DFSUnconnected(graph);
    // BFSUnConnected(graph);
    // prim(graph, 'a');
    // kruskal(graph);
    dijkstra(graph, 0);
    return 0;
}
