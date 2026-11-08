//INPUT CAN BE GIVEN WITH ANY NO:OF SPACE , int a = a + b, int a=a+b ALL OK
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char s[100], w[20];
    int i = 0, j;

    printf("Enter statement:\n");
    fgets(s, 100, stdin);

    while (s[i] != '\0')
    {
        if (isspace(s[i]))
            i++;

        else if (isalpha(s[i]))
        {
            j = 0;
            while (isalnum(s[i]))
                w[j++] = s[i++];

            w[j] = '\0';

            if (!strcmp(w,"int") || !strcmp(w,"float") ||
                !strcmp(w,"if") || !strcmp(w,"else") ||
                !strcmp(w,"while") || !strcmp(w,"return"))
                printf("%s : Keyword\n", w);
            else
                printf("%s : Identifier\n", w);
        }

        else if (isdigit(s[i]))
        {
            j = 0;
            while (isdigit(s[i]) || s[i] == '.')
                w[j++] = s[i++];

            w[j] = '\0';
            printf("%s : Number\n", w);
        }

        else if (strchr("+-*/=<>", s[i]))
            printf("%c : Operator\n", s[i++]);

        else if (strchr(";,(){}", s[i]))
            printf("%c : Separator\n", s[i++]);

        else
            i++;
    }

    return 0;
}
