#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100], stack[200];
int top = -1, ip = 0, len;

int prec(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void display(char action[])
{
    int i;
    printf("$");
    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("\t\t");

    for (i = ip; i < len; i++)
        printf("%c", input[i]);

    printf("$\t\t%s\n", action);
}

int reduce()
{
    char next = (ip < len) ? input[ip] : '$';

    // Rule 1: E -> i
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        display("Reduce E->i");
        return 1;
    }

    // Rule 2: E -> (E)
    if (top >= 2 && stack[top-2] == '(' && stack[top-1] == 'E' && stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
        display("Reduce E->(E)");
        return 1;
    }

    // Rule 3: E -> E op E
    if (top >= 2 && stack[top-2] == 'E' && strchr("+-*/", stack[top-1]) && stack[top] == 'E')
    {
        // FIX: Only reduce if next token is an operator with lower/equal precedence, or an end-marker
        if (next == '$' || next == ')' || 
            (strchr("+-*/", next) && prec(stack[top-1]) >= prec(next)))
        {
            top -= 2;
            stack[top] = 'E';
            display("Reduce E->E op E");
            return 1;
        }
    }

    return 0;
}

int main()
{
    int i = 0, j = 0;

    printf("Enter input string: ");
    if (!fgets(input, sizeof(input), stdin))
        return 0;

    // FIX: Safely convert names/numbers to 'i' without double-incrementing index loops
    while (input[i])
    {
        if (isspace((unsigned char)input[i]))
        {
            i++;
            continue;
        }

        if (isalnum((unsigned char)input[i]) || input[i] == '_')
        {
            while (isalnum((unsigned char)input[i]) || input[i] == '_')
            {
                i++;
            }
            input[j++] = 'i';
        }
        else
        {
            input[j++] = input[i++];
        }
    }

    input[j] = '\0';
    len = j;

    if (len == 0)
    {
        printf("Rejected\n");
        return 0; // Prevent downstream execution on empty text
    }

    // Validate characters
    for (i = 0; i < len; i++)
    {
        if (!strchr("+-*/()i", input[i]))
        {
            printf("Invalid characters: %c\n", input[i]);
            return 0;
        }
    }

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    display("Initial");

    while (ip < len)
    {
        stack[++top] = input[ip++];
        display("Shift");

        while (reduce());
    }

    while (reduce());

    if (top == 0 && stack[0] == 'E')
        printf("\nAccepted\n");
    else
        printf("\nRejected\n");

    return 0;
}
