/* Largest sum of row or column */

#include<stdio.h>
#include<time.h>
#define row 16
#define col 16

int largest(int array[row][col]);
void result(int, int, int);

int main()
{
	 int array[row][col], i, j;
	 
	 srand((unsigned) time(NULL));
	 
	 printf("\n\n      |");
	 for(i=1;i<=col;i++)
		 printf("%4d", i);
		 
	 printf("\n   ");
	 for(i=0;i<(col+1)*4;i++) {
		 if (i==3) printf("+");
		 else printf("-");
	 }
		 
	 for(i=0;i<row;i++) {
		 printf("\n   %2d |", i+1);
		 for(j=0;j<col;j++) {
			 array[i][j]=rand()%100+1;
			 printf("%4d", array[i][j]);
		 }
	 }

	 largest(array);
}

int largest(int array[row][col])
{
	 int sum, larger_sum=0, i, j, k, cor;
	 
	 //sum row
	 for(i=0;i<row;i++) {
		 sum=0;
		 for(j=0;j<col;j++)
		    sum += array[i][j];
		 if (sum>larger_sum) {
		    larger_sum=sum;
		    k=i+1;
		    cor=1;
		 }
	 }
	 
	 //sum col
	 for(i=0;i<col;i++) {
		 sum=0;
		 for(j=0;j<row;j++)
		    sum += array[j][i];
		 if (sum>larger_sum) {
		 	 larger_sum=sum;
		 	 k=i+1;
		 	 cor=2;
		 }
	 }
	 
	 result(larger_sum, k, cor);
}

void result(int sum, int k, int cor)
{
    printf("\n\n\n   The largerst sum is ");
	 if(cor==1) printf("%d in row %d", sum, k);
	 else printf("%d in col %d", sum, k);

	 getch();
	 system("cls");
	 main();
}
