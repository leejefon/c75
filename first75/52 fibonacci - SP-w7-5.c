/* n'th term of Fibonacci series */

#include<stdio.h>

int main()
{
 	 int num;

    system("cls");

    printf("Enter a number: ");
    scanf("%d", &num);
    
    printf("%d", fibonacci(num));

    getch();
    main();
}

int fibonacci(int n)
{
 	  if (n==1) return 0;
	  else if (n==2) return 1;
	  
	  return fibonacci(n-1) + fibonacci(n-2);
}
