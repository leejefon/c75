/* Any-Base to Any-Base convertor */

/*************************
 *  Written by Jeff Lee  *
 *  2008/02/22 02:00 pm  *
 *************************/ 
  
#include<stdio.h>
#include<stdlib.h>

int main()
{
    long long int num, deci=0, deci_ori, ob, obp, nb, nb_ori, rem;
    int ans, p=-1, np;
    
	 printf("\n\n\n\tAny number: ");
    scanf("%lld", &num);
    printf("\tThe base (2-10): ");
    scanf("%lld", &ob);
    printf("\tNew base (2-10 or 16): ");
    scanf("%lld", &nb);
    
    printf("\n\t   %lld (base %lld) = ", num, ob);
    
    for(obp=1;num>0;num/=10) {
       rem = (num%10)*obp;
       deci += rem;
       obp *= ob;
    }
    
    deci_ori = deci;
    nb_ori = nb;   // used instead of using power function
    
    for(;deci>0;p++) deci /= nb;   // count how many powers needed
    
    deci = deci_ori;   // this is the only place deci_ori is used...
    
    if (nb_ori == 16)
       printf("%X (base 16)\n", deci);   // it converts the deci to hexa right away!
    else {
       for(;p>0;p--) {
          nb = nb_ori;
          for(np=1;np<p;np++)
             nb *= nb_ori;   // if using math.h, can be written as pow(nb,np+1)
          ans = deci/nb;
          printf("%d", ans);
          deci %= nb;
       }
       printf("%lld (base %lld)\n", deci, nb_ori);   // prints the final remainder
    }
    
    printf("\n\tAgain?(Yes = 1, No = 0) ");
    scanf("%d", &p);
    if (p == 1) {
       system("cls");
       main();
    }
    else
    return 0;
}

/*
int main()
{
    long long int hex;
    
    printf("\n\n\t(Enter -1 to quit)\n\tNumber in hexa: ");
    scanf("%X", &hex);
    if (hex == -1)
       exit(0);
    printf("\n\t%X (base 16) = %u (base 10)\n", hex, hex);
    
    main();
    system("pause");
    return 0;
}
*/
