/* Temperture Convert */

#include<stdio.h>
#include<stdlib.h>

double F2C(double F)
{    
    return 5/9.*(F-32);
}

int main()
{
    double F;
    char kk=248;
	 
	 system("cls");

    printf("Enter temp F: ");
    scanf("%lf", &F);
    
    printf("\nTemp %.2lf %cF in C is %.2lf %cC.", F, kk, F2C(F), kk); 



    getch();
    //system("pause");
    return 0;
}
