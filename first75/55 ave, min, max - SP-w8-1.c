/* Ave, Min, Max */

#include<stdio.h>
#include<time.h>

int main()
{
	 int a[10], ave, min=100, max=0, i, sum=0;

    system("cls");

	 srand((unsigned) time(NULL));

	 printf("\n\n\ta[10]={");
	 for(i=0;i<10;i++) {
		 a[i] = rand()%100+1;
		 printf("%d, ", a[i]);
		 sum += a[i];
		 if (a[i]>max) max = a[i];
		 else if (a[i]<min) min=a[i];
		 else continue;
	 }
    printf("\b\b}\n\n\n\tAve: %d\t\tMax: %d\t\tMin: %d", sum/10, max, min);
    
    getch();
    main();
    return 0;
}
