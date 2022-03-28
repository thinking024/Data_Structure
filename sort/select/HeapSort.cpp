#include <iostream>
using namespace std;

// a[root+1, len]已经是堆，现将a[root, len]调整为以root为根的堆
void heapAjust(int a[], int root, int len)
{
    a[0] = a[root];
    for (size_t i = 2 * root; i <= len; i++)
    {
        // 找到a[root]的两个孩子 a[2*root] a[2*root+1]中的较大者
        if (i < len && a[i] < a[i + 1])
        {
            i++;
        }
        // root大于两个孩子的值，说明已经是大根堆
        if (a[0] > a[i])
        {
            break;
        }
        // 把较大的那个孩子放到根节点，此时可能破坏了它下面原本有序的子树，需要对它下面的子树再做调整
        else
        {
            a[root] = a[i];
            root = i;
        }
    }
    a[root] = a[0]; // 把元素再放回去
}

void createHeap(int a[], int len)
{
    // a[0]空置，因为使用到了root的孩子是2*root 2*root+1的性质
    for (size_t i = len / 2; i > 0; i--)
    {
        heapAjust(a, i, len);
    }
}

void heapSort(int a[], int len)
{
    createHeap(a, len); // 先建立好大根堆
    // 每次排序前，尾部a[i+1, len]，已经有序
    for (size_t i = len; i > 1; i--)
    {
        // 把堆顶元素，即最大的元素，放到堆底a[i]的位置
        int temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        heapAjust(a, 1, i - 1); // 重新调整a[1, i-1]为大根堆
    }
}

// 链式：X，稳定：X
int main()
{
    int a[6] = {0, 4, 3, 5, 1, 2};
    int len = 5;
    // 建立大根堆，实现从小到大排序
    heapSort(a, len);
    for (size_t i = 1; i <= len; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}