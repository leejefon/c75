/* ¤«¦r¹CÀ¸ XXOO */

/***********************  *******************  ***************************  *************************
 * Written by Jeff Lee *  * Appearance Edit *  *  Computer Medium Level  *  *  Computer Hard Level  *
 * 2008/02/29 01:30 am *  *   08/03/01 pm   *  * Added 08/03/02 11:30 am *  * Done 08/03/02 4:00 am *
 ***********************  *******************  ***************************  *************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#include<conio.h>
#include<windows.h>

void instruction(int); //
void two_players(void); //
void computer_play(int); // 
int computer_medium(int, char a[]); //
int computer_hard(int, char a[]); // half
void draw_map(char a[]); //
void example_board(void); //
int judge_win(char a[]); //
int judge_repeat(int, char a[]); //
void result(char a[], char player[]); //
void play_again(void); //
void setcolor(unsigned short); //

int main()
{
 	 int choice, desh, j;

    system("cls");
    srand((unsigned) time(NULL));
    printf("\n\n\n\n\t\t\t\t     Welcome to XXOO!\n\n\n\t\t");
    for (desh=1;desh<=56;desh++) {  // From Here
    	  j=rand()%15+1;              // ...
        setcolor(j);                // ...
        printf("-");                // ...
        sleep(15);                  // To Here
    }                               // ... are garbage ... just prints the moving desh
    
    setcolor(7);
    printf("\n\n\n\n\t\t\t\t    1. P1 vs P2\n");      // From Here
    printf("\n\t\t\t\t    2. P1 vs COM (Easy)\n");    // ...
    printf("\n\t\t\t\t    3. P1 vs COM (Medium)\n");  // ...
    printf("\n\t\t\t\t    4. P1 vs COM (Hard)\n");    // ...
    printf("\n\t\t\t\t    5. Exit\n\n");              // ...
    printf("\n\n\t\t\t\tEnter your choice: ");        // To Here
	 scanf("%d", &choice);                           // ... is the main menu of the game...
	 
	 if (choice == 1 || choice == 2 || choice == 3 || choice == 4) instruction(choice);
	 else if (choice == 5) {
       setcolor(14);printf("\n\t\t\t\t   See you again!");
       getch();  // Replacement of system("pause")
       exit(0);
	 }
}

void instruction(int choice)
{
 	  int star, j;
      
     system("cls");
 	  srand((unsigned) time(NULL));
     printf("\n\n\n\t\t\t\t       Instruction\n\n\t\t");
 	  for (star=1;star<=56;star++) {  // From Here
      	j=rand()%15+1;              // ...
        	setcolor(j);                // ...
        	printf("*");                // ...
        	sleep(15);                  // To Here
     }                               // ... are garbage ... just prints the moving star
	  
     setcolor(8); 
	  printf("\n\n\n\t\t\t   The following is an example game board.\n");
	  printf("\t\t\t   Enter the number represented.\n");
	  example_board();
     printf("\n\n\t\t\t   Start Play??\n\t\t\t   (Enter any key to begin!)");
     getch();
     if (choice == 1) two_players();
     else if (choice == 2) computer_play(2);
     else if (choice == 3) computer_play(3);
     else if (choice == 4) computer_play(4);
}

void two_players(void)
{
 	  int i=1, num;
 	  char a[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
 	  char player1[10], player2[10];
 	  
 	  printf("\n\n\t\t\t   Enter name (player 1): ");
 	  scanf("%s", player1);
 	  printf("\n\t\t\t   Enter name (player 2): ");
 	  scanf("%s", player2);
      
     do{
        system("cls");
        printf("\n\n\t\t\t\t%10s VS %-10s\n\n", player1, player2);
        printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        example_board();
        
        if (i%2==1) {
           draw_map(a);
           printf("\t\t\t\t%s, Enter your choice: ", player1);
 	        scanf("%d", &num);
 	        if (judge_repeat(num, a) == 1) {
              printf("\n\t\t\tThere is already stuff there! enter again!!");
              getch();  // Replacement of system("pause")
              continue;
           }
           else if (judge_repeat(num, a) == 0) a[num-1] = 'O';
        }
        else if (i%2==0) {
           draw_map(a);
           printf("\t\t\t\t%s, Enter your choice: ", player2);
    	     scanf("%d", &num);
    	     if (judge_repeat(num, a) == 1) {
              printf("\n\t\t\tThere is already stuff there! enter again!!");
              getch();  // Replacement of system("pause")
              continue;
           }
           else if (judge_repeat(num, a) == 0) a[num-1] = 'X';
        }
        if (judge_win(a) == 1 && i%2==1) result(a, player1);
        else if (judge_win(a) == 1 && i%2==0) result(a, player2);
        else if (judge_win(a) == 2) result(a, '\0');
        
        i++;
     } while(1);
}

void computer_play(int choice)  // The basic idea is that the computer choose a random spot, without any strategy
{
 	  int num, i;
 	  char a[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
 	  char player[7] = "Player";
 	  char comp[9] = "Computer";
 	  
 	  printf("\n\n\n\t\t\t   Who goes first?");
 	  printf("\n\t\t\t   1. Player\n\t\t\t   2. Computer\n");
 	  printf("\n\t\t\t   Enter your choice: ");
 	  scanf("%d", &num);
     
     if(num==1) i=1;
     else if(num==2) i=2;
     
     do{
        system("cls");
        printf("\n\n\t\t\t\t   COMPUTER VS PLAYER!!\n");
        if (choice == 2) printf("\t\t\t\t\t  (Easy)\n\n");
        else if (choice == 3) printf("\t\t\t\t\t (Medium)\n\n");
        else if (choice == 4) printf("\t\t\t\t\t  (Hard)\n\n");
        printf("\t\t\t****************************************\n\n");
        example_board();
        
        if (i%2==1) {
           draw_map(a);
           printf("\t\t\t\tPlayer, Enter your choice: ");
 	        scanf("%d", &num);
 	        if (judge_repeat(num, a) == 1) {
              printf("\n\t\t\tThere is already stuff there! enter again!!");
              getch();
              continue;
           }
           else if (judge_repeat(num, a) == 0) a[num-1] = 'O';
        }  // End of the user's turn
        else if (i%2==0) {  // Beginning of computer easy level
           if (choice == 2) {  // This if statement is for computer easy level
              draw_map(a);
              do {
                 srand((unsigned) time(NULL));  // These tow lines...
                 num = rand()%9+1;              // Let the computer choose a random number
       	        if (judge_repeat(num, a) == 1) continue;
                 else if (judge_repeat(num, a) == 0) {
                    a[num-1] = 'X';
                    break;
                 }
              } while(1);
           }  // End of computer easy level
           else if (choice == 3) {  // Beginning of computer medium level 
              do {
                 num = computer_medium(i,a);
                 if (judge_repeat(num+1, a) == 1) continue;
                 else if (judge_repeat(num+1, a) == 0) {
                    a[num] = 'X';
                    break;
                 }
              } while(1);
           }  // End of computer medium level
           else if (choice == 4) {  // Beginning of computer hard level
              do {
                 num = computer_hard(i,a);
                 if (judge_repeat(num+1, a) == 1) continue;
                 else if (judge_repeat(num+1, a) == 0) {
                    a[num] = 'X';
                    break;
                 }
              } while(1);
           }  // End of computer hard level
        }  // End of computer's turn
        if (judge_win(a) == 1 && i%2==1) result(a, player);
        else if (judge_win(a) == 1 && i%2==0) result(a, comp);
        else if (judge_win(a) == 2) result(a, '\0');
        
        i++;
     } while(1);
}

int computer_medium(int i, char a[])  // This medium level only judges if the palyer is winning or if itself is lining up
{    
    // The following checks if the computer is winning
    if ((a[0]=='X' && a[2]=='X' && a[1]==' ') || (a[4]=='X' && a[7]=='X' && a[1]==' ')) return 1;       // Top Middle
    else if ((a[0]=='X' && a[6]=='X' && a[3]==' ') || (a[4]=='X' && a[5]=='X' && a[3]==' ')) return 3;  // Left Middle
    else if ((a[3]=='X' && a[4]=='X' && a[5]==' ') || (a[2]=='X' && a[8]=='X' && a[5]==' ')) return 5;  // Right Middle
    else if ((a[1]=='X' && a[4]=='X' && a[7]==' ') || (a[6]=='X' && a[8]=='X' && a[7]==' ')) return 7;  // Bottom Middle
    else if ((a[1]=='X' && a[2]=='X' && a[0]==' ') || (a[3]=='X' && a[6]=='X' && a[0]==' ') || (a[4]=='X' && a[8]=='X' && a[0]==' ')) return 0;  // Top Left
    else if ((a[0]=='X' && a[1]=='X' && a[2]==' ') || (a[4]=='X' && a[6]=='X' && a[2]==' ') || (a[5]=='X' && a[8]=='X' && a[2]==' ')) return 2;  // Top Right
    else if ((a[0]=='X' && a[1]=='X' && a[6]==' ') || (a[7]=='X' && a[8]=='X' && a[6]==' ') || (a[4]=='X' && a[2]=='X' && a[6]==' ')) return 6;  // Bottom Left
    else if ((a[0]=='X' && a[4]=='X' && a[8]==' ') || (a[6]=='X' && a[7]=='X' && a[8]==' ') || (a[2]=='X' && a[5]=='X' && a[8]==' ')) return 8;  // Bottom Right
    else if ((a[0]=='X' && a[8]=='X' && a[4]==' ') || (a[1]=='X' && a[7]=='X' && a[4]==' ') || (a[2]=='X' && a[6]=='X' && a[4]==' ') || (a[3]=='X' && a[5]=='X' && a[4]==' ')) return 4;  // Middle Middle
    
    // The following checks if the player is lining up
    if ((a[0]=='O' && a[2]=='O' && a[1]==' ') || (a[4]=='O' && a[7]=='O' && a[1]==' ')) return 1;       // Top Middle
    else if ((a[0]=='O' && a[6]=='O' && a[3]==' ') || (a[4]=='O' && a[5]=='O' && a[3]==' ')) return 3;  // Left Middle
    else if ((a[3]=='O' && a[4]=='O' && a[5]==' ') || (a[2]=='O' && a[8]=='O' && a[5]==' ')) return 5;  // Right Middle
    else if ((a[1]=='O' && a[4]=='O' && a[7]==' ') || (a[6]=='O' && a[8]=='O' && a[7]==' ')) return 7;  // Bottom Middle
    else if ((a[1]=='O' && a[2]=='O' && a[0]==' ') || (a[3]=='O' && a[6]=='O' && a[0]==' ') || (a[4]=='O' && a[8]=='O' && a[0]==' ')) return 0;  // Top Left
    else if ((a[0]=='O' && a[1]=='O' && a[2]==' ') || (a[4]=='O' && a[6]=='O' && a[2]==' ') || (a[5]=='O' && a[8]=='O' && a[2]==' ')) return 2;  // Top Right
    else if ((a[0]=='O' && a[1]=='O' && a[6]==' ') || (a[7]=='O' && a[8]=='O' && a[6]==' ') || (a[4]=='O' && a[2]=='O' && a[6]==' ')) return 6;  // Bottom Left
    else if ((a[0]=='O' && a[4]=='O' && a[8]==' ') || (a[6]=='O' && a[7]=='O' && a[8]==' ') || (a[2]=='O' && a[5]=='O' && a[8]==' ')) return 8;  // Bottom Right
    else if ((a[0]=='O' && a[8]=='O' && a[4]==' ') || (a[1]=='O' && a[7]=='O' && a[4]==' ') || (a[2]=='O' && a[6]=='O' && a[4]==' ') || (a[3]=='O' && a[5]=='O' && a[4]==' ')) return 4;  // Middle Middle
    
    else return rand()%9;
}

int computer_hard(int i, char a[])  // This hard level has some other strategy...but medium level is pretty good already...
{
    int start[4] = {0,8,2,6}, j=rand()%4;
    
    // The following is the first step
    if (i==2 && (a[0]=='O' || a[2]=='O' || a[6]=='O' || a[8]=='O')) return 4;
    else if (i==2) return start[j];
    
    // The following checks if the computer is winning
    if ((a[0]=='X' && a[2]=='X' && a[1]==' ') || (a[4]=='X' && a[7]=='X' && a[1]==' ')) return 1;       // Top Middle
    else if ((a[0]=='X' && a[6]=='X' && a[3]==' ') || (a[4]=='X' && a[5]=='X' && a[3]==' ')) return 3;  // Left Middle
    else if ((a[3]=='X' && a[4]=='X' && a[5]==' ') || (a[2]=='X' && a[8]=='X' && a[5]==' ')) return 5;  // Right Middle
    else if ((a[1]=='X' && a[4]=='X' && a[7]==' ') || (a[6]=='X' && a[8]=='X' && a[7]==' ')) return 7;  // Bottom Middle
    else if ((a[1]=='X' && a[2]=='X' && a[0]==' ') || (a[3]=='X' && a[6]=='X' && a[0]==' ') || (a[4]=='X' && a[8]=='X' && a[0]==' ')) return 0;  // Top Left
    else if ((a[0]=='X' && a[1]=='X' && a[2]==' ') || (a[4]=='X' && a[6]=='X' && a[2]==' ') || (a[5]=='X' && a[8]=='X' && a[2]==' ')) return 2;  // Top Right
    else if ((a[0]=='X' && a[1]=='X' && a[6]==' ') || (a[7]=='X' && a[8]=='X' && a[6]==' ') || (a[4]=='X' && a[2]=='X' && a[6]==' ')) return 6;  // Bottom Left
    else if ((a[0]=='X' && a[4]=='X' && a[8]==' ') || (a[6]=='X' && a[7]=='X' && a[8]==' ') || (a[2]=='X' && a[5]=='X' && a[8]==' ')) return 8;  // Bottom Right
    else if ((a[0]=='X' && a[8]=='X' && a[4]==' ') || (a[1]=='X' && a[7]=='X' && a[4]==' ') || (a[2]=='X' && a[6]=='X' && a[4]==' ') || (a[3]=='X' && a[5]=='X' && a[4]==' ')) return 4;  // Middle Middle
    
    // The following checks if the player is lining up
    if ((a[0]=='O' && a[2]=='O' && a[1]==' ') || (a[4]=='O' && a[7]=='O' && a[1]==' ')) return 1;       // Top Middle
    else if ((a[0]=='O' && a[6]=='O' && a[3]==' ') || (a[4]=='O' && a[5]=='O' && a[3]==' ')) return 3;  // Left Middle
    else if ((a[3]=='O' && a[4]=='O' && a[5]==' ') || (a[2]=='O' && a[8]=='O' && a[5]==' ')) return 5;  // Right Middle
    else if ((a[1]=='O' && a[4]=='O' && a[7]==' ') || (a[6]=='O' && a[8]=='O' && a[7]==' ')) return 7;  // Bottom Middle
    else if ((a[1]=='O' && a[2]=='O' && a[0]==' ') || (a[3]=='O' && a[6]=='O' && a[0]==' ') || (a[4]=='O' && a[8]=='O' && a[0]==' ')) return 0;  // Top Left
    else if ((a[0]=='O' && a[1]=='O' && a[2]==' ') || (a[4]=='O' && a[6]=='O' && a[2]==' ') || (a[5]=='O' && a[8]=='O' && a[2]==' ')) return 2;  // Top Right
    else if ((a[0]=='O' && a[1]=='O' && a[6]==' ') || (a[7]=='O' && a[8]=='O' && a[6]==' ') || (a[4]=='O' && a[2]=='O' && a[6]==' ')) return 6;  // Bottom Left
    else if ((a[0]=='O' && a[4]=='O' && a[8]==' ') || (a[6]=='O' && a[7]=='O' && a[8]==' ') || (a[2]=='O' && a[5]=='O' && a[8]==' ')) return 8;  // Bottom Right
    else if ((a[0]=='O' && a[8]=='O' && a[4]==' ') || (a[1]=='O' && a[7]=='O' && a[4]==' ') || (a[2]=='O' && a[6]=='O' && a[4]==' ') || (a[3]=='O' && a[5]=='O' && a[4]==' ')) return 4;  // Middle Middle

	 // Write a loop to count how many boxes have been chosen and determine whether the computer starts or the player, and then write different possibility

	 // The following is for the possible moves for the second move
    if (i==4 && a[4]=='O' && a[0]=='X') return 8;
    else if (i==4 && a[4]=='O' && a[2]=='X') return 6;
    else if (i==4 && a[4]=='O' && a[6]=='X') return 2;
    else if (i==4 && a[4]=='O' && a[8]=='X') return 0;
    else if (i==4 && (a[1]=='O' || a[3]=='O' || a[5]=='O' || a[7]=='O')) return 4;
    else if (i==4 && (a[0]=='O' || a[2]=='O' || a[6]=='O' || a[8]=='O')) return start[j];
    
    // The following is for the possible moves for the third move
    else if (i==6) return start[j];
    
    // This is for the remaining cases...
    else return rand()%9;   
}

void draw_map(char a[])  // Very similar to example board, except that the number on the board isn't simply from 1-9
{
     int row, i=0;
     
     setcolor(15);printf("\n\n");
     for (row=1;row<60;row++) {
        if (row%12==1) printf("\n\t\t\t\t\t");
        else if (row/12%2 == 0) {
	        if (row%12==0) printf("");
           else if (row%4==0) printf("|");
           else if (row%4==2) printf("%c", a[i++]);
	        else printf(" ");
        }
        else if (row/12%2 == 1) {
           if (row%12==0) printf("");
           else if (row%4==0) printf("+");
           else printf("-");
        }
     }
     printf("\n\n");
}

void example_board(void)   // Uses alternate rows to print the board
{
     int row, i=1;
     
     setcolor(15);
     for (row=1;row<60;row++) {
        if (row%12==1) printf("\n\t\t\t\t\t");    // The beginning of each row, prints some tab
        else if (row/12%2 == 0) {                 // For the even lines, where the numbers are
		     if (row%12==0) printf("");             // The end of each row, prints nothing
           else if (row%4==0) printf("|");        // Used to separate columns
	        else if (row%4==2) printf("%d", i++);  // Prints the number in each box
		     else printf(" ");                      // Prints the space in each box
        }
        else if (row/12%2 == 1) {                 // For the odd lines, print some desh
           if (row%12==0) printf("");             // The end of the row, prints nothing
           else if (row%4==0) printf("+");        // Intersections
           else printf("-");                      // Print desh
        }
     }
}

int judge_win(char a[])
{
	 int win=0; // 0 == nothing, 1 == win, 2 == tie
    
    if (a[0]=='O' && a[1]=='O' && a[2]=='O') win=1;       // From Here
    else if (a[0]=='O' && a[3]=='O' && a[6]=='O') win=1;  // ...
    else if (a[0]=='O' && a[4]=='O' && a[8]=='O') win=1;  // ...
    else if (a[1]=='O' && a[4]=='O' && a[7]=='O') win=1;  // ...
    else if (a[2]=='O' && a[4]=='O' && a[6]=='O') win=1;  // ...
    else if (a[2]=='O' && a[5]=='O' && a[8]=='O') win=1;  // ...
    else if (a[3]=='O' && a[4]=='O' && a[5]=='O') win=1;  // ...
    else if (a[6]=='O' && a[7]=='O' && a[8]=='O') win=1;  // To Here ... 'O' wins
    
    else if (a[0]=='X' && a[1]=='X' && a[2]=='X') win=1;  // From Here
    else if (a[0]=='X' && a[3]=='X' && a[6]=='X') win=1;  // ...
    else if (a[0]=='X' && a[4]=='X' && a[8]=='X') win=1;  // ...
    else if (a[1]=='X' && a[4]=='X' && a[7]=='X') win=1;  // ...
    else if (a[2]=='X' && a[4]=='X' && a[6]=='X') win=1;  // ...
    else if (a[2]=='X' && a[5]=='X' && a[8]=='X') win=1;  // ...
    else if (a[3]=='X' && a[4]=='X' && a[5]=='X') win=1;  // ...
    else if (a[6]=='X' && a[7]=='X' && a[8]=='X') win=1;  // To Here ... 'X' wins
    
    else if (a[1]!=' ' && a[2]!=' ' && a[3]!=' ' && a[4]!=' ' && a[5]!=' ' && a[6]!=' ' && a[7]!=' ' && a[8]!=' ' && a[9]!=' ') win=2;
    // If every a[] is occupied and none of them lines up, it ties...
    
	 return win;
} 

int judge_repeat(int num, char a[])
{
    if (a[num-1] != ' ') return 1;  // 1 stands for repeating
    else return 0;
}

void result(char a[], char player[])
{
     system("cls");
     setcolor(13);printf("\n\n\n\t\t\t\t       GAME OVER!!!\n\n");
     printf("\t\t\t****************************************\n\n");
     example_board();
     draw_map(a);
     if (player == '\0') printf("\n\t\t\t\t\t   Tie!");
     else printf("\n\t\t\t\t      %s wins!", player);
     getch();  // Replacement of system("pause")
     play_again();
}

void play_again(void)
{
    char c;
    
    system("cls");
    getchar();  // Used to get rid of some garbage character stored in memory
    
    printf("\n\n\n\n\n\t\t\t\t   Play Again? (y/n) ");
    c = getchar();
    
    if (c == 'y' || c == 'Y') main();
    else if (c == 'n' || c == 'N') {
       printf("\n\n\t\t\t\t       Bye Bye!!");
       getch();  // Replacement of system("pause")
       exit(0);
    }
    else {
       MessageBox (NULL, "Not a correct option!\n Enter again!" , "Error!!", MB_OK | MB_ICONWARNING);
       // A pop-out message box ... quite useless ...
       play_again();
    }
}

void setcolor(unsigned short color)  // The function that prints different colors
{
     HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hcon,color);
}
