/* Sliding Puzzle Games */

/*************************  ***********************  ***********************
 *  Written by Jeff Lee  *  *   Program Organize  *  *       Ranking       *
 *  2008/04/08 02:30 pm  *  * 2008/04/23 12:00 am *  * 2008/04/28 11:00 am *
 *************************  ***********************  ***********************/

#include<stdio.h>
#include<windows.h>

struct record{
   char player[5];
   int nmoves;
} rankings[15];

FILE *rankingfile;
char filename[20]="text//rank.game";
char up='l', down='.', left=',', right='/';
int row, col, moves;

void getrank()
{
     int i;
     char cmd[30]="attrib ";

     if ((rankingfile=fopen(filename,"r")) == NULL) {
        rankingfile=fopen(filename,"w");
        for (i=0;i<15;i++) {
            fprintf(rankingfile,"AAAA\n");
            fprintf(rankingfile,"%d\n", (i+1)*50);
        }
        fclose(rankingfile);
        rankingfile=fopen(filename,"r");

        strcat(cmd,filename);
        strcat(cmd," +H");
        system(cmd);
     }

     for (i=0;i<15;i++) {
         fscanf(rankingfile,"%[^\n]", rankings[i].player);
         fgetc(rankingfile);
         fscanf(rankingfile,"%d", &rankings[i].nmoves);
         fgetc(rankingfile);  // to get the '\n' after the int
     }

     fclose(rankingfile);
}

void ranking(char choice)
{
     int i;
     struct record temp;

     system("mode con cols=28 lines=22");

     printf("\n\n       Your Move: %3d\n", moves);

     if (choice == 'a') {
        if (moves < rankings[4].nmoves) {
           rankings[4].nmoves=moves;
           printf("\n      Congradulations!\n\n     You are in Top 5!!\n");
           printf("\n    Name (5 chars): ");
           gets(rankings[4].player);
           for (i=4;i>0;i--)
               if (rankings[i].nmoves < rankings[i-1].nmoves) {
                  temp=rankings[i];
                  rankings[i]=rankings[i-1];
                  rankings[i-1]=temp;
               }
        }
        else printf("\n\n         Too Bad...\n\n  You are not in Top 5s...\n");
        printf("\n\n      3x3 Top 5 Scores\n\n");
        printf("     Rank   Name  Moves\n");
        printf("    --------------------\n");
        for (i=0;i<5;i++) printf("      %d    %5s  %4d\n", i+1, rankings[i].player, rankings[i].nmoves);
     }
     else if (choice == 'b') {
        if (moves < rankings[9].nmoves) {
           rankings[9].nmoves=moves;
           printf("\n      Congradulations!\n\n     You are in Top 5!!\n");
           printf("\n    Name (5 chars): ");
           gets(rankings[9].player);
           for (i=9;i>5;i--)
               if (rankings[i].nmoves < rankings[i-1].nmoves) {
                  temp=rankings[i];
                  rankings[i]=rankings[i-1];
                  rankings[i-1]=temp;
               }
        }
        else printf("\n\n         Too Bad...\n\n  You are not in Top 5s...\n");
        printf("\n\n      4x4 Top 5 Scores\n\n");
        printf("     Rank   Name  Moves\n");
        printf("    --------------------\n");
        for (i=5;i<10;i++) printf("      %d    %5s  %4d\n", i-4, rankings[i].player, rankings[i].nmoves);
     }
     else if (choice == 'c') {
        if (moves < rankings[14].nmoves) {
           rankings[14].nmoves=moves;
           printf("\n      Congradulations!\n\n     You are in Top 5!!\n");
           printf("\n    Name (5 chars): ");
           gets(rankings[14].player);
           for (i=14;i>10;i--)
               if (rankings[i].nmoves < rankings[i-1].nmoves) {
                  temp=rankings[i];
                  rankings[i]=rankings[i-1];
                  rankings[i-1]=temp;
               }
        }
        else printf("\n\n         Too Bad...\n\n  You are not in Top 5s...\n");
        printf("\n\n      5x5 Top 5 Scores\n\n");
        printf("     Rank   Name  Moves\n");
        printf("    --------------------\n");
        for (i=10;i<15;i++) printf("      %d    %5s  %4d\n", i-9, rankings[i].player, rankings[i].nmoves);
     }

     rankingfile=fopen(filename,"w");

     for (i=0;i<15;i++) {
         fprintf(rankingfile,"%s\n", rankings[i].player);
         fprintf(rankingfile,"%d\n", rankings[i].nmoves);
     }

     fclose(rankingfile);
}

void randomize(int size, char a[][size])
{
     enum {up,left,down,right};
     int direction, row=size-1, col=size-1, counter=0;

     do {
        direction = rand()%4;

        if (direction == up && row!=size-1) {
           a[row][col]=a[row+1][col];
           a[row+1][col]=' ';
           row++;
        }
        else if (direction == left && col!=size-1) {
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

     } while (counter<50);
}

void move(int size, char a[][size], char direction)
{
     if (direction == up && row!=size-1) {
        a[row][col]=a[row+1][col];
        a[row+1][col]=' ';
        row++; moves++;
     }
     else if (direction == left && col!=size-1) {
        a[row][col]=a[row][col+1];
        a[row][col+1]=' ';
        col++; moves++;
     }
     else if (direction == down && row!=0) {
        a[row][col]=a[row-1][col];
        a[row-1][col]=' ';
        row--; moves++;
     }
     else if (direction == right && col!=0) {
        a[row][col]=a[row][col-1];
        a[row][col-1]=' ';
        col--; moves++;
     }
     else if (direction == 'o') exit(0);
     else {
        if (size==3) printf("\n\n     Not a good move yo!");
        if (size==4) printf("\n\n       Not a good move yo!");
        if (size==5) printf("\n\n         Not a good move yo!");
        getch();
     }
}

int judge_over(int size, char a[size][size])
{
    int row, col, start, end;

    if (size==3) {start=49; end=57;}
    if (size==4) {start=65; end=80;}
    if (size==5) {start=65; end=89;}

    for (row=0;row<size;row++)
        for (col=0;col<size;col++)
            if (start<end && a[row][col]!=start++)
               return 1;

    return 0;
}

/* 3x3 Starts*/
void print_3x3(char a[3][3])
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

void game_3x3()
{
     char a[3][3]={"123","456","78 "};

     system("mode con cols=29 lines=20");
     system("title Sliding Puzzle");

     randomize(3,a);

     //a[0][0]='1'; a[0][1]='2'; a[0][2]='3'; a[1][0]='4'; a[1][1]='5';
     //a[1][2]='6'; a[2][0]='7'; a[2][1]=' '; a[2][2]='8'; row=2; col=1;

     do {
        system("cls");
        print_3x3(a);

        printf("\n\n\t %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
        printf("\n\n\t  Moves: %2d", moves);

        move(3,a,getch());

     } while (judge_over(3,a));

     system("mode con lines=21");
     a[2][2]='9';

     print_3x3(a);
     printf("\n\n\t %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
     printf("\n\n\t  Moves: %2d", moves);
     printf("\n\n      Congradulations!!");
}

/* 4x4 Starts */
void print_4x4(char a[4][4])
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

void game_4x4()
{
     char a[4][4]={"ABCD","EFGH","IJKL","MNO "};

     system("mode con cols=33 lines=22");
     system("title 15 Sliding Puzzle");

     randomize(4,a);

     //a[0][0]='A'; a[0][1]='B'; a[0][2]='C'; a[0][3]='D'; a[1][0]='E'; a[1][1]='F';
     //a[1][2]='G'; a[1][3]='H'; a[2][0]='I'; a[2][1]='J'; a[2][2]='K'; a[2][3]='L';
     //a[3][0]='M'; a[3][1]='N'; a[3][2]=' '; a[3][3]='O'; row=3; col=2;

     do {
        system("cls");
        print_4x4(a);

        printf("\n\n\t   %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
        printf("\n\n\t    Moves: %d", moves);

        move(4,a,getch());

     } while (judge_over(4,a));

     system("mode con lines=23");
     a[3][3]='P';

     print_4x4(a);
     printf("\n\n\t   %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
     printf("\n\n\t    Moves: %d", moves);
     printf("\n\n        Congradulations!!");
}

/* 5x5 Starts */
void print_5x5(char a[5][5])
{
     char col1[23]={218,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,194,196,196,196,191,0},
          col3[23]={195,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,197,196,196,196,180,0},
          col8[23]={192,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,193,196,196,196,217,0},
          col2[23]={179,' ',a[0][0],' ',179,' ',a[0][1],' ',179,' ',a[0][2],' ',179,' ',a[0][3],' ',179,' ',a[0][4],' ',179,0},
          col4[23]={179,' ',a[1][0],' ',179,' ',a[1][1],' ',179,' ',a[1][2],' ',179,' ',a[1][3],' ',179,' ',a[1][4],' ',179,0},
          col5[23]={179,' ',a[2][0],' ',179,' ',a[2][1],' ',179,' ',a[2][2],' ',179,' ',a[2][3],' ',179,' ',a[2][4],' ',179,0},
          col6[23]={179,' ',a[3][0],' ',179,' ',a[3][1],' ',179,' ',a[3][2],' ',179,' ',a[3][3],' ',179,' ',a[3][4],' ',179,0},
          col7[23]={179,' ',a[4][0],' ',179,' ',a[4][1],' ',179,' ',a[4][2],' ',179,' ',a[4][3],' ',179,' ',a[4][4],' ',179,0};

     printf("\n\n\n\t  24 Sliding Puzzle\n");
     printf("\n\t%s", col1);
     printf("\n\t%s", col2);
     printf("\n\t%s", col3);
     printf("\n\t%s", col4);
     printf("\n\t%s", col3);
     printf("\n\t%s", col5);
     printf("\n\t%s", col3);
     printf("\n\t%s", col6);
     printf("\n\t%s", col3);
     printf("\n\t%s", col7);
     printf("\n\t%s", col8);
}

void game_5x5()
{
     char a[5][5]={"ABCDE","FGHIJ","KLMNO","PQRST","UVWX "}, direction;

     system("mode con cols=37 lines=24");
     system("title 24 Sliding Puzzle");

     randomize(5,a);

     //a[0][0]='A'; a[0][1]='B'; a[0][2]='C'; a[0][3]='D'; a[0][4]='E'; a[1][0]='F';
     //a[1][1]='G'; a[1][2]='H'; a[1][3]='I'; a[1][4]='J'; a[2][0]='K'; a[2][1]='L';
     //a[2][2]='M'; a[2][3]='N'; a[2][4]='O'; a[3][0]='P'; a[3][1]='Q'; a[3][2]='R';
     //a[3][3]='S'; a[3][4]='T'; a[4][0]='U'; a[4][1]='V'; a[4][2]='W'; a[4][3]=' ';
     //a[4][4]='X'; row=4; col=3;

     do {
        system("cls");
        print_5x5(a);

        printf("\n\n\t     %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
        printf("\n\n\t      Moves: %d", moves);

        move(5,a,getch());

     } while (judge_over(5,a));

     system("mode con lines=25");
     a[4][4]='Y';

     print_5x5(a);
     printf("\n\n\t     %c%c %c%c %c%c %c%c", up, 24, down, 25, right, 26, left, 27);
     printf("\n\n\t      Moves: %d", moves);
     printf("\n\n          Congradulations!!");
}

void hide_cursor()
{
     HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO cci;
     cci.bVisible = FALSE;
     cci.dwSize = 25;
     SetConsoleCursorInfo(hcon,&cci);
}

int main()
{
    char choice;

    //system("mode con cp select=437");
    srand(time(NULL));
    hide_cursor();

    do {
       system("mode con cols=20 lines=11");
       system("title Games");
       system("cls");

       row=col=moves=0;
       printf("\n\n\n       A. 3x3");
       printf("\n\n       B. 4x4");
       printf("\n\n       C. 5x5");

       choice=getch();

       getrank();

       if (choice=='a') game_3x3();
       else if (choice=='b') game_4x4();
       else if (choice=='c') game_5x5();
       else if (choice=='o') exit(0);
       else continue;

       getch(); ranking(choice);

    } while (getch());

    return 0;
}
