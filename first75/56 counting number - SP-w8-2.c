/* Counting Intergetrs */

#include<stdio.h>

int main()
{
	 int a[10]={0}, num, i;

    system("cls");

    printf("\n\n\tEnter intergers: ");
    scanf("%d", &num);
    
	 while(num>0) {
		 i=num%10;
		 a[i]++;
		 num/=10;
	 }
	 
	 printf("\n\n\tNumbers\t Times\n");
	 printf("\t--------------\n");
	 for (i=0;i<10;i++) {
		 if (a[i]>0)
	 	 	 printf("\t%4d\t%4d\n", i, a[i]);
	 }
	 
    getch();
    main();
    return 0;
}
