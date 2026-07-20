/* Dynamic random number */

#include<stdio.h>

int main()
{
	 int *num, howmany, i, start, end;
	 
	 srand(time(NULL));
	 
	 printf("How many humbers?");
	 scanf("%d", &howmany);
	 printf("From where to where?");
	 scanf("%d %d", &start, &end);
	 
	 num = malloc(howmany*sizeof(int));

	 printf("The %d random numbers are: ", howmany);
	 
	 for (i=0;i<howmany;i++) {
		  *(num+i)=rand()%(end-start)+start;
		  printf("%d ", *(num+i));
    }

    getch();
    return 0;
}
