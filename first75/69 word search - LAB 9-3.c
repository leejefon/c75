#include<stdio.h>
#include<stdlib.h>

int first(char *a, char *b);
int mystrlen(char *a);

int main()
{
    char a[80], b[80];
    
    gets(a);
    gets(b);
    
    if (first(a,b)>0) printf("\nString B offset %d chars from beg of A", first(a,b));
    else printf("no b in a");
    
    getch();
    
    return 0;
}

int first(char *a, char *b)
{
    int i, j, ct;
    char *aptr=a, *bptr=b;
    
    for (i=0; i<mystrlen(a); i++) {
        *bptr=*b;
        for (j=0, ct=0; j<mystrlen(b); j++) {
            if (*(aptr+i+j) == *(bptr+j)) ct++;
            else break;
        }
        if (ct == mystrlen(b)) break;
    }
    
    if (i == mystrlen(a)) return -1;
    
    return i;
}

int mystrlen(char *a)
{
    int i;
    char *aptr=a;
    
    for (i=0; *(aptr+i)!='\0'; i++);
    
    return i;
}
