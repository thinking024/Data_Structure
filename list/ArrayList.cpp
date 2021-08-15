#include <stdio.h>
#include <iostream>

#pragma region init
using namespace std;

#define MAXSIZE 10

typedef int Elem;
#pragma endregion

#pragma region StaticArrayList
typedef struct StaticArrayList // 此处的为结构体名称
{
    Elem data[MAXSIZE]; // 静态分配空间
    int length;
} StaticArrayList; // 此处的为使用typedef对整个结构体重定义后的数据类型名称

void initStaticArrayList(StaticArrayList &list)
{
    list.length = 0;

    // 此for循环也可省略
    for (int i = 0; i < list.length; i++)
    {
        list.data[i] = 0;
    }
}
#pragma endregion

typedef struct DynamicArrayList
{
    Elem *data; //  动态分配空间
    int length;
} DynamicArrayList;

bool initDynamicArrayList(DynamicArrayList &list)
{
    /* 也可使用C语言的malloc
       initSize 要分配的元素个数
       sizeof(Elem) 每个元素所占空间大小
    */
    /* int initSize = 10; 
    list.data = (Elem*)malloc(sizeof(Elem) * initSize); */
    list.data = new Elem[MAXSIZE];
    if (!list.data)
    {
        return false;
    }
    list.length = 0;
    return true;
    
}

void showList(DynamicArrayList list)
{
    for (int i = 0; i < list.length; i++)
    {
        cout<<list.data[i]<<" ";
    }
    cout<<endl;
    
}

bool insertElem(DynamicArrayList &list, int index, Elem e)
{
    if (list.data == NULL)
    {
        return false;
    }
    // index 的范围是 [1, length + 1]，代表插入第index个元素之后，即数组中index - 1的下标
    if (index < 1 || index > list.length + 1)
    {
        return false;
    }
    if (list.length >= MAXSIZE) // 存储空间已满
    {
        return false;
    }
    for (int i = list.length; i >= index; i--)
    {
        list.data[i] = list.data[i - 1];
    }
    list.data[index - 1] = e;
    list.length++;
    return true;
}

// 把删除的元素用e返回
bool deleteElem(DynamicArrayList &list, int index, Elem &e)
{
    if (list.data == NULL)
    {
        return false;
    }
    //index in [1, lenghth]，删除第index个元素，即数组下标为index-1
    if (index < 1 || index > list.length)
    {
        return false;
    }
    e = list.data[index - 1];
    for (int i = index - 1; i < list.length - 1; i++)
    {
        list.data[i] = list.data[i + 1];
    }
    list.length--;
    return true;
}

int main()
{
    Elem e;
    Elem a;
    DynamicArrayList list;
    initDynamicArrayList(list);
    bool insertResult = insertElem(list, 1, 100);
    cout<<insertResult<<endl;
    showList(list);

    bool deleteResult = deleteElem(list, 1, e);
    cout<<deleteResult<<"  "<<e<<endl;
    return 0;
}