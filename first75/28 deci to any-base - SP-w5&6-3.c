/* Decimal to Any-Base converter */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int base, base_ori, deci, deci_ori, p=-1, np, ans;
    
    printf("Enter a decimal number: ");
    scanf("%d", &deci);
    printf("Enter a base between 2-9: ");
    scanf("%d", &base);
    
    deci_ori = deci;
    base_ori = base;
    
    for(;deci>0;p++)
       deci/=base;
       
    deci = deci_ori;
    
    printf("%d in base %d is ", deci, base);
    
    for(;p>0;p--) {
       base = base_ori;
       for(np=1;np<p;np++)
          base *= base_ori;
       ans = deci/base;
       printf("%d", ans);
       deci %= base;
    }
    
    printf("%d\n\n", deci);
    
    main();
    system("pause");
    return 0;
}
