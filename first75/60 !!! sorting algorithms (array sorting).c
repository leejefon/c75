/* Different ways of sorting number */

/***********************  **************************
 * Written by Jeff Lee *  * Selection Sort Correct *
 * 2008/03/06 10:30 am *  *   2008/03/07 02:00pm   *
 ***********************  **************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define length 10000

void selectionSort(int *in); //
void insertionSort(int *in); //
void bubbleSort(int *in); //
void quickSort(int number[], int, int); //
void swap(int *a, int *b); // for quicksort
void printout(int *in); //

int main()
{
  	 int array[length];
  	 int i, choice;
  	 clock_t start, finish;

	 srand(time(NULL));
	 printf("\n");

	 for(i=0;i<length;i++) {
	    array[i]=rand()%100+1;
	    printf("%4d",array[i]);
    	 if(i%20==19)
          printf("\n");
    }

    printf("\n\n\
            (1)Selection sort\n\
            (2)Insertion sort\n\
            (3)Bubble sort\n\
            (4)Quick sort\n\
            (5)Quit\n");
    printf("\nEnter your choise:");
    scanf("%d",&choice);

    start = clock();

    switch(choice){
       case  1: selectionSort(array); 	   printout(array); break;
   	 case  2: insertionSort(array); 	   printout(array); break;
   	 case  3: bubbleSort(array);    	   printout(array); break;
   	 case  4: quickSort(array,0,length-1); printout(array); break;
   	 default: exit(0);
    }

    finish = clock();
    printf("\n\nTime taken: %.3f sec\n", (double)(finish - start)/CLOCKS_PER_SEC);

    getch();
    return 0;
}

void selectionSort(int *in)
{
  	  int i, j, min, temp;

	  for(i=0;i<(length-1);i++){
		  min=i;
		  for(j=i+1;j<length;j++){
           if(in[j]<in[min])
        	     min = j;
		  }
    	  temp = in[i];
    	  in[i] = in[min];
    	  in[min] = temp;

		  //printout(in);
        //printf("\n");
	  }
}

void insertionSort(int *in)
{
  	  int i,j,temp;

  	  for(i=1;i<length;i++){
 	     temp = in[i];
		  j=i-1;
    	  while((j>=0) && (in[j] > temp)){
           in[j+1] = in[j];
      	  j--;
		  }
    	  in[j+1] = temp;
    	  
	     //printout(in);
		  //printf("\n");
 	  }
}


void bubbleSort(int *in)
{
  	  int i, j, temp;

	  for(i=0;i<length;i++){
        for(j=0;j<length-i;j++)
           if(in[j]>in[j+1]){
        	     temp = in[j];
        		  in[j] = in[j+1];
        		  in[j+1] = temp;
    		  }
	     
	     //printout(in);
		  //printf("\n");
	  }
}

void quickSort(int number[], int left, int right)
{
  	  int i, j, s;

  	  if(left < right) {
        s = number[left];
        i = left;
    	  j = right + 1;

        while(1) {
	        while(i + 1 < length && number[++i] < s);
           while(j -1 > -1 && number[--j] > s);
			  if(i >= j) break;
           swap(&number[i], &number[j]);
        }

        number[left] = number[j];
        number[j] = s;

        //printout(number);
	     //printf("\n");

        quickSort(number, left, j-1);
        quickSort(number, j+1, right);
     }
}

void swap(int *a, int *b)
{
 	  int t=*a; *a=*b; *b=t;
}

void printout(int *in)
{
  	  int i;

	  for(i=0;i<length;i++){
        printf("%4d",in[i]);
    	  if(i%20==19)
           printf("\n");
	  }
}
