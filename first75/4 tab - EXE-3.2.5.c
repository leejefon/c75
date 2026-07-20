/* Tabs */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, c, d, e;
    float b;
    
    printf("Enter item number: ");
    scanf("%d", &a);
    printf("Enter item price: ");
    scanf("%f", &b);
    printf("Enter date(mm/dd/yy): ");
    scanf("%d/%d/%d", &c, &d, &e);
    
    printf("Item\t\tItem price\t\tDate\n");
    printf("%d\t\t$ %.2f\t\t\t%d/%d/%d\n", a, b, c, d, e);
    
    system("pause");
    return 0;
}
