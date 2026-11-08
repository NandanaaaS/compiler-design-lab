/*
Enter number of states and symbols: 3 2
Enter symbols:
a b
Enter epsilon transition matrix:
0 1 0
0 0 1
0 0 0
Enter transitions for each symbol:
Symbol a:
1 0 0
0 1 0
0 0 0
Symbol b:
0 0 0
0 0 0
0 0 1
Enter final states (0 or 1):
0 0 1

NFA without epsilon:

Symbol a:
q0 -> q0 q1 q2 
q1 -> q1 q2 
q2 -> 

Symbol b:
q0 -> q2 
q1 -> q2 
q2 -> q2 

Final states: q0 q1 q2 
*/
#include <stdio.h>

int e[10][10], t[10][10][10];
int newt[10][10][10];
int closure[10];
int final[10], newfinal[10];
char sym[10];
int n, m;

void findClosure(int s)
{
    int i;
    closure[s] = 1;
    for(i = 0; i < n; i++)
    {
        if(e[s][i] && !closure[i])
            findClosure(i);
    }
}
int main()
{
    int i, j, k, a, x;
    printf("Enter number of states and symbols: ");
    scanf("%d %d", &n, &m);
    printf("Enter symbols:\n");
    for(i = 0; i < m; i++)
        scanf(" %c", &sym[i]);

    printf("Enter epsilon transition matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &e[i][j]);
  
    printf("Enter transitions for each symbol:\n");
    for(a = 0; a < m; a++)
    {
        printf("Symbol %c:\n", sym[a]);
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &t[a][i][j]);
    }

    printf("Enter final states (0 or 1):\n");
    for(i = 0; i < n; i++)
        scanf("%d", &final[i]);
  
    /* Convert epsilon-NFA to NFA */
    for(i = 0; i < n; i++)
    {
        for(a = 0; a < m; a++)
        {
            /* Find epsilon-closure(i) */
            for(j = 0; j < n; j++)
                closure[j] = 0;

            findClosure(i);

            /* Take symbol transition from closure states */

            for(j = 0; j < n; j++)
            {
                if(closure[j])
                {
                    for(k = 0; k < n; k++)
                    {
                        if(t[a][j][k])
                        {
                            /* Find epsilon-closure(k) */

                            for(x = 0; x < n; x++)
                                closure[x] = 0;

                            findClosure(k);

                            /* Add states to new transition */

                            for(x = 0; x < n; x++)
                            {
                                if(closure[x])
                                    newt[a][i][x] = 1;
                            }

                            /* Recalculate closure(i) */

                            for(x = 0; x < n; x++)
                                closure[x] = 0;

                            findClosure(i);
                        }
                    }
                }
            }
        }
    }

    /* Find new final states */

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            closure[j] = 0;

        findClosure(i);

        for(j = 0; j < n; j++)
            if(closure[j] && final[j])
                newfinal[i] = 1;
    }

    /* Display NFA transition table */

    printf("\nNFA without epsilon:\n");

    for(a = 0; a < m; a++)
    {
        printf("\nSymbol %c:\n", sym[a]);

        for(i = 0; i < n; i++)
        {
            printf("q%d -> ", i);

            for(j = 0; j < n; j++)
            {
                if(newt[a][i][j])
                    printf("q%d ", j);
            }

            printf("\n");
        }
    }

    /* Display final states */
    printf("\nFinal states: ");
    for(i = 0; i < n; i++)
        if(newfinal[i])
            printf("q%d ", i);
    printf("\n");
    return 0;
}
