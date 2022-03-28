#include <iostream>
using namespace std;

// 将无序表a[low,mid] a[mid+1,high]合并为一个有序表b[low,high]
void merge(int a[], int b[], int low, int mid, int high)
{
    int i = low; // a[low,mid]的索引
    int j = mid + 1; // a[mid+1,high]的索引
    int k = low; // b[low,high]的索引
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            b[k++] = a[i++];
        }
        else
        {
            b[k++] = a[j++];
        }
    }

    // 把剩下的部分接入b表
    while (i <= mid)
    {
        b[k++] = a[i++];
    }
    while (j <= high)
    {
        b[k++] = a[j++];
    }
}

// 将a划分成两部分，并将其有序合并
void sort(int a[], int b[], int low, int high)
{
    int c[100];
    if (low == high)
    {
        b[low] = a[low];
        return;
    }
    int mid = (low + high) / 2;
    sort(a, c, low, mid); // 对左半边进行归并排序，结果放入c的左半边
    sort(a, c, mid + 1, high);  // 对右半边进行归并排序，结果放入c的右半边
    merge(c, b, low, mid, high); // 把结果cd额左右半边进行归并，结果放入b
}

void mergeSort(int a[], int n)
{
    sort(a, a, 0, n - 1);
}

// 链式：√，稳定：√
int main()
{
    int a[5] = {4, 3, 5, 1, 2};
    int n = 5;
    mergeSort(a, n);
    for (size_t i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    
    return 0;
}