                
                  /**************************************************************
                   *                                                            *
                   *                      ~Virus 3  v1.0~                       *
                   *   Original Game link:                                      *
                   *   http://www.arcadetown.com/virus3/gameonline.asp          *
                   *                                                            *
                   **************************************************************/

                  /**************************************************************
                   *                                                            *
                   *                    University of Toronto                   *
                   *                APS106 - Computer Fundamental               *
                   *                     Project 2008 Spring                    *
                   *                                                            *
                   *     Professor: Prof. Markus Bussman                        *
                   *                                                            *
                   *     Student  : Jeff  Chieh-Feng Lee   995862883            *
                   *                                                            *
                   **************************************************************/

                  /**************************************************************
                   *                                                            *
                   *   Game Completion Record:                                  *
                   *                                                            *
                   *   Main menu + Generate boards (input&random) == 08/03/02   *
                   *   Virus 3 Play (part) + Most small fuctions  == 08/03/20   *
                   *   Virus 3 Play (done) + Organize code        == 08/03/21   *
                   *   Computer Play (done)  + output logfile     == 08/03/22   *
                   *   Appreance Edit (color & style)             == 08/03/23   *
                   *   Computer Play (improved) (max to min)      == 08/04/05   *
                   *   Computer Play (improved) (saving numbers)  == 08/04/06   *
                   *                                                            *
                   *                         DONE!!!!                           *
                   *                                                            *
                   **************************************************************/

// Header Files
#include<stdio.h>
#include<windows.h>

typedef enum {NO,YES} bool;

enum {Black, d_blue, d_green,   cyan,
      d_red, purple,   brown, l_gray,
       gray,   blue,   green, l_blue,
        red, l_purp,  yellow,  white};

enum {BOARDSIZEMAX=24,BOARDSIZEMIN=6,COLORMAX=9,COLORMIN=4};

#define maxboard 100

// Major Functions
void tutorial();
void game_initialize(int);
void play(char a[][], int size[], char);
void computer_play(char a[][], int size[], char);

// Helper Functions
bool judge_over(char a[][], int size[]);
bool check_same(char a[][], char a_saved[][], int size[]);
bool check_filename(char filename[]);
int computer_thinking(char a[][], int size[]);
int number_color(int);

// Other functions
void board_print(char a[][], int size[]);
void horizontal_line(int, int);
void again(void);
void goodbye(void);
void credit(void);
void setcolor(int);
void hide_cursor(void);

// Global declarations for commonly used variables
int rct, cct;
FILE *logfile;

int main()
{
    char choice;

    system("COLOR 0f");  // sets the background to be black
    system("TITLE ~~~~VIRUS 3~~~~");  // changes the title
    system("mode con lines=50 cols=90");  // sets the size of the window
    srand(time(NULL));

    do {
       system("cls");
       printf("\n\n\n\n\t\t\t\t   Welcome to Virus 3!!");
       horizontal_line(1,50);

       // The main menu of the game
       setcolor(white);
       printf("\n\n\t\t\t\t     1. Start Virus");
       printf("\n\n\t\t\t\t     2. Computer Play");
       printf("\n\n\t\t\t\t     3. Tutorial");
       printf("\n\n\t\t\t\t     4. Exit\n");
       setcolor(cyan); printf("\n\n\t\t\t\t     (0. Credit by...)\n");
       setcolor(white); printf("\n\n\t\t\t\t     Select: ");
       choice = getche();
                 
       switch (choice) {
          case '0': credit(); break;
          case '1': case '2': game_initialize((int) choice-48); break;
          case '3': system("cls"); tutorial(); break;
          default: goodbye(); break;
       }

    } while(1);

    return 0;
}

void tutorial()
{
     int size[3]={7,7,2}, i=0;
         // size initiation for the example board, size[0] == row, size[1] == col, size[2] == number of choices,
     char example[maxboard][maxboard], example_saved[maxboard][maxboard];
          // This example array is a simple board that will show how to play in the instruction

     hide_cursor();
     setcolor(l_gray); printf("\n\n\n\t\t\t\t\tTutorial");
     horizontal_line(2,56);
     printf("\n\n       ");

     // The following explains the starting of a game
     setcolor(d_green); printf("First, you will be asked for whether you want to create a log file.\n\n       ");
                        printf("A log file records the score for every move you made.\n\n       ");
     setcolor(red);     printf("The extension will automatically be TEXT file, so just enter the name.\n\n\n       ");
     setcolor(l_gray);  printf("Then you will be asked to choose the Board Type that you want to use.\n\n       ");
                        printf("You can either use the random board generated by the pre-installed function,\n\n       ");
                        printf("or if you have an input board file, you can choose '2' and enter the directory.\n\n\n       ");
     setcolor(blue);    printf("An example directory will be C:\\Documents\\board.txt\n\n       ");
                        printf("If the file is in the same directory as the game file,\n\n       ");
                        printf("just simply type in the file name and extension.\n\n\n       ");
     setcolor(brown);   printf("Finally, you will be asked to enter the size of the board you want to play\n\n       ");
                        printf("if you choose to use the random board.\n\n       ");
                        printf("The row and col are simply the number of rows and columns of the board.\n\n       ");
                        printf("'num' is the number of colors in the board that you can choose.\n\n\n       ");
     setcolor(yellow);  printf("Row and Col ranges from 6 to 24, and Num ranges from 4-9\n\n       ");
     setcolor(red);     printf("When enter the size, just simply separate them by a SPACE.\n       ");

     getch(); // used like system("pause");

     for (rct=0;rct<size[0];rct++)
         for (cct=0;cct<size[1];cct++)
             example[rct][cct] = rand()%size[2]+49;

     example[0][0]='X';  // initialize the first number '2' to be 'X'
     example[0][1]='1';  // initialize the number next to 'X' to be '1'
     example[1][0]='1';  // initialize the number next to 'X' to be '1'

     // The following nested do-while loop is a simple example for showing how to play
     do {
        system("cls");

        setcolor(l_gray); printf("\n\n\n\t\t\t\t\tTutorial\n");
        horizontal_line(3,56);

        printf("\n\t\t\t\t Here is an example board\n");
        board_print(example, size);

        // Draws X
        do {
           for (rct=0;rct<maxboard;rct++)
               for (cct=0;cct<maxboard;cct++)
                   example_saved[rct][cct]=example[rct][cct];

           for (rct=0;rct<size[0];rct++)
               for (cct=0;cct<size[1];cct++)
                   if (example[rct][cct]==i+49 && (example[rct-1][cct]=='X' || example[rct][cct-1]=='X' ||
                       example[rct+1][cct]=='X' || example[rct][cct+1]=='X'))  example[rct][cct] = 'X';

        } while (check_same(example,example_saved,size));  // end of the drawing X loop

        if (i==0) {
           setcolor(l_gray); printf("\n\n\t\t\t      You start with one ");
           setcolor(d_red ); printf("Virus X ");
           setcolor(l_gray); printf("!!\n");
                             sleep(1200);
           setcolor(l_gray); printf("\n\n\t\t\t   Your virus will multiply rapidly after\n\n\t\t\t   ");
                             printf("every move as you choose an adjacent\n\n\t\t\t   number, in this case,");
           setcolor(l_purp); printf(" 1");
           setcolor(l_gray); printf("\n\n\n\t\t\t\t\tPress ");
           setcolor(l_purp); printf("1");
           setcolor(l_gray); printf("...");
        }
        if (i==1) {
           setcolor(l_gray); printf("\n\n\t\t\t    After you press ");
           setcolor(l_purp); printf("1");
           setcolor(l_gray); printf(", all the ");
           setcolor(l_purp); printf("1");
           setcolor(l_gray); printf("s next\n\n\t\t\t    to the Virus are infected and also");
                             printf("\n\n\t\t\t    becomes a colony of ");
           setcolor(d_red ); printf("The Virus X");
           setcolor(l_gray); printf(" !!\n\n\n\t\t\t\t ");
                             sleep(1200);
                             printf("And when you press ");
           setcolor(yellow); printf("2");
           setcolor(l_gray); printf("...");
        }
        if (i==2) {
           setcolor(l_gray); printf("\n\n\t\t\t     All the ");
           setcolor(yellow); printf("2");
           setcolor(l_gray); printf("s next to the virus are");
                             printf("\n\n\t\t\t     infected and also becomes ...\n\n\n\t\t\t\t     ");
           setcolor(d_red ); printf("The Virus X !!!\n");
                             sleep(1200); break;
        }

        getch(); i++;
                                  
     } while (1);  // end of instruction loop

     setcolor(white);
     printf ("\n\n\n\t\t    You will keep choosing numbers until your virus \n\n\t\t    take over the whole board!!\n");
     printf ("\n\n\t\t    The total amount of a number eaten each time by your");
     printf ("\n\n\t\t    virus will be squared and be added up to your score.");
     getch();

     setcolor(gray); printf("\n\n\n\t\t\t\t\tThats it!\n\n\t\t       Are You Ready?  Return to main menu in ");

     while (i>0) {printf("%1d sec\b\b\b\b\b", i--); sleep(1000);}

     return;
}

void game_initialize(int choice)
{
     int size[3], number[maxboard][maxboard];  // use integer array to get numbers from the file is easier
     char a[maxboard][maxboard], filename[50], boardtype, yorn;
     FILE *fileboard;
     time_t playtime=time(NULL);

     fflush(stdin);

     setcolor(7);
     printf("\n\n\n\t\t\tDo you want to create a log file? (y/n) ");
     yorn = getche();

     if (yorn=='Y' || yorn=='y') {
        printf("\n\n\t\t\tName your file: ");
        gets(filename);
        if (!check_filename(filename)) {
           if (choice==1) strcat(filename, ".txt");
           if (choice==2) strcat(filename, " - Computer-Play.txt");
        }
        logfile = fopen(filename,"w");

        // Prints project & group details to the log file
        fprintf(logfile,"\n");
        fprintf(logfile,"\t**************************************************************\n");
        fprintf(logfile,"\t*                    University of Toronto                   *\n");
        fprintf(logfile,"\t*                APS106 - Computer Fundamental               *\n");
        fprintf(logfile,"\t*                     Project 2008 Spring                    *\n");
        fprintf(logfile,"\t*                                                            *\n");
        fprintf(logfile,"\t*     Professor: Prof. Markus Bussman                        *\n");
        fprintf(logfile,"\t*                                                            *\n");
        fprintf(logfile,"\t*     Student  : Jeff  Chieh-Feng Lee   995862883            *\n");
        fprintf(logfile,"\t*                                                            *\n");
        fprintf(logfile,"\t**************************************************************\n");
        fprintf(logfile,"\n\n\t\t\t   %.24s\n\n\n", ctime(&playtime));
     }
     else if (yorn!='n') game_initialize(choice);

     printf("\n\n\n\t\t\t");
     printf("Choose a Board Type:\n\n\t\t\t");
     printf("1.  Random Board\n\t\t\t");
     printf("2.  Use Your Own Board! (board from input file)\n\n\t\t\t");
     printf("Your Choice: ");
     boardtype = getche();
                  
     // Generate random board
     if (boardtype == '1') {
        do {
           printf("\n\n\n\t\t\tEnter size (row col num): ");
           scanf("%d %d %d", &size[0], &size[1], &size[2]);
           if (size[0]<BOARDSIZEMIN || size[1]<BOARDSIZEMIN || size[2]<COLORMIN ||
               size[0]>BOARDSIZEMAX || size[1]>BOARDSIZEMAX || size[2]>COLORMAX) {
              setcolor(red); printf("\n\t\t\tPlease follow the instruction!\n"); setcolor(l_gray);
           }
           else break;

        } while (1);

        if (yorn=='Y' || yorn=='y') fprintf(logfile, "\t %d %d %d\n\t", size[0], size[1], size[2]);

        for (rct=0;rct<size[0];rct++) {
            for (cct=0;cct<size[1];cct++) {
                do {
                   a[rct][cct] = rand()%size[2]+49;
                   if (a[0][1]==a[0][0] || a[1][0]==a[0][0]) continue;
                   else break;

                } while (1);
                if (yorn=='Y' || yorn=='y') fprintf(logfile, "%c", a[rct][cct]);
            }
            if (yorn=='Y' || yorn=='y') fprintf(logfile, "\n\t");
        }
        if (yorn=='Y' || yorn=='y') fprintf(logfile, "\n\n");
     }  // end of random board
     // Input board from a file
     else if (boardtype == '2') {
        printf("\n\n\t\t\tEnter the file name or directory:\n\n\t\t\t");

        do {
           gets(filename);
           fileboard = fopen(filename, "r");

           if (fileboard == NULL) {
              setcolor(red);
              printf("\n\t\t\tNo such file or directory!\n");
              printf("\t\t\tPlease enter again\n\n\t\t\t");
              setcolor(l_gray);
           }
           else break;

        } while (1);

        fscanf(fileboard, "%d", &size[0]);
        fscanf(fileboard, "%d", &size[1]);
        fscanf(fileboard, "%d", &size[2]);

        if (yorn=='Y' || yorn=='y') {
           fprintf(logfile, "\t%d ",size[0]);
           fprintf(logfile, "%d ",size[1]);
           fprintf(logfile, "%d\n\t",size[2]);
        }

        for (rct=0;rct<size[0];rct++) {
            for (cct=0;cct<size[1];cct++) {
                fscanf(fileboard, "%1d", &number[rct][cct]);
                if (yorn=='Y' || yorn=='y')
                   fprintf(logfile, "%d", number[rct][cct]);
                a[rct][cct] = number[rct][cct]+48;
            }
            if (yorn=='Y' || yorn=='y') fprintf(logfile, "\n\t");
        }
        if (yorn=='Y' || yorn=='y') fprintf(logfile, "\n\n");
     }  // end of input board
     else {
        setcolor(red); printf("\n\n\t\t\tPlease Enter what it says there!!");
        setcolor(l_gray); getch(); game_initialize(choice);
     }

     fflush(stdin);
     system("cls");

     if (choice == 1) play(a,size,yorn);
     else if (choice == 2) computer_play(a,size,yorn);

     return;
}

void play(char a[maxboard][maxboard], int size[], char yorn)
{
     int move=-1, score=0, ctx=1, enter, virus=1;
     char number=a[0][0], number_saved, a_saved[maxboard][maxboard], quit;

     a[0][0] = 'X';

     if (yorn=='Y' || yorn=='y') fprintf(logfile, "\t   START\n");

     // Playing loop begins
     do {
        system("cls");

        setcolor(l_gray);
        printf("\n\n\n\n\t\t\t\t\t Virus 3");
        horizontal_line(3,56);
        board_print(a,size);

        setcolor(l_purp); printf("\n\n\t\t\t\t\t\t  Moves: %3d   Score: %d", ++move, score);
        setcolor(d_red); printf("\n\n\t\t\t\t\t\t  Virus Population: %d\n", virus);
        setcolor(white);

        if (yorn=='Y' || yorn=='y') fprintf(logfile, "\t  %c %5d\n", number, score);

        if (judge_over(a,size) == 1) break;

        if (number!='0') number_saved = number;

        printf("\n\n\t\t\t    Choose a medium (");

        for (ctx=1;ctx<=size[2];ctx++)
            if (number_saved != (ctx+48)) {
               setcolor(number_color(ctx)); printf("%d, ", ctx);
            }

        setcolor(white); printf("\b\b) to\n\n\t\t\t    Grow your");
        setcolor(d_red); printf (" Virus");
        setcolor(white); printf ("! (0 to exit): ");

        // choosing number
        do {
           scanf("%d", &enter);

           if ((number=enter+48) == '0') {
              getchar();
              printf("\n\n\t\t\tAre you sure you want to quit the game?(y/n/m)");
              quit = getch();
              if (quit=='y' || quit=='Y') goodbye();
              else if (quit=='n' || quit=='N') {move--; break;}
              else if (quit=='m' || quit=='M') return;
           }
           else if (number == number_saved) {
              setcolor(red); printf("\n\n\t\t\t\tAll the %c has been choosen!", number);
              setcolor(white); printf("\n\n\t\t\t\t      Choose again: ");
           }
           else if (enter>size[2]) {
              setcolor(red); printf("\n\n\t\t\t    The number should be less than %d", size[2]);
              setcolor(white); printf("\n\n\t\t\t\t     Choose again: ");
           }
           else break;
           
        } while (1);

        ctx=0;

        // The following loop draws 'X'
        do {
           for (rct=0;rct<size[0];rct++)
               for (cct=0;cct<size[1];cct++) {
                   a_saved[rct][cct]=a[rct][cct];
                   if (a[rct][cct]==number && (a[rct-1][cct]=='X' || a[rct][cct-1]=='X' || a[rct+1][cct]=='X' || a[rct][cct+1]=='X')) {
                      a[rct][cct] = 'X';
                      ctx++; virus++;
                   }
               }
        } while (check_same(a,a_saved,size));  // end of the drawing X loop
                                  
        score += ctx*ctx;

     } while (1);  // end of the playing loop

     if (yorn=='Y' || yorn=='y') {
        fprintf(logfile,"\t    END\n\n");
        fclose(logfile);
     }
                  
     printf("\n\n");

     again();
}

void computer_play(char a[maxboard][maxboard], int size[], char yorn)
{
     int move=-1, score=0, ctx=1, virus=1;
     char number=a[0][0], a_saved[maxboard][maxboard];

     a[0][0] = 'X';

     if (yorn=='Y' || yorn=='y') fprintf (logfile, "\t   START\n");

     // Play loop begins
     do {
        system("cls");

        setcolor(l_gray);
        printf("\n\n\n\t\t\t\tVirus 3 (Computer Auto-Play)");
        horizontal_line(3,56);
        board_print(a,size);

        setcolor(l_purp); printf("\n\n\t\t\t\t\t\tMoves: %3d   Score: %d", ++move, score);
        setcolor(d_red); printf("\n\n\t\t\t\t\t\tVirus Population: %d\n", virus);
        setcolor(white);

        if (yorn=='Y' || yorn=='y') fprintf(logfile, "\t  %c %5d\n", number, score);

        if (judge_over(a, size) == 1) break;

        printf("\n\n\t\t\t\tMedia Avaliable (");

        for (ctx=1;ctx<=size[2];ctx++)
            if (number != (ctx+48)) {
               setcolor(number_color(ctx)); printf("%d, ", ctx);
            }

        setcolor(white); printf("\b\b) \n\n\t\t\t\t   -- Computer chose ");
        setcolor(number_color(number-48)); printf("%c", number);

        number = computer_thinking(a,size);
                                  
        ctx=0;

        // The following do-while loop draws 'X'
        do {
           for (rct=0;rct<size[0];rct++)
               for (cct=0;cct<size[1];cct++) {
                   a_saved[rct][cct]=a[rct][cct];
                   if (a[rct][cct]==number && (a[rct-1][cct]=='X' || a[rct][cct-1]=='X' || a[rct+1][cct]=='X' || a[rct][cct+1]=='X')) {
                      a[rct][cct] = 'X';
                      ctx++; virus++;
                   }
               }
        } while (check_same(a,a_saved,size));  // end of the drawing X loop
                                  
        score += ctx*ctx;
        //sleep(800);

     } while (1);  // end of the playing loop

     if (yorn=='Y' || yorn=='y') {
        fprintf(logfile,"\t    END\n\n");
        fclose(logfile);
     }
                  
     again();
}

int computer_thinking(char pmnt_copy[maxboard][maxboard], int size[])
{
    /*
       The computer counts how many of each number are adjacent to 'X',
       and return the the one with minimum number.  This way, the number
       with higher repetition will remained and finally all becomes 'X'
       at once.  Also, it will save 4 numbers to the end and infect at once.
    */

    int num_ct[9]={0}, number, num_saved=600, ntl[4]={2,7,3,5};
    char min=0, tmp[maxboard][maxboard], tmp_saved[maxboard][maxboard];

    for (number=0;number<size[2];number++) {
        for (rct=0;rct<size[0];rct++)
            for (cct=0;cct<size[1];cct++)
                tmp[rct][cct]=pmnt_copy[rct][cct];

        do {
           for (rct=0;rct<size[0];rct++)
               for (cct=0;cct<size[1];cct++) {
                   tmp_saved[rct][cct]=tmp[rct][cct];
                   if (tmp[rct][cct]==number+49 && (tmp[rct-1][cct]=='X' || tmp[rct][cct-1]=='X' ||
                       tmp[rct+1][cct]=='X' || tmp[rct][cct+1]=='X')) {
                      tmp[rct][cct]='X'; num_ct[number]++;
                   }
               }
        } while (check_same(tmp,tmp_saved,size));  // end of the drawing X loop
    }  // end of checking each number

    for (number=size[2]-1;number>=0;number--)
        if (num_ct[number]<num_saved && num_ct[number]!=0 && number!=ntl[0]-1 &&
            number!=ntl[1]-1 && number!=ntl[2]-1 && number!=ntl[3]-1) {
           num_saved=num_ct[number];
           min=number+49;
        }

    if (min!=0) return min;
    else if (num_ct[ntl[3]-1]!=0) return ntl[3]+48;
    else if (num_ct[ntl[2]-1]!=0) return ntl[2]+48;
    else if (num_ct[ntl[1]-1]!=0) return ntl[1]+48;
    else if (num_ct[ntl[0]-1]!=0) return ntl[0]+48;
}

bool judge_over(char a[maxboard][maxboard], int size[])
{
    /*
       This function checks if all the numbers on the board have become 'X'.
       If it has, the game is over (return YES), else the game continues(return NO).
    */

    for (rct=0;rct<size[0];rct++)
        for (cct=0;cct<size[1];cct++)
            if (a[rct][cct]!='X') return NO;

    return YES;
}

bool check_same(char a[maxboard][maxboard], char a_saved[maxboard][maxboard], int size[])
{
    // This check_same function is used to draw 'X'

    for (rct=0;rct<size[0];rct++)
        for (cct=0;cct<size[1];cct++)
            if (a[rct][cct]!=a_saved[rct][cct]) return YES;

    return NO;
}

bool check_filename(char *filename)
{
    /*
       This function checks if the filename entered contains .txt extension,
       if not, returns NO and the program will strcat .txt to the the filename.
    */

    char *a=filename, b[5]=".txt", *bptr=b;

    for (rct=0;rct<60;rct++) {
        bptr=b; cct=0;
        while (*(bptr+cct)!='\0') if (*(a+rct+cct)!=*(bptr+cct++)) break;
        if (*(bptr+cct)=='\0') return YES;
    }

    return NO;
}

int number_color(int number)
{
    if (number==1) return l_purp;
    if (number==2) return yellow;
    if (number==3) return white;
    if (number==4) return l_blue;
    if (number==5) return green;
    if (number==6) return blue;
    if (number==7) return gray;
    if (number==8) return l_gray;
    if (number==9) return brown;
}

void board_print(char a[maxboard][maxboard], int size[])
{
     int spacect;

     printf("\n\n");

     for (rct=0;rct<size[0];rct++) {

         // This for loop prints spaces from the left margin so that it is more "center justified"
         for (spacect=0;spacect<sqrt(2800/(size[1]+1));spacect++) printf("  ");

         // This for loop prints the number in different color
         for (cct=0;cct<size[1];cct++) {
             if (a[rct][cct]=='X') {setcolor(4);printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='1') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='2') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='3') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='4') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='5') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='6') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='7') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='8') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
             else if (a[rct][cct]=='9') {setcolor(number_color(a[rct][cct]-48)); printf("%c ", a[rct][cct]);}
         }
         printf("\n");
     }
}

void again(void)
{
     char yorn;

     setcolor(brown); printf("\n\n\t\t\t\t\tGame Over!");

     do {
        setcolor(white); printf("\n\n\n\t\t\t\t    Play Again? (y/n) ");
        yorn=getch();
        if (yorn == 'y' || yorn == 'Y') return;
        else if (yorn == 'n' || yorn == 'N') goodbye();
        else printf("\n\n\t\t\t\t   Not a correct option!\n\n");
     } while(1);
}

void goodbye(void)
{
     setcolor(white); hide_cursor();
     printf("\n\n\n\t\t\t      Thank you for playing Virus 3!");
     printf("\n\n\t\t\t\t      Welcome again!\n\n\t\t\t\t\t    ");
     getch(); exit(0);
}

void horizontal_line(int type, int length)
{
     int dash, color;

     // Type 1 - moving-color
     if (type == 1) {
        printf("\n\n\n\t\t   ");
        for (dash=1;dash<=length;dash++) {
            color=rand()%15+1;
            setcolor(color);
            printf("=");
            sleep(15);
        }
        printf("\n\n");
     }
     // Type 2 - moving
     else if (type == 2) {
        printf("\n\n\n\t\t   ");
        for (dash=1;dash<=length;dash++) {
            printf("-");
            sleep(15);
        }
        printf("\n\n");
     }
     // Type 3 - normal
     else if (type == 3) {
        printf("\n\n\n\t\t");
        for (dash=1;dash<=length;dash++) printf("-");
        printf("\n\n");
     }
}

void setcolor(int color)
{
     /*
        This function is used to access color more easily (as numbers)
        So that we don't need to enter something like...
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED));
     */
                                  
     HANDLE what=GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(what,color);
}

void hide_cursor()
{
     HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO cci;
     cci.bVisible = FALSE;
     cci.dwSize = 25;
     SetConsoleCursorInfo(hcon,&cci);
}

void credit(void)
{
     setcolor(d_green); printf("\n\n\n");
     printf("\t\t**************************************************************\n");
     printf("\t\t*                                                            *\n");
     printf("\t\t*                     ~ Virus 3  v1.0 ~                      *\n");
     printf("\t\t*   Original Game link:                                      *\n");
     printf("\t\t*   http://www.arcadetown.com/virus3/gameonline.asp          *\n");
     printf("\t\t*                                                            *\n");
     printf("\t\t**************************************************************\n\n\n");

     printf("\t\t**************************************************************\n");
     printf("\t\t*                                                            *\n");
     printf("\t\t*                    University of Toronto                   *\n");
     printf("\t\t*                APS106 - Computer Fundamental               *\n");
     printf("\t\t*                     Project 2008 Spring                    *\n");
     printf("\t\t*                                                            *\n");
     printf("\t\t*     Professor: Prof. Markus Bussman                        *\n");
     printf("\t\t*                                                            *\n");
     printf("\t\t*     Student  : Jeff  Chieh-Feng Lee   995862883            *\n");
     printf("\t\t*                                                            *\n");
     printf("\t\t**************************************************************\n\n");

     getch();
     return;
}
