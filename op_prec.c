
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char stack[200], input[200];
    char symbols[] = "+-*/()i$";
    char table[8][8] = {
        {'>','>','<','<','<','>','<','>'},
        {'>','>','<','<','<','>','<','>'},
        {'>','>','>','>','<','>','<','>'},
        {'>','>','>','>','<','>','<','>'},
        {'<','<','<','<','<','=','<',' '},
        {'>','>','>','>',' ','>',' ','>'},
        {'>','>','>','>',' ','>',' ','>'},
        {'<','<','<','<','<',' ','<',' '}
    };

    int top = -1, ip = 0, i, j, a, b;
    char relation;

    printf("Enter expression (use i for id): ");
    fgets(input, sizeof(input), stdin);

    /* Remove spaces */
    for (i = 0, j = 0; input[i] && input[i] != '\n'; i++)
        if (!isspace((unsigned char)input[i]))
            input[j++] = input[i];
    input[j] = '\0';

    if (j == 0) {
        printf("Rejected\n");
        return 0;
    }

    /* Check valid symbols */
    for (i = 0; input[i]; i++)
        if (!strchr("i+-*/()", input[i])) {
            printf("Rejected\n");
            return 0;
        }

    strcat(input, "$");
    stack[++top] = '$';

    printf("\nSTACK\t\tINPUT\n");
    printf("$\t\t%s\n", input);

    while (1) {
        /* Find topmost terminal */
        i = top;
        while (i >= 0 && stack[i] == 'E')
            i--;

        if (i < 0) {
            printf("Rejected\n");
            break;
        }

        /* Find table indices */
        for (a = 0; symbols[a] != stack[i]; a++);
        for (b = 0; symbols[b] != input[ip]; b++);

        if (top == 1 && stack[0] == '$' &&
            stack[1] == 'E' && input[ip] == '$') {
            printf("Accepted\n");
            break;
        }

        relation = table[a][b];

        if (relation == '<' || relation == '=') {
            if (input[ip] == '$') {
                printf("Rejected\n");
                break;
            }
            stack[++top] = input[ip++];
        }
        else if (relation == '>') {
            /* i -> E */
            if (stack[top] == 'i') {
                stack[top] = 'E';
            }
            /* (E) -> E */
            else if (top >= 2 && stack[top] == ')' &&
                     stack[top-1] == 'E' &&
                     stack[top-2] == '(') {
                top -= 2;
                stack[top] = 'E';
            }
            /* E op E -> E */
            else if (top >= 2 && stack[top] == 'E' &&
                     stack[top-2] == 'E' &&
                     strchr("+-*/", stack[top-1])) {
                top -= 2;
                stack[top] = 'E';
            }
            else {
                printf("Rejected\n");
                break;
            }
        }
        else {
            printf("Rejected\n");
            break;
        }

        for (i = 0; i <= top; i++)
            printf("%c", stack[i]);
        printf("\t\t%s\n", input + ip);
    }

    return 0;
}
