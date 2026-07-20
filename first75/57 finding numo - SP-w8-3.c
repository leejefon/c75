/* Finding Numo */

#include<stdio.h>
#include<time.h>

#define len 200

void find_index(int, int j[]);

// Find more than one position
int main()
{
	 int j[len]={0}, num, i;

	 srand((unsigned) time(NULL));
    system("cls");

	 printf("\n  ");
	 for(i=0;i<len;i++) {
       j[i] = rand()%100+1;
       printf("%4d", j[i]);
       if ((i+1)%20==0)
			 printf("\n  ");
	 }

	 printf("\nEnter the number that you wanna search: ");
    scanf("%d", &num);

	 find_index(num, j);

    getch();
    main();
    return 0;
}

void find_index(int num, int j[])
{
	 int i,found[len]={0}, count=0;

	 for(i=0;i<len;i++) {
		 if(num == j[i]) {
			 found[count]=i;
			 count++;
 		 }
	 }

	 if (count == 0)
		 printf("\nNo such number found!");
	 else {
       printf("\nThe number you are looking for is at ");
		 for(i=0;i<count;i++)
		    printf("%d, ", found[i]+1);
		 printf("\b\b position.");
	 }
}

/*
int find_index(int, int j[]);

// No repeating number
int main()
{
	 int num, i=0, j[len], k;

	 srand((unsigned) time(NULL));
    system("cls");
	 printf("\n  ");

	 while(i<len) {
		 j[i] = rand()%100;
		 for(k=0;k<i;k++)
			 if (j[i]==j[k]) goto keepgoing;

       printf("%4d", j[i]);
       if ((i+1)%20==0)
			 printf("\n  ");
       i++;

		 keepgoing:
			 continue;
    }

    printf("\nEnter the number that you wanna search (0-%d): ", len-1);
    scanf("%d", &num);

	 printf("\nThe number you are looking for is at %dth position.", find_index(num,j));

    getch();
    main();
    return 0;
}

int find_index(int num, int j[])
{
	 int i;

	 for(i=0;i<len;i++) {
		 if(num == j[i])
			 return i+1;
	 }
}
*/
