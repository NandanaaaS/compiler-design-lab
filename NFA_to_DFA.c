/*
Enter no:of states and symbols: 3 2
Enter no:of final states: 1
2
NFA Transitions:
Enter no:of destinations: 2
0 1
Enter no:of destinations: 1
0
Enter no:of destinations: 1
2
Enter no:of destinations: 0
Enter no:of destinations: 0
Enter no:of destinations: 1
2

DFA:
D0 = {q0 }  --0--> D1  --1--> D0
D1 = {q0 q1 }  --0--> D2  --1--> D0
D2 = {q0 q1 q2 } [FINAL]  --0--> D2  --1--> D3
D3 = {q0 q2 } [FINAL]  --0--> D1  --1--> D3
*/

#include<stdio.h>

int nfa[10][10][10], c[10][10];
int dfa[100], trans[100][10];
int final[10], dfinal[100];
int d = 1;
int m, n;

int main()
{
    int i, j, k, x, y, next;

    printf("Enter no:of states and symbols: ");
    scanf("%d %d", &n, &m);

    printf("Enter no:of final states: ");
    scanf("%d", &x);

    for(i = 0; i < x; i++)
    {
        scanf("%d", &y);
        final[y] = 1;
    }

    printf("NFA Transitions:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("Enter no:of destinations: ");
            scanf("%d", &c[i][j]);

            for(k = 0; k < c[i][j]; k++)
                scanf("%d", &nfa[i][j][k]);
        }
    }

    /* Initial DFA state = {q0} */

    dfa[0] = 1;

    for(i = 0; i < d; i++)
    {
        for(j = 0; j < m; j++)
        {
            next = 0;

            for(k = 0; k < n; k++)
            {
                if(dfa[i] & (1 << k))
                {
                    for(x = 0; x < c[k][j]; x++)
                        next = next | (1 << nfa[k][j][x]);
                }
            }

            for(y = 0; y < d; y++)
            {
                if(dfa[y] == next)
                    break;
            }

            if(y == d)
            {
                dfa[d] = next;
                d++;
            }

            trans[i][j] = y;
        }
    }

    /* Identify final DFA states */

    for(i = 0; i < d; i++)
        for(k = 0; k < n; k++)
            if((dfa[i] & (1 << k)) && final[k])
                dfinal[i] = 1;

    printf("\nDFA:\n");

    for(i = 0; i < d; i++)
    {
        printf("D%d = {", i);

        for(k = 0; k < n; k++)
            if(dfa[i] & (1 << k))
                printf("q%d ", k);

        printf("}");

        if(dfinal[i])
            printf(" [FINAL]");

        for(j = 0; j < m; j++)
            printf("  --%d--> D%d", j, trans[i][j]);

        printf("\n");
    }

    return 0;
}
