/* Sorting characters using Insertion Sort*/

#include<stdio.h>

void getText(char a[], int);
void insertionsort(char a[], int);

int main()
{
	 int n=10;
	 char a[n];

    printf("Enter some garbage: ");
    getText(a, n);
    insertionsort(a, n);
}

void getText(char a[], int n)
{
	  int i;
	  
	  for(i=0;i<n;i++)
		  scanf("%c", &a[i]);
}

void insertionsort(char a[], int n)
{
	  int i, j;
	  char temp;
	  
	  for(i=1;i<n;i++) {
		  temp=a[i];
		  j=i-1;
		  while ((j>=0) && (a[j]>temp)) {
			  a[j+1]=a[j];
			  j--;
		  }
		  a[j+1]=temp;
	  }
	  
	  for(i=0;i<n;i++)
		  printf("%c", a[i]);

	  getch();
}
