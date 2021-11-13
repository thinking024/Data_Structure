#include <iostream>
using namespace std;


int partion(int a[], int low, int high)
{
    int pivot = a[low]; // 取第一个元素作为枢轴
    while (low < high)
    {
        //从尾部开始，寻找到第一个小于枢轴的元素，将其放到前面
        while (low < high && a[high] >= pivot)
        {
            high--;
        }
        a[low] = a[high];

        while (low < high && a[low] <= pivot)
        {
            low++;
        }
        a[high] = a[low];
    }
    a[low] = pivot;
    return pivot;
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partion(a, low, high); // 从枢轴位置开始划分子表
        quickSort(a, low, pivotIndex - 1);
        quickSort(a, pivotIndex + 1, high);
    }
}

int main()
{
    int a[5] = {4, 3, 5, 1, 2};
    int n = 5;
    int low = 0;
    int high = n - 1;
    quickSort(a, low, high);
    for (size_t i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}