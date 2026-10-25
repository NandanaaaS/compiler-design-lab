#include <stdio.h>
#include <ctype.h>

char s[200];
int i = 0, error = 0;

void E();
void EP();
void T();
void TP();
void F();

void skip()
{
    while (isspace((unsigned char)s[i]))
        i++;
}

void E()
{
    if (error) return;
    printf("E -> T E'\n");
    T();
    EP();
}

void EP()
{
    if (error) return;
    skip();

    if (s[i] == '+' || s[i] == '-')
    {
        printf("E' -> %c T E'\n", s[i++]);
        T();
        EP();
    }
    else
        printf("E' -> #\n");
}

void T()
{
    if (error) return;
    printf("T -> F T'\n");
    F();
    TP();
}

void TP()
{
    if (error) return;
    skip();

    if (s[i] == '*' || s[i] == '/')
    {
        printf("T' -> %c F T'\n", s[i++]);
        F();
        TP();
    }
    else
        printf("T' -> #\n");
}

void F()
{
    if (error) return;
    skip();

    if (s[i] == '(')
    {
        printf("F -> ( E )\n");
        i++;
        E();
        skip();

        if (s[i] == ')')
            i++;
        else
            error = 1;
    }
    else if (isalnum((unsigned char)s[i]))
    {
        printf("F -> id\n");

        while (isalnum((unsigned char)s[i]))
            i++;
    }
    else
        error = 1;
}

int main()
{
    printf("Enter expression: ");
    if (!fgets(s, sizeof(s), stdin))
        return 0;

    E();
    skip();

    if (s[i] == '$')
    {
        i++;
        skip();
    }

    if (!error && s[i] == '\0')
        printf("\nParsing successful!\n");
    else
        printf("\nInvalid expression!\n");

    return 0;
}
