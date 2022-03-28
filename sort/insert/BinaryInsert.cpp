#include <iostream>
using namespace std;

// 链式：X，稳定：√
int main()
{
    int i, j, low, high, temp, mid;
    int a[5] = {4, 3, 5, 1, 2};
    // 依次将a[1]至a[n-1]插入前面已排好的序列中
    for (i = 1; i < 5; i++)
    {
        // a[0]到a[i-1]是有序的
        temp = a[i];
        low = 0;
        high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (a[mid] > a[i])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        // 从high+1到i-1全部往后挪，原high+1位置插入新元素a[i]
        for (j = i; j > high + 1; j--)
        {
            a[j] = a[j - 1];
        }
        a[high + 1] = temp;
    }

    for (size_t i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}