/*
Enter number of states: 3
Enter epsilon transition matrix:
0 1 0
0 0 1
0 0 0
E-closure(q0) = { q0 q1 q2 }
E-closure(q1) = { q1 q2 }
E-closure(q2) = { q2 }
*/
#include <stdio.h>

int e[10][10], n;
int closure[10];

void findClosure(int s)
{
    int i;

    closure[s] = 1;

    for(i = 0; i < n; i++)
    {
        if(e[s][i] == 1 && closure[i] == 0)
        {
            findClosure(i);
        }
    }
}

int main()
{
    int i, j;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transition matrix:\n");

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &e[i][j]);

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            closure[j] = 0;

        findClosure(i);

        printf("E-closure(q%d) = { ", i);

        for(j = 0; j < n; j++)
        {
            if(closure[j])
                printf("q%d ", j);
        }

        printf("}\n");
    }

    return 0;
}
