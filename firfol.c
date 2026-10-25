
#include <stdio.h>
#include <ctype.h>

char p[50][100];
int first[26][128] = {0}, follow[26][128] = {0};
int nt[26] = {0}, n;

int add(int set[], int c)
{
    if (!set[c]) {
        set[c] = 1;
        return 1;
    }
    return 0;
}

int main()
{
    int i, j, k, t, x, changed, nullable;
    char A, B, c;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon):\n");
    for (i = 0; i < n; i++) {
        scanf("%99s", p[i]);
        nt[p[i][0] - 'A'] = 1;
    }

    /* FIRST */
    do {
        changed = 0;

        for (i = 0; i < n; i++) {
            A = p[i][0];
            nullable = 1;

            for (j = 2; p[i][j]; j++) {
                c = p[i][j];

                if (!isupper((unsigned char)c)) {
                    changed |= add(first[A-'A'], (unsigned char)c);
                    nullable = 0;
                    break;
                }

                x = c - 'A';

                for (k = 0; k < 128; k++)
                    if (k != '#' && first[x][k])
                        changed |= add(first[A-'A'], k);

                if (!first[x]['#']) {
                    nullable = 0;
                    break;
                }
            }

            if (nullable)
                changed |= add(first[A-'A'], '#');
        }
    } while (changed);

    /* FOLLOW */
    add(follow[p[0][0]-'A'], '$');

    do {
        changed = 0;

        for (i = 0; i < n; i++) {
            A = p[i][0];

            for (j = 2; p[i][j]; j++) {
                B = p[i][j];

                if (!isupper((unsigned char)B))
                    continue;

                nullable = 1;

                for (k = j + 1; p[i][k]; k++) {
                    c = p[i][k];

                    if (!isupper((unsigned char)c)) {
                        changed |= add(follow[B-'A'], (unsigned char)c);
                        nullable = 0;
                        break;
                    }

                    x = c - 'A';

                    for (t = 0; t < 128; t++)
                        if (t != '#' && first[x][t])
                            changed |= add(follow[B-'A'], t);

                    if (!first[x]['#']) {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable)
                    for (k = 0; k < 128; k++)
                        if (follow[A-'A'][k])
                            changed |= add(follow[B-'A'], k);
            }
        }
    } while (changed);

    printf("\nFIRST sets:\n");
    for (i = 0; i < 26; i++)
        if (nt[i]) {
            printf("FIRST(%c) = { ", 'A' + i);
            for (k = 0; k < 128; k++)
                if (first[i][k])
                    printf("%c ", k);
            printf("}\n");
        }

    printf("\nFOLLOW sets:\n");
    for (i = 0; i < 26; i++)
        if (nt[i]) {
            printf("FOLLOW(%c) = { ", 'A' + i);
            for (k = 0; k < 128; k++)
                if (follow[i][k])
                    printf("%c ", k);
            printf("}\n");
        }

    return 0;
}
