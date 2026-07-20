/* Name of the game --- TBA */

/*************************
 *  Written by Jeff Lee  *
 *  2008/04/07 10:00 pm  *
 *************************/

#include<stdio.h>

int judge_over(char a[3][3])
{
 	 int row, col, i=49;

	 for (row=0;row<3;row++)
		  for (col=0;col<3;col++)
				if (i<=56 && a[row][col]!=i++) return 1;

	 return 0;
}

void print(char a[3][3])
{
     char col1[15]={218,196,196,196,194,196,196,196,194,196,196,196,191,0},
          col7[15]={192,196,196,196,193,196,196,196,193,196,196,196,217,0},
          col3[15]={195,196,196,196,197,196,196,196,197,196,196,196,180,0},
          col2[15]={179,' ',a[0][0],' ',179,' ',a[0][1],' ',179,' ',a[0][2],' ',179,0},
          col4[15]={179,' ',a[1][0],' ',179,' ',a[1][1],' ',179,' ',a[1][2],' ',179,0},
          col6[15]={179,' ',a[2][0],' ',179,' ',a[2][1],' ',179,' ',a[2][2],' ',179,0};
          
	  printf("\n\n\n       Sliding  Puzzle\n");
     printf("\n\t%s", col1);
     printf("\n\t%s", col2);
     printf("\n\t%s", col3);
     printf("\n\t%s", col4);
     printf("\n\t%s", col3);
     printf("\n\t%s", col6);
     printf("\n\t%s", col7);
}

int main()
{
	 int row, col, i;
	 char a[3][3]={' '}, direction, up='l', down='.', left=',', right='/';
	 
	 system("mode con cols=29 lines=20");
	 //system("mode con cp select=437");
	 system("title Sliding Puzzle");
	 system("cls");
	 srand(time(NULL));
	 
	 for (i=49;i<=56;i++) {
			row=rand()%3;
			col=rand()%3;
			if (a[row][col]=='\0') a[row][col]=i;
			else i--;
     }
     
	  i=0; row=0; col=0;
	  
	  //a[0][0]='1'; a[0][1]='2'; a[0][2]='3'; a[1][0]='4'; a[1][1]='5';
	  //a[1][2]='6'; a[2][0]='7'; a[2][1]=' '; a[2][2]='8'; row=2; col=1;
	  
	  do {
		  system("cls");
	 	  print(a);

     	  printf("\n\n\t %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
	 	  printf("\n\n\t  Moves: %2d", i);
	 	  
		  direction = getch();
		  
		  if (direction == up && row!=2) {
			  a[row][col]=a[row+1][col];
			  a[row+1][col]=' ';
			  row++; i++;
		  }
		  else if (direction == left && col!=2) {
			  a[row][col]=a[row][col+1];
			  a[row][col+1]=' ';
			  col++; i++;
		  }
		  else if (direction == down && row!=0) {
           a[row][col]=a[row-1][col];
			  a[row-1][col]=' ';
			  row--; i++;
		  }
		  else if (direction == right && col!=0) {
           a[row][col]=a[row][col-1];
			  a[row][col-1]=' ';
			  col--; i++;
		  }
		  else if (direction == 'o') exit(0);
		  else {
 		     printf("\n\n\a     Not a good move yo!");
			  getch();
		  }
		  
	  } while(judge_over(a));
	  
	  system("mode con lines=21");
     system("cls");
     a[2][2]='9';

	  print(a);
	  printf("\n\n\t %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
	  printf("\n\n\t  Moves: %2d", i);
	  printf("\n\n      Congradulations!!");

	  getch();
	  return 0;
}
