/* Rounding Numbers */

#include<stdio.h>
#include<stdlib.h>

int rounding(double a)
{
 	 if (a>0) return a+0.5;
    else if (a<0) return a-0.5;
}

int main()
{
    double num;
	 
    printf("Enter a number: ");
    scanf("%lf", &num);

	 if(rounding(num)>num) printf("It rounds up to ");
	 else if(rounding(num)<num) printf("It rounds down to ");
	 else printf("It's just ");
	 
	 printf("%d", rounding(num));

    getch();
    return 0;
}
