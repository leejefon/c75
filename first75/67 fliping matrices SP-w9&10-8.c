/* Fliping matrices */

#include<stdio.h>
#include<windows.h>
#define SIZE 6

void print(void);
void exchange(char);
void hide_cursor(void);

int a[SIZE][SIZE];

int main()
{
    int i, j, over=1;
    char choice;

    hide_cursor();

    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            a[i][j]=SIZE*i+j+1;

    do {

       print();

       switch (choice = getch()) {
          case '1': case '2': case '3': case '4':
             exchange(choice); break;
          case '5':
             over=0; break;
       }

    } while(over);

    return 0;
}

void exchange(char choice)
{
     int i, j, temp[SIZE][SIZE];

     for (i=0;i<SIZE;i++)
         for (j=0;j<SIZE;j++)
             temp[i][j]=a[i][j];

     for (i=0;i<SIZE;i++)
         for (j=0;j<SIZE;j++) {
             if (choice == '1') a[i][j]=temp[i][SIZE-j-1];        // tl_tr
             if (choice == '2') a[i][j]=temp[SIZE-i-1][SIZE-j-1]; // tl_br
             if (choice == '3') a[i][j]=temp[SIZE-i-1][j];        // tl_bl
             if (choice == '4') a[i][j]=temp[j][i];               // tr_bl
         }
}


void print(void)
{
     int i, j;

     printf("\n\n");

     for (i=0;i<SIZE;i++) {
         printf("\t");

         for (j=0;j<SIZE;j++)
             printf("%4d", a[i][j]);

         switch (i) {
            case 0: printf("\n"); break;
            case 1: printf("\tWhat do you want to do with the matrix?\n"); break;
            case 2: printf("\t   1. Flip top left  to  top   right\n\t\
                            \t   2. Flip top left  to bottom right"); break;
            case 3: printf("\t   3. Flip top left  to bottom left\n\t\
                            \t   4. Flip top right to bottom left"); break;
            case 4: printf("\t   5. Exit Program\n"); break;
         }

         printf("\n");
     }

     printf("\n");
}

void hide_cursor()
{
     HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO cci;
     cci.bVisible = FALSE;
     cci.dwSize = 25;
     SetConsoleCursorInfo(hcon,&cci);
}
