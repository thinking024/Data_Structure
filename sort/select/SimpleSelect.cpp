#include <iostream>
using namespace std;

int main()
{
    int i, j, min, n, temp;
    int a[5] = {4, 3, 5, 1, 2};
    n = 5;

    // 共进行n-1躺排序
    // a[0]到a[i-1]是有序的
    // 每次将a[i]到a[n-1]最小的元素选出放到a[i]上
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        
        if (min != i)
        {
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
    
    for (size_t i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}