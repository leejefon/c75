/* Legal Date */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int day, month, year;
    
    printf ("Enter a date between 1908-2008(yy/mm/dd): ");
    scanf ("%d/%d/%d", &year, &month, &day);
    
    if (month > 12){
    printf ("Please don't fool around...\n\n");
     system ("pause");
    return 0;
}
/*
    if (month=1, 3, 5, 7, 8, 10, 12 && day>31){
    printf ("Are you kidding me?\n\n");
     system ("pause");
    return 0;
}

    if (month=2, 4, 6, 9, 11 && day>30){
    printf ("Stop playing this program...\n\n");
     system ("pause");
    return 0;
}
*/
    printf ("Dated this %d", day);
    switch (day){
           case 1: case 21: case 31:
                printf ("st");   break;
           case 2: case 22:
                printf ("nd");   break;
           case 3: case 23:
                printf ("rd");   break;
           default: printf ("th");break;
           }
    
    printf (" Day of ");    
    switch (month) {
           case 1: printf ("January");      break;
           case 2: printf ("Feburary");     break;
           case 3: printf ("March");        break;
           case 4: printf ("April");        break;
           case 5: printf ("May");          break;
           case 6: printf ("June");         break;
           case 7: printf ("July");         break;
           case 8: printf ("August");       break;
           case 9: printf ("September");    break;
           case 10: printf ("October");     break;
           case 11: printf ("November");    break;
           case 12: printf ("December");    break;
    } 
    
    if (0<=year && year<=8)       
       printf (", 20%.2d\n\n", year);
    else if (9<=year && year<=99)
        printf (", 19%.2d\n\n", year);
    
    system ("pause");
    return 0;
}
