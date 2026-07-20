#include <stdio.h>

int main()
{
     int W[12]={6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
     int y, m, d, w, k;
     
     printf("Enter date(yyyy/mm/dd): ");
     scanf("%d/%d/%d",&y, &m, &d);

     w=W[m-1]+y+(y/4)-(y/100)+(y/400);

     if( ((y%4)==0) && (m<3) ) {
        w--;
        if((y%100)==0) w++;
        if((y%400)==0) w--;
     }
     
     k=(w+d)%7;
     printf("\nIt's ");
     switch(k) {
        case 0: printf("Sunday.\n");    break;
        case 1: printf("Monday.\n");    break;
        case 2: printf("Tuesday.\n");   break;
        case 3: printf("Wednesday.\n"); break;
        case 4: printf("Thursday.\n");  break;
        case 5: printf("Friday.\n");    break;
        case 6: printf("Saturday.\n");  break;
     }

     getch();
     system("cls");
     main();
     return 0;
}

