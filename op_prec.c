#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char stack[200],input[100];
    int top=-1,i,j,a,b,ip=0;
    char relation;
    printf("Enter input string:");
    fgets(input,sizeof(input),stdin);
    char symbols[]="+-*/()i$";
    char precedence[8][8]={
        {'>','>','<','<','<','>','<','>'},
        {'>','>','<','<','<','>','<','>'},
        {'>','>','>','>','<','>','<','>'},
        {'>','>','>','>','<','>','<','>'},
        {'<','<','<','<','<','=','<',' '},
        {'>','>','>','>',' ','>',' ','>'},
        {'>','>','>','>',' ','>',' ','>'},
        {'<','<','<','<','<',' ','<',' '}
    };
    for(i=0,j=0;input[i] && input[i]!='\n';i++)  
    {
        if(!isspace((unsigned char)input[i])){
            input[j++]=input[i];
        }
    }
    input[j]='\0';
    if(j==0)
    {
        printf("Rejected\n");
        return 0;
    }
    for(i=0;input[i];i++)
    {
        if(!strchr("+-*/i()",input[i]))
        {
            printf("Invalid characters\n");
            return 0;
        }
    }
    strcat(input,"$");
    stack[++top]='$';
    printf("STACK\t\tINPUT\n");
    printf("$\t\t%s\n",input);
    while(1)
    {
        i=top;
        while(i>=0 && stack[i]=='E')
        {
            i--;
        }
        for(a=0;symbols[a]!=stack[i];a++);
        for(b=0;symbols[b]!=input[ip];b++);
        if(a==8 || b==8){
            printf("Rejected\n");
            return 0;
        }
        relation=precedence[a][b];
        if(top==1 && stack[top]=='E' && stack[top-1]=='$' && input[ip]=='$')
        {
            printf("Accepted\n");
            return 0;
        }
        if(relation=='<'||relation=='=')
        {
            if(input[ip]=='$'){
                printf("Rejected\n");
                return 0;
            }
            stack[++top]=input[ip++];
        }
        else if(relation=='>')
        {
            if(stack[top]=='i')
            {
                stack[top]='E';
            }
            else if(top>=2 && stack[top]==')' && stack[top-1]=='E' && 
                stack[top-2]=='(')
            {
                top-=2;
                stack[top]='E';
            }
            else if(top>=2 && stack[top]=='E' && stack[top-2]=='E' && 
                strchr("+-*/",stack[top-1]))
            {
                top-=2;
                stack[top]='E';
            }
            else
            {
                printf("Rejected\n");
                return 0;
            }
        }
        else
        {
            printf("Rejected\n");
            return 0;
        }
        for(i=0;i<=top;i++)
        {
            printf("%c",stack[i]);
        }
        printf("\t\t%s\n",input+ip);
    }
    return 0;
    
}