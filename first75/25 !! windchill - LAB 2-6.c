/* Windchill Calculator */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    float temper, velo, fah, cel, wc;
    char  ature, city, kk=248;
    
    printf("(Enter -1 to quit)\n");
    printf("Enter the temperature (ex: 25c or 60f): ");
    scanf("%f%c", &temper, &ature);
    if (temper == -1 && ature == '\n')
       exit(0);
    printf("Enter the wind velocity (ex: 30k or 25m): ");
    scanf("%f%c", &velo, &city);
    
    if (ature == 'f' && city =='k')
       velo /= 1.609344;
    else if (ature == 'c' && city == 'm')
       temper = 9/5*temper+32;
    else if (ature =='c' && city =='k') {
       velo /= 1.609344;
       temper = 9/5*temper+32;
    }
    else if (ature =='f' && city =='m');
    else {
       printf("\nPlease enter something valid.\n\n");
       main();
    }
    
    wc = 35.74 + 0.6215*temper - 35.75*pow(velo,0.16) + 0.4275*temper*pow(velo,0.16);
    
    printf("\n\tWindchill is %.2f %cF or %.2f %cC\n\n", wc, kk, 5*(wc-32)/9, kk); 
    
    main();
    system("pause");
    return 0;
}
