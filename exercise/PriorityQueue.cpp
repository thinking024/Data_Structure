#include <iostream>
using namespace std;

typedef int Elem;

typedef struct HeapStruct
{
    int capacity; // 最大容量
    int size;     // 当前容量
    Elem *elements;
} HeapStruct, *PriorityQueue;

void init(PriorityQueue &queue, int maxSize)
{
    queue = new HeapStruct;
    queue->capacity = maxSize;
    queue->size = 0;
    queue->elements = new Elem[maxSize + 1]; // 第0个元素空置
}

int isEmpty(PriorityQueue queue)
{
    if (queue == NULL || queue->size == 0)
        return 1;
    return 0;
}

int isFull(PriorityQueue queue)
{
    if (queue->capacity == queue->size)
    {
        return 1;
    }
    return 0;
}

int push(PriorityQueue &queue, Elem elem)
{
    if (isFull(queue))
    {
        return 0;
    }
    int i;
    // 从尾部开始，逐渐往上寻找大根堆中适合插入的位置，比elem小的元素往下走
    for (i = queue->size + 1; i > 1 && elem > queue->elements[i / 2]; i = i / 2)
    {
        queue->elements[i] = queue->elements[i / 2];
    }
    queue->elements[i] = elem;
    queue->size++;
    return 1;
}

int pop(PriorityQueue &queue, Elem &elem)
{
    if (isEmpty(queue))
    {
        return 0;
    }
    elem = queue->elements[1];
    int i, maxChild;
    Elem last = queue->elements[queue->size--];
    for (i = 1; i * 2 <= queue->size; i = maxChild)
    {
        //选择两个孩子中的最大值
        maxChild = i * 2;
        if (maxChild < queue->size && queue->elements[maxChild] < queue->elements[maxChild + 1])
            maxChild++;

        //堆底还有更小的元素，则还要往下
        if (last < queue->elements[maxChild])
            queue->elements[i] = queue->elements[maxChild];
        else
            break;
    }
    queue->elements[i] = last;
    return 1;
}

int main()
{
    PriorityQueue queue;
    init(queue, 8);
    int a[5] = {4, 5, 2, 3, 1};
    for (size_t i = 0; i < 5; i++)
    {
        push(queue, a[i]);
    }
    for (size_t i = 1; i <= queue->size; i++)
    {
        cout << queue->elements[i] << " ";
    }
    cout << endl;
    for (size_t i = 0; i < 5; i++)
    {
        Elem elem = 0;
        if (pop(queue, elem))
            cout << elem << " ";
    }
    
    return 0;
}