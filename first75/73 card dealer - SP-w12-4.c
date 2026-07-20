/* Card dealer */

#include<stdio.h>

typedef enum {No, Yes} bool;

typedef struct {
   char rank[3];
   char suit[8];
} CARD;

void card_analysis(void);

CARD deal[5];
int num_of_suit[4], num_of_rank[13];

int main()
{
    int i, ranky, suity, seed=45;
    //bool card_exist[13][4]={No};
    char suits[4][8]={"Spade","Heart","Diamond","Club"},
         ranks[13][3]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};

    system("title Poker Hands");
    system("mode con lines=18 cols=26");

    //srand(time(NULL));

    while (srand(seed)) {
       bool card_exist[13][4]={No};

       for (i=0;i<4;i++) num_of_suit[i]=0;
       for (i=0;i<13;i++) num_of_rank[i]=0;

       printf("%d\n\n\n    Five cards dealt:\n\n", seed++);

       for (i=0;i<5;i++) {
           ranky=rand()%13;
           suity=rand()%4;
           if (card_exist[ranky][suity]==0) {
              strcpy(deal[i].rank, ranks[ranky]);
              strcpy(deal[i].suit, suits[suity]);
              card_exist[ranky][suity]=Yes;
              num_of_suit[suity]++;
              num_of_rank[ranky]++;
              printf("        %2s %s\n", deal[i].rank, deal[i].suit);
           }
           else i--;
       }
    
       card_analysis();

       if (getch()=='q') return 0;
       //sleep(500);
       system("cls");

    }
}

void card_analysis()
{
     int suit, rank=0, straightnum=0;
     bool flush=No, straight=No, four=No, three=No, pairs=0;
     
     /* Check for flush */
     for (suit=0;suit<4;suit++)
         if (num_of_suit[suit]==5) flush=Yes;
         
     /* Check for straight */
     while (num_of_rank==0) rank++;  // Move rank to where there is card
     for (;rank<13 && num_of_rank[rank];rank++) straightnum++;
     if (straightnum==5) straight=Yes;

     /* Check for duplicate cards */
     for (rank=0;rank<13;rank++) {
         if (num_of_rank[rank]==4) four=Yes;
         if (num_of_rank[rank]==3) three=Yes;
         if (num_of_rank[rank]==2) pairs++;
     }
     
     if (straight && flush)   printf("\n\n     Stragiht Flush    \n");
     else if (four)           printf("\n\n     Four of a kind    \n");
     else if (three && pairs) printf("\n\n       Full House      \n");
     else if (flush)          printf("\n\n         Flush         \n");
     else if (straight)       printf("\n\n        Straight       \n");
     else if (three)          printf("\n\n     Three of a kind   \n");
     else if (pairs == 2)     printf("\n\n        Two Pairs      \n");
     else if (pairs == 1)     printf("\n\n          A Pair       \n");
     else                     printf("\n\n        High card      \n");
     
     return;
}
