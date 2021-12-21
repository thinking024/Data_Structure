#include <string.h>
#include <iostream>

using namespace std;

typedef struct Item
{
    int id;
    int weight;
    int value;
    float v_w;
    int isChoosen;
} Item;

void findItems(int pack[8][16], int i, int j, Item items[])
{
    if (i >= 0)
    {
        if (pack[i][j] == pack[i - 1][j])
        {
            items[i - 1].isChoosen = 0;
            findItems(pack, i - 1, j, items);
        }
        else if (j - items[i - 1].weight >= 0 && pack[i][j] == pack[i - 1][j - items[i - 1].weight] + items[i - 1].value)
            ;
        {
            items[i - 1].isChoosen = 1;
            findItems(pack, i - 1, j - items[i].weight, items);
        }
    }
}

void dp(Item items[], int itemsNum, int maxWeight)
{
    int pack[7 + 1][15 + 1] = {0};

    /* for (size_t i = 0; i <= maxWeight; i++)
    {
        pack[0][i] = 0;
    } */

    for (size_t i = 1; i <= itemsNum; i++)
    {
        pack[i][0] = 0;
        for (size_t j = 1; j <= maxWeight; j++)
        {
            if (j < items[i - 1].weight) // 背包容量不足
            {
                pack[i][j] = pack[i - 1][j];
            }
            else // 可以放下当前物品，选择放还是不放
            {
                pack[i][j] = (pack[i - 1][j] > (pack[i - 1][j - items[i - 1].weight] + items[i - 1].value)) ? pack[i - 1][j] : (pack[i - 1][j - items[i - 1].weight] + items[i - 1].value);
            }
        }
    }
    cout << pack[itemsNum][maxWeight] << endl;
    findItems(pack, itemsNum, maxWeight, items);
}

// 只能取得局部最优，无法获取全局最优
void greedy(Item items[], int itemsNum, int maxWeight)
{
    int max;
    Item temp;
    for (size_t i = 0; i < itemsNum - 1; i++)
    {
        max = i;
        for (size_t j = i + 1; j < itemsNum; j++)
        {
            if (items[j].v_w > items[max].v_w)
            {
                max = j;
            }
        }

        if (max != i)
        {
            temp = items[i];
            items[i] = items[max];
            items[max] = temp;
        }
    }

    cout << "id " << "v_w" << endl;
    for (size_t i = 0; i < itemsNum; i++)
    {
        cout << items[i].id << "  " << items[i].v_w << endl;
    }

    cout << "result\n";
    int weight = 0;
    int value = 0;
    for (size_t i = 0; i < itemsNum; i++)
    {
        if (items[i].weight + weight > maxWeight)
        {
            break;
        }
        items[i].isChoosen = 1;
        weight += items[i].weight;
        value += items[i].value;
        cout << items[i].id << endl;
    }
    cout << value << " " << weight << endl;
}

int main()
{
    int itemsNum = 7;
    int maxWeight = 15;
    Item items[7];
    for (size_t i = 0; i < 7; i++)
    {
        cin >> items[i].value >> items[i].weight;
        items[i].id = i + 1;
        items[i].isChoosen = 0;
        items[i].v_w = (float)items[i].value / items[i].weight;
    }
    // greedy(items, itemsNum, maxWeight);
    dp(items, itemsNum, maxWeight);
    return 0;
}