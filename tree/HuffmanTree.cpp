#include <string.h>
#include <iostream>

using namespace std;

typedef struct HTNode
{
    int weight;
    int parent, leftChild, rightChild;
} HTNode, *HuffmanTree;

// 使用数组[1, 2n-1]存储结点，前n个为初始结点，后面n-1个为合并形成的结点
void createHuffmanTree(HuffmanTree &tree, int n)
{
    if (n < 1)
    {
        return;
    }
    int m = 2 * n -1;
    int i;
    tree = new HTNode[m + 1];
    for (i = 1; i < m + 1; i++)
    {
        tree[i].parent = 0;
        tree[i].leftChild = 0;
        tree[i].rightChild = 0;
    }
    for (i = 1; i < n + 1; i++)
    {
        cin >> tree[i].weight;
    }

    for (i = n + 1; i < m + 1; i++)
    {
        int minIndex1, minIndex2;
        int minWeight1, minWeight2;
        minWeight1 = minWeight2 = 100;
        // 从已合并好的[1, i-1]中，选出两个无父结点且权值最小的进行合并
        for (size_t j = 1; j < i; j++)
        {
            if (tree[j].parent == 0)
            {
                if (tree[j].weight < minWeight1)
                {
                    minIndex2 = minIndex1;
                    minWeight2 = minWeight1;

                    minIndex1 = j;
                    minWeight1 = tree[j].weight;
                }
                else if (tree[j].weight < minWeight2)
                {
                    minIndex2 = j;
                    minWeight2 = tree[j].weight;
                }
            }
        }

        tree[minIndex1].parent = i;
        tree[minIndex2].parent = i;
        tree[i].leftChild = minIndex1;
        tree[i].rightChild = minIndex2;
        tree[i].weight = minWeight1 + minWeight2;
    }
}

void show(HuffmanTree tree, int n)
{
    for (size_t i = 1; i < 2 * n; i++)
    {
        cout << i << " "  << tree[i].weight << " " << tree[i].parent << endl;  
    }
    
}

int main()
{
    HuffmanTree tree;
    createHuffmanTree(tree, 8);
    show(tree, 8);
    return 0;
}