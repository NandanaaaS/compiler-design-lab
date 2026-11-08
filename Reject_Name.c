%{
#include <stdio.h>
%}

%%
.*Nand.*    { printf("Rejected\n"); }
.*          { printf("Accepted\n"); }
%%

int yywrap() { return 1; }

int main()
{
    printf("Enter string: ");
    yylex();
    return 0;
}
