/* Guess Game */

/******************** 
 * Done by Jeff Lee *
 *    2008/01/27    *
 ********************/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    
    int num, i, j, n=1;
    
    srand((unsigned) time(NULL));
    num = rand()%1000+1;
    
    //printf("%d\n", num);
    printf("Guess a number between 1-1000!\n(Enter -1 to quit the game)\n\n");    
    printf("Guess %d: ", n++);
    scanf("%d", &i);
    
    if(i == -1)
          exit(0);
          
    while(i<1 || i>1000) {
       printf("\nBETWEEN 1-1000!!! You idiot!!\n");
       printf("Choose again(%d): ", n++);
       scanf("%d", &i);
    }
    
    if ((i-num)<=40 && (num-i)<=40 && i!=num && n==2) {
       printf("Wow genuis!!Got so close at first guess!!\n");
       printf("The difference is less than 30!!\n");
    }
    else if (i==num) {
       printf("Oh my god!! How did you do it!! You got it in one guess!!!\n\n");
       main();
    }
                    
    big:
        while (i>num) {
           printf("\nLower than %d...Guess again!\n", i);
           printf("Try again(%d): ", n++);
           scanf("%d", &i);
          
           if(i == -1)
               exit(0);
          
           if(i<1 || i>1000) {
               printf("\nBETWEEN 1-200!!! You idiot!!\n");
               printf("Choose again(%d): ", n++);
               scanf("%d", &i);
           }
               
           if ((i-num)<=30 && i!=num)
               printf("\nClose!");
          
           if (i<num) goto small;
           else if (i==num) {
               printf("\nYou Got it in %d ", n-1);
               switch(n-1) {
                      case 2: case 3: case 4: case 5:
                           printf("guesses!! 妳可以去簽樂透了!!\n\n\n"); break;
                      case 6: case 7: case 8: case 9:
                           printf("guesses...猜有點多次喔 不過恭喜啦 至少猜到了!!\n\n\n"); break;
                      case 10: printf("guesses...算妳好運...最後一次機會被你猜到了...\n\n\n"); break;
               }
               system("pause"); 
               system("cls");
               main();
           }
               
           if (n>10) {
              printf("\nThe correct answer is %d!!", num);
              printf("\n猜了十次都還猜不到...太天才了吧...重玩吧\n\n");               
              main();
           }
        }

    small:
         while(i<num) {      
            printf("\nHigher than %d...Guess again!\n", i);
            printf("Try again(%d): ", n++);
            scanf("%d", &i);
           
            if(i == -1)
               exit(0);
           
            if(i<1 || i>1000){
               printf("\nBETWEEN 1-200!!! You idiot!!\n");
               printf("Choose again(%d): ", n);
               scanf("%d", &i);}
                    
            if ((num-i)<=30 && i!=num)
               printf("\nClose!");
           
            if (i>num) goto big;
            else if (i==num) {
               printf("\nYou Got it in %d ", n-1);
               switch(n-1){
                      case 2: case 3: case 4: case 5:
                           printf("guesses!! 妳可以去簽樂透了!!\n\n\n"); break;
                      case 6: case 7: case 8: case 9:
                           printf("guesses...猜有點多次喔 不過恭喜啦 至少猜到了!!\n\n\n"); break;
                      case 10: printf("guesses...算妳好運...最後一次機會被你猜到了...\n\n\n"); break;
               }
               system("pause");
               system("cls");
               main();
            }
               
            if (n>10) {
               printf("\nThe correct answer is %d!!", num);
               printf("\n猜了十次都還猜不到...太天才了吧...重玩吧\n\n");
               main();
            } 
         }

   system("pause");
   return 0;
}
