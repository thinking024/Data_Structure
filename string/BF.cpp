#include <stdio.h>
#include <string.h>
#include <iostream>

#pragma region init
using namespace std;

#define MAXSIZE 11
#pragma endregion

// 使用顺序表结构的字符串，下标范围[1, MAXSIZE]
typedef struct {
    char data[MAXSIZE + 1];
    int length;
} SqString;

// s: 主串 sub:字串 从主串中第begin个位置开始查找 
int bruteForce(SqString s, SqString sub, int begin)
{
    int i = begin; // 遍历主串过程中所用下标
    int j = 1; // 遍历子串过程中所用下标
    while (i <= s.length && j <= sub.length)
    {
        if (s.data[i] == sub.data[j])
        {
            i++;
            j++;
        }
        else
        {
            /* i = i - (j - 1) + 1
               已走过j-1步
               i-(j-1) i回到在本次匹配前原来的位置
               i+1 i向后走一步开始下一次匹配
            */
            i = i - j + 2;
            j = 1;
        }
    }

    // 考虑匹配到最后一步，并成功的情况
    if (j > sub.length)
    {
        // i为最后走到主串的位置，回退匹配中走过的sub.length步，回到匹配开始的位置
        return i - sub.length;
    }
    return 0;
    
}

void init(SqString &s)
{
    s.length = 0;
}

int main()
{
    SqString s;
    init(s);
    memcpy(s.data, " helloworld", sizeof(char) * 11);
    s.data[11] = '\0';
    s.length = 10;

    SqString sub;
    init(sub);
    memcpy(sub.data, " world", sizeof(char) * 6);
    sub.data[6] = '\0';
    sub.length = 5;

    int index = bruteForce(s, sub, 1);
    cout << index << endl;
    return 0;
}