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
    List vertexs;
    int vexNum, arcNum;
} ALGraph;

int isVisited[MVNUM] = {0};

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
        cin >> graph.vertexs[i].data;
        graph.vertexs[i].first = NULL;
    }

    for (size_t k = 0; k < graph.arcNum; k++)
    {
        VerTex start, end;
        Arc value;
        cin >> start >> end >> value;
        int i = getIndex(graph.vertexs, start);
        int j = getIndex(graph.vertexs, end);

        ArcNode* node = new ArcNode;
        node->value = value;
        node->endIndex = j;

        // 把新生成的结点插入表头
        node->next = graph.vertexs[i].first;
        graph.vertexs[i].first = node;

        // 无向图还需将i j互换再做一次
    }
}

void DFSConnected(ALGraph graph, int vex)
{
    VexNode node = graph.vertexs[vex];
    cout << node.data << " ";
    isVisited[vex] = 1;
    ArcNode* arc = node.first;
    while (arc)
    {
        if (isVisited[arc->endIndex] == 0)
        {
            DFSConnected(graph, arc->endIndex);
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

int main()
{
    ALGraph graph;
    create(graph);
    DFSUnconnected(graph);
    return 0;
}