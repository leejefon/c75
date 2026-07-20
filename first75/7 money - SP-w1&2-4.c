/* Money */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x, quat, dim, nick, pen;
    
    printf("Enter and amount: ");
    scanf("%d", &x);
    
    quat = x/25;
    dim = (x%25)/10;
    nick = (x-quat*25-dim*10)/5;
    pen = x-quat*25-dim*10-nick*5;
    
    printf("\n");
    printf("%d quarter(s), %d dime(s), %d nickel(s), %d penny(ies)\n", quat, dim, nick, pen);
    printf("\n");
    
    system("pause");
    return 0;
}
