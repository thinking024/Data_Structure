#include <iostream>
using namespace std;

int main()
{
    int i, j, low, high, temp, mid, n;
    bool flag;
    int a[5] = {4, 3, 5, 1, 2};
    n = 5;
    
    for (i = 0; i < n - 1; i++)
    {
        flag = false;
        // 从尾部开始，逆序的数逐渐往前走，其余的元素往后挪，
        // 第i次排序前，a[0, i-1]已有序，需要把a[i]确定下来
        // 或者把两层for循环反向，从头部开始，逆序的数逐渐往下沉，走到最后面a[n-1]的位置，其余的元素往前挪
        for (j = n - 1; j > i; j--)
        {
            if (a[j - 1] > a[j])
            {
                temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
                flag = true;
            }
        }
        if (flag == false)
        {
            break;
        }
    }
    
    for (size_t i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}