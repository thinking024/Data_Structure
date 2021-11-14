#include <stdio.h>
#include <iostream>

#pragma region init
using namespace std;


#pragma endregion

typedef struct PNode {
    float coef;
    int expn;
    struct PNode *next;
}PNode, *Polynomial;

void createPolynomial(Polynomial &p, int n) {
    p = new PNode;
    p->coef = 0.0;
    p->expn = 0;
    p->next = NULL;

    float coef;
    int expn;

    for (size_t i = 0; i < n; i++)
    {
        cin >> coef >> expn;
        PNode *newNode = new PNode;
        newNode->coef = coef;
        newNode->expn = expn;

        PNode *temp = p->next;
        PNode *pre = p;
        while (temp != NULL)
        {
            if (temp->expn > newNode->expn)
            {
                break;
            }
            temp = temp->next;
            pre = pre->next;
        }
        newNode->next = temp;
        pre->next = newNode;
    }
}

void addPolynomial(Polynomial &pa, Polynomial pb)
{
    PNode *p1, *p2, *p;
    p1 = pa->next;
    p2 = pb->next;
    p = pa;

    while (p1 && p2)
    {
        if (p1->expn < p2->expn)
        {
            p->next = p1;
            p1 = p1->next;
            p = p->next;
        }
        else if (p1->expn > p2->expn)
        {
            p->next = p2;
            p2 = p2->next;
            p = p->next;
        }
        else
        {
            if (p1->coef + p2->coef != 0)
            {
                p1->coef += p2->coef;
                p->next = p1;
                p = p->next;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    p->next = p1?p1:p2;
}

void showPolynomail(Polynomial p)
{
    p = p->next;
    while (p != NULL)
    {
        if (p->coef != 1)
        {
            cout << p->coef;
        }

        cout << "x";
        if (p->expn != 1)
        {
            cout << "^" << p->expn;
        }

        p = p->next;
        if (p != NULL)
        {
            cout << "+ ";
        }
    }
    cout << endl;
}

int main()
{
    Polynomial p, p2;

    createPolynomial(p, 4);
    createPolynomial(p2, 2);

    showPolynomail(p);
    showPolynomail(p2);

    addPolynomial(p, p2);
    showPolynomail(p);
    return 0;
}