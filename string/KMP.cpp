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

int* getNext(SqString s)
{
    int* next = new int[s.length + 1];
    next[1] = 0;
    int i = 1;
    int j = 0;
    while (i < s.length)
    {
        if (j == 0 || s.data[i] == s.data[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    
    return next;
}

int* getNextVal(SqString s)
{
    int* nextVal = new int[s.length + 1];
    nextVal[1] = 0;
    int i = 1;
    int j = 0;
    while (i < s.length)
    {
        if (j == 0 || s.data[i] == s.data[j])
        {
            i++;
            j++;
            if (s.data[i] != s.data[j])
            {
                nextVal[i] = j;
            }
            else
            {
                nextVal[i] = nextVal[j]; // 前面有出现过重复的字符
            }
            
        }
        else
        {
            j = nextVal[j];
        }
    }
    
    return nextVal;
}

int kmp(SqString s, SqString sub, int begin)
{
    if (begin < 1 || begin > s.length)
    {
        return 0;
    }
    
    int *next = getNextVal(sub);
    int i = begin;
    int j = 1;
    while (i <= s.length && j <= sub.length)
    {
        // 在第一个字符就匹配失败，j通过next[1] = 0
        // j++ 变为1， i++ i向后移1步
        if (s.data[i] == sub.data[j] || j == 0)
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j > sub.length)
    {
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
    cout << kmp(s, sub, 1) << endl;

    /* int* next = getNextVal(sub);
    for (size_t i = 1; i <= sub.length; i++)
    {
        cout << next[i] << " ";
    } */
    
    return 0;
}