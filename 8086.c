#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* put spaces around operators so "a+b" becomes " a + b " */
void fix(char *s)
{
    char t[150];
    int i, j = 0;
    for (i = 0; s[i]; i++)
    {
        if (strchr("+-*/", s[i]))
            j += sprintf(t + j, " %c ", s[i]);
        else if (s[i] != '\0' && strchr("<>=!", s[i]))
        {
            if (i == 0 || !strchr("<>=!", s[i - 1])) t[j++] = ' ';
            t[j++] = s[i];
            if (!strchr("<>=!", s[i + 1])) t[j++] = ' ';
        }
        else t[j++] = s[i];
    }
    t[j] = 0;
    strcpy(s, t);
}

int main()
{
    int n, i, j, nv = 0;
    char s[20][150], d[10], a[10], b[10], op, c[10], l[10];
    char v[30][10], tmp[150], *t, *p;

    printf("Enter number of statements: ");
    scanf("%d", &n);
    getchar();

    printf("Enter three address code:\n");
    for (i = 0; i < n; i++)
    {
        fgets(s[i], 50, stdin);
        fix(s[i]);
    }

    /* collect variables (skip numbers, labels, if, goto) */
    for (i = 0; i < n; i++)
    {
        if (strchr(s[i], ':')) continue;
        strcpy(tmp, s[i]);
        for (p = "", t = strtok(tmp, " \n"); t; p = t, t = strtok(0, " \n"))
            if (isalpha(t[0]) && strcmp(t, "if") && strcmp(t, "goto") && strcmp(p, "goto"))
            {
                for (j = 0; j < nv && strcmp(v[j], t); j++);
                if (j == nv) strcpy(v[nv++], t);
            }
    }

    printf("\n8086 Assembly Code:\nDATA SEGMENT\n");
    for (i = 0; i < nv; i++)
        printf("\t%s DW ?\n", v[i]);
    printf("DATA ENDS\nCODE SEGMENT\n\tASSUME CS:CODE, DS:DATA\n");
    printf("START:\tMOV AX, DATA\n\tMOV DS, AX\n");

    for (i = 0; i < n; i++)
    {
        if (sscanf(s[i], "goto %9s", l) == 1)
            printf("JMP %s\n", l);

        else if (sscanf(s[i], "if %9s %9s %9s goto %9s", a, c, b, l) == 4)
        {
            printf("MOV AX, %s\nCMP AX, %s\n", a, b);

            if (!strcmp(c, "<")) printf("JL %s\n", l);
            else if (!strcmp(c, ">")) printf("JG %s\n", l);
            else if (!strcmp(c, "<=")) printf("JLE %s\n", l);
            else if (!strcmp(c, ">=")) printf("JGE %s\n", l);
            else if (!strcmp(c, "==")) printf("JE %s\n", l);
            else if (!strcmp(c, "!=")) printf("JNE %s\n", l);
        }

        else if (strchr(s[i], ':'))
            printf("%s", s[i]);

        else if (sscanf(s[i], "%9s = %9s %c %9s", d, a, &op, b) == 4)
        {
            printf("MOV AX, %s\n", a);

            if (op == '+') printf("ADD AX, %s\n", b);
            else if (op == '-') printf("SUB AX, %s\n", b);
            else if (op == '*') printf("MOV BX, %s\nMUL BX\n", b);
            else if (op == '/') printf("MOV BX, %s\nXOR DX, DX\nDIV BX\n", b);

            printf("MOV %s, AX\n", d);
        }

        else if (sscanf(s[i], "%9s = %9s", d, a) == 2)
            printf("MOV AX, %s\nMOV %s, AX\n", a, d);
    }

    printf("MOV AH, 4CH\nINT 21H\nCODE ENDS\nEND START\n");
    return 0;
}
