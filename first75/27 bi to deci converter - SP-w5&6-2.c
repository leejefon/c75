/* 4 digits Binary Converter */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a,b,c,d, deci;
    
    do{
    printf("enter a four-digit binary number: ");
    scanf("%1d%1d%1d%1d", &a, &b, &c, &d);
    } while ((a<0||a>1||b<0||b>1||c<0||c>1||d<0||d>1));
    
    deci = d + 2*c + 4*b + 8*a;
    
    printf("Binary %d%d%d%d equals decimal %d\n\n", a,b,c,d,deci);
    
    system("pause");
    return 0;
}
