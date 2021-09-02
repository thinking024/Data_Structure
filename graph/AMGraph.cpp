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
    VerTex vexs[MVNUM]; // 存储顶点的数组
    Arc arcs[MVNUM][MVNUM]; // 存储边的数组
    int vexNum, arcNum;
} AMGraph;

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
    for (size_t i = 0; i < graph.arcNum; i++)
    {
        for (size_t j = 0; j < graph.arcNum; i++)
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

int main()
{
    return 0;
}