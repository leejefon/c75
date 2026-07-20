/* 15 Sliding Puzzle */

/*************************
 *  Written by Jeff Lee  *
 *  2008/04/08 02:00 pm  *
 *************************/

#include<stdio.h>

void randomize(char a[4][4])
{
     enum {up,left,down,right};
     int direction, row=3, col=3, counter=0;

     do {
        direction = rand()%4;

        if (direction == up && row!=3) {
		    a[row][col]=a[row+1][col];
		    a[row+1][col]=' ';
		    row++;
		  }
		  else if (direction == left && col!=3) {
			  a[row][col]=a[row][col+1];
			  a[row][col+1]=' ';
			  col++;
		  }
		  else if (direction == down && row!=0) {
           a[row][col]=a[row-1][col];
			  a[row-1][col]=' ';
			  row--;
		  }
		  else if (direction == right && col!=0) {
           a[row][col]=a[row][col-1];
			  a[row][col-1]=' ';
			  col--;
		  }
		  else continue;

        if (a[0][0]==' ') counter++;

     } while (counter<20);
}

int judge_over(char a[4][4])
{
 	 int row, col, i=65;

	 for (row=0;row<4;row++)
		  for (col=0;col<4;col++)
				if (i<80 && a[row][col]!=i++) return 1;

	 return 0;
}

void print(char a[4][4])
{
     char col1[19]={218,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,191,0},
          col9[19]={192,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,217,0},
          col3[19]={195,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,180,0},
          col2[19]={179,' ',a[0][0],' ',179,' ',a[0][1],' ',179,' ',a[0][2],' ',179,' ',a[0][3],' ',179,0},
          col4[19]={179,' ',a[1][0],' ',179,' ',a[1][1],' ',179,' ',a[1][2],' ',179,' ',a[1][3],' ',179,0},
          col6[19]={179,' ',a[2][0],' ',179,' ',a[2][1],' ',179,' ',a[2][2],' ',179,' ',a[2][3],' ',179,0},
          col8[19]={179,' ',a[3][0],' ',179,' ',a[3][1],' ',179,' ',a[3][2],' ',179,' ',a[3][3],' ',179,0};
          
	  printf("\n\n\n\t15 Sliding Puzzle\n");
     printf("\n\t%s", col1);
     printf("\n\t%s", col2);
     printf("\n\t%s", col3);
     printf("\n\t%s", col4);
     printf("\n\t%s", col3);
     printf("\n\t%s", col6);
     printf("\n\t%s", col3);
     printf("\n\t%s", col8);
     printf("\n\t%s", col9);
}

int main()
{
	 int row=0, col=0, i=0;
	 char a[4][4], direction, up='l', down='.', left=',', right='/';
	 
	 system("mode con cols=33 lines=22");
	 system("title 15 Sliding Puzzle Game");
    //system("mode con cp select=437");
	 system("cls");
	 srand(time(NULL));

    a[0][0]='A'; a[0][1]='B'; a[0][2]='C'; a[0][3]='D'; a[1][0]='E'; a[1][1]='F';
	 a[1][2]='G'; a[1][3]='H'; a[2][0]='I'; a[2][1]='J'; a[2][2]='K'; a[2][3]='L';
	 a[3][0]='M'; a[3][1]='N'; a[3][2]='O'; a[3][3]=' ';

    randomize(a);

	 //a[0][0]='A'; a[0][1]='B'; a[0][2]='C'; a[0][3]='D'; a[1][0]='E'; a[1][1]='F';
	 //a[1][2]='G'; a[1][3]='H'; a[2][0]='I'; a[2][1]='J'; a[2][2]='K'; a[2][3]='L';
	 //a[3][0]='M'; a[3][1]='N'; a[3][2]=' '; a[3][3]='O'; row=3; col=2;

	 do {
	    system("cls");
	    print(a);

       printf("\n\n\t   %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
	    printf("\n\n\t    Moves: %2d", i);
	 	  
	    direction = getch();
		  
	    if (direction == up && row!=3) {
		    a[row][col]=a[row+1][col];
		    a[row+1][col]=' ';
		    row++; i++;
		 }
		 else if (direction == left && col!=3) {
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
          printf("\n\n\a       Not a good move yo!");
          getch();
       }

    } while(judge_over(a));

    system("mode con lines=23");
    system("cls");
    a[3][3]='P';

    print(a);
    printf("\n\n\t %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
    printf("\n\n\t    Moves:%3d", i);
    printf("\n\n        Congradulations!!");

    getch();
    return 0;
}
