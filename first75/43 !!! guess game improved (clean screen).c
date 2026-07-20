/* Guess Game */

/***********************
 * Written by Jeff Lee *
 * 2008/02/23 02:30 pm *
 ***********************/

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

void setcolor(unsigned short color)
{
     HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hcon,color);
}

void again(void)
{
    char c='\0';
    
    getchar();
    printf("\n\n\t\t\t\t Play Again? (y/n) ");
    c = getchar();
    if (c == 'y') main();
    else if (c == 'n') {
       printf("\n\n\t\t\t\t      Bye Bye!!");
       getch();
    }
    else {
       MessageBox (NULL, "Not a correct option!\n Enter again!" , "Error!!", 0);
       again();
    }
}

int main()
{
    int num, guess=-100, max, min=0, i, j, k;
    time_t start;
    time_t end;
    
    system("cls");
    setcolor(14); printf("\n\n\n\t\t\t       Welcome to The Guess Game!!\n\n\t\t");
    for(i=1;i<=57;i++) {
       j=rand()%15+1;
       setcolor(j);
       printf("-");
       sleep(15);
    }
    setcolor(9); printf("\n\n\n\n\t\t\t\tWhat's the range you want?\n\n\t\t  <<Enter a number greater than 10 or Enter -1 to quit>>\n\n\n\t\t\t\t\t    ");
    setcolor(8); scanf("%d", &max);
    if (max == -1) exit(0);
    
    srand((unsigned)time(NULL));
    num = rand()%max+1;
    
    if (num == max) num--;
    if (max <=10) {
       setcolor(12); printf("\n\n\t\t\t     Enter something less than 10 yo!\n\n");
       system("pause");
       main();
    }
    
    if (max<1000) i=k=10;
    else if (max<10000) i=k=15;
    else if (max>=10000) i=k=20;
    
    time(&start);
    
    system("cls");
    while(1) {
       //printf("%d", num);
       if (i--==0) break;
          
       if ((num-guess) <= num/20 && (guess-num) <= num/20) {
          setcolor(13); printf("\n\n\t\tAlmost There!!\n");
       }
       else if ((num-guess) <= num/10 && (guess-num) <= num/10) {
          setcolor(14); printf("\n\n\t\tThat was a very close guess!!\n");
       }
          
       setcolor(11); printf("\n\n\t\t%d < GUESS < %d\n\n", min, max);
       
       setcolor(10); printf("\n\t\tLife remain: ");
       for (j=0; j<i+1; j++) printf("=");
       
       if (j>=9) {setcolor(12); printf("\n\t\tYou still have many chances!\n");}
       else if (j<9 && j>6) {setcolor(5); printf("\n\t\tYou can do it!\n");}
       else if (j>3) {setcolor(13); printf("\n\t\tTry harder!!\n");}
       else if (j<=3) {setcolor(4); printf("\n\t\tDon't Give up!\n");}
          
       setcolor(15); printf("\n\n\t\tGuess a number\n\n\n\t\t      ");
       scanf("%d", &guess);
       
       if (guess >= max || guess <= min) {
          printf("\n\t\tTold you the range is between %d and %d, don't fool around!!\n\n\n\n", min, max);
          getch(); 
          system("cls");
          continue;
       }
          
       if (guess == num) break;
       else if (guess > num) max = guess;
       else if (guess < num) min = guess;
       
       system("cls");
    }
    
    system("cls");
    if (guess == num) {
       time(&end);
       printf("\n\n\n\n\t     Congratulations!! You got the number in %d guesses in %g seconds!\n\n\n", k-i, difftime(end,start));
    }
    else {
       printf("\n\n\n\n\t\t\t   Too bad,,,you didn't get it...\n\n");
       printf("\n\n\t\t\t     The correct answer is %d\n\n", num);
    }
    again();
}
