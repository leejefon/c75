#include <stdio.h>
#include <time.h>

int main()
{
	 int i=10;
	 time_t start = time(NULL);
    time_t current;
    time_t now;
    
    do{
       time(&current);
       printf("Time: %.24s. \n", ctime(&current));
       printf("\nDelay for %d more seconds.\n", i--);
       sleep(1000);
       system("cls");
    } while(difftime(current,start) < 10.0);
    
    printf("\n\nFinished delay.\n\n");
    
    time(&now);
    printf("It's %.24s.\n", ctime(&now));

    getch();
    return 0;
}
