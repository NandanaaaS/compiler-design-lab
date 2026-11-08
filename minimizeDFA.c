/*
Enter no:of states and symbols: 4 2
Enter transitions:
1 2
1 3
1 2
1 3
Enter final states count: 2
Enter final states: 2 3

Equivalent states:
q0 = q1
q2 = q3

Minimized DFA:
Q0 = {q0 q1 }  --0--> Q0  --1--> Q2
Q2 = {q2 q3 }  --0--> Q0  --1--> Q2  (Final)
*/
#include<stdio.h>

int trans[10][10], final[10], mark[10][10];
int n,m;

int main()
{
    int i,j,k,change,a,b,t,rep[10];

    printf("Enter no:of states and symbols: ");
    scanf("%d %d",&n,&m);

    printf("Enter transitions:\n");

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&trans[i][j]);

    printf("Enter final states count: ");
    scanf("%d",&k);

    printf("Enter final states: ");
    for(i=0;i<k;i++)
    {
        scanf("%d",&j);
        final[j]=1;
    }

    /* Mark final and non-final pairs */
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(final[i]!=final[j])
                mark[i][j]=1;

    /* Find equivalent states */
    do
    {
        change=0;

        for(i=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(mark[i][j])
                    continue;

                for(k=0;k<m;k++)
                {
                    a=trans[i][k];
                    b=trans[j][k];

                    if(a==b)
                        continue;

                    if(a>b)
                    {
                        t=a;
                        a=b;
                        b=t;
                    }

                    if(mark[a][b])
                    {
                        mark[i][j]=1;
                        change=1;
                        break;
                    }
                }
            }
        }
    }while(change);

    printf("\nEquivalent states:\n");

    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(!mark[i][j])
                printf("q%d = q%d\n",i,j);

    /* Find representative of each state */
    for(i=0;i<n;i++)
    {
        rep[i]=i;

        for(j=0;j<i;j++)
        {
            if(!mark[j][i])
            {
                rep[i]=j;
                break;
            }
        }
    }

    /* Print minimized DFA */
    printf("\nMinimized DFA:\n");

    for(i=0;i<n;i++)
    {
        if(rep[i]!=i)
            continue;

        printf("Q%d = {",i);

        for(j=0;j<n;j++)
            if(rep[j]==i)
                printf("q%d ",j);

        printf("}");

        for(k=0;k<m;k++)
            printf("  --%d--> Q%d",k,rep[trans[i][k]]);

        if(final[i])
            printf("  (Final)");

        printf("\n");
    }

    return 0;
}
