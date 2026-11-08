#include <stdio.h>
#include <string.h>

int main()
{
    int n, i;
    char s[20][50], d[10], a[10], b[10], op, c[10], l[10];

    printf("Enter number of statements: ");
    scanf("%d", &n);
    getchar();

    printf("Enter three address code:\n");
    for (i = 0; i < n; i++)
        fgets(s[i], 50, stdin);

    printf("\n8086 Assembly Code:\n");

    for (i = 0; i < n; i++)
    {
        if (sscanf(s[i], "goto %9s", l) == 1)
            printf("JMP %s\n", l);

        else if (sscanf(s[i], "if %9s %9s %9s goto %9s", a, c, b, l) == 4)
        {
            printf("MOV AX, %s\nCMP AX, %s\n", a, b);

            if (!strcmp(c, "<")) printf("JL %s\n", l);
            else if (!strcmp(c, ">")) printf("JG %s\n", l);
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

    return 0;
}
