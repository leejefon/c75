/* Number of digits */

#include<stdio.h>
#include<stdlib.h>

int number_of_digits(int number)
{
 	 int i=0;
 	 
 	 if (number<=0) return -1;
 	 
 	 for(;number>0;i++) number /= 10;

    return i;
	 
}

int main()
{
    int num, digit;
	 
	 system("cls");

    printf("Enter a number: ");
    scanf("%d", &num);
    
    digit = number_of_digits(num);
	 
	 if (digit == -1) printf("\n\nSorry, wrong number...");
	 else printf("\n\nThe number of digit in %d is %d", num, digit);

    getch();
    main();
    //system("pause");
    return 0;
}
