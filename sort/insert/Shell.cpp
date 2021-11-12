#include <iostream>
using namespace std;

int main()
{
    int i, j, d, n;
    n = 5;
    // 对a[1, n]进行排序，a[0]作为暂存变量
    int a[6] = {0, 4, 3, 5, 1, 2};
    for (d = n / 2; d >= 1; d = d / 2)
    {
        // 每次取增量为d，从后面倒着数
        for (size_t i = d + 1; i < n + 1; i++)
        { 
            // 后面的元素 < 前面的元素
            if (a[i] < a[i - d])
            {
                // 对子序列做直接插入排序
                a[0] = a[i];
                for (j = i - d; j > 0 && a[0] < a[j]; j = j - d)
                {
                    a[j + d] = a[j];
                }
                a[j + d] = a[0];
            }
        }
    }

    for (size_t i = 1; i < n + 1; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}