/* Binary Search */

#include<stdio.h>
#include<time.h>
#define SIZE 100

int binary_search(int array[], int);

int main()
{
	 int array[SIZE], i, num;
	 
	 printf("\n  ");
	 for(i=0;i<SIZE;i++) {
		 array[i] = i*2+i/2;
		 printf("%5d", array[i]);
		 if ((i+1)%10==0) printf("\n  ");
	 }

	 printf("\n\n\tWhat number are you looking for? ");
	 scanf("%d", &num);
	 
	 if (binary_search(array, num) == -1)
		 printf("\n\tNo such number in the list!!");
	 else
	    printf("\n\tValue %d is stored in array[%d]", num, binary_search(array, num));
	 
    getch();
    system("cls");
    main();
    return 0;
}

int binary_search(int array[], int num)
{
	 int low=0, high=SIZE-1, mid;

	 while(low!=high-1) {
		 mid=(low+high)/2;
		 if(array[mid]>num) high=mid;
		 else if (array[mid]<num) low=mid;
		 else return mid;
	 }
	 return -1;
}
