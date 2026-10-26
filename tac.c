#include <stdio.h>
#include <string.h>
#include <ctype.h>

char op[100], val[100][20];
int top = -1, vtop = -1, temp = 1;

int prec(char c)
{
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void generate()
{
    char a[20], b[20], r[20], c = op[top--];

    strcpy(b, val[vtop--]);
    strcpy(a, val[vtop--]);

    sprintf(r, "t%d", temp++);
    printf("%s = %s %c %s\n", r, a, c, b);
    strcpy(val[++vtop], r);
}

int main()
{
    char s[100], lhs[20] = "";
    int i = 0, j = 0;

    printf("Enter expression: ");
    scanf("%99s", s);

    while (s[i] && s[i] != '=') lhs[j++] = s[i++];
    lhs[j] = '\0';
    if (s[i] == '=') i++;

    printf("\nThree Address Code:\n");

    while (s[i]) {
        if (isalnum((unsigned char)s[i]) || s[i] == '_') {
            j = 0;
            vtop++;
            while (isalnum((unsigned char)s[i]) || s[i] == '_')
                val[vtop][j++] = s[i++];
            val[vtop][j] = '\0';
        }
        else if (s[i] == '(')
            op[++top] = s[i++];
        else if (s[i] == ')') {
            while (top != -1 && op[top] != '(') generate();
            if (top == -1) {
                printf("Invalid expression\n");
                return 1;
            }
            top--;
            i++;
        }
        else if (strchr("+-*/", s[i])) {
            while (top != -1 && op[top] != '(' &&
                   prec(op[top]) >= prec(s[i]))
                generate();
            op[++top] = s[i++];
        }
        else {
            printf("Invalid character\n");
            return 1;
        }
    }

    while (top != -1) {
        if (op[top] == '(') {
            printf("Invalid expression\n");
            return 1;
        }
        generate();
    }

    if (vtop != 0) {
        printf("Invalid expression\n");
        return 1;
    }

    if (*lhs) printf("%s = %s\n", lhs, val[vtop]);
    else printf("Result = %s\n", val[vtop]);

    return 0;
}
