#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char letter;
    
    printf("Enter letter grade: ");
    scanf("%c", &letter);
    
    if (letter == 'A' || letter == 'a')
       printf("The numerical grade is between 80-100\nYou are in Honor Roll!!\n\n");
    else if (letter == 'B' || letter == 'b')
         printf("The numerical grade is between 70-80\nYou did a good job!\n\n");
    else if (letter == 'C' || letter == 'c')
         printf("The numerical grade is between 60-69.9\nNah..acceptable..just excaped from probation\n\n");
    else if (letter == 'D' || letter == 'd')
         printf("The numerical grade is between 50-59.9\nToo bad..you are in probation..Do better next semester!\n\n");
    else if (letter == 'F' || letter == 'f')
         printf("YOU FAILED!!!Coma Back Next YEAR!\n\n");
    else if (letter == 'e')
         exit(0);
    else
         printf("Type an LETTER GRADE!\n\n");
    
    system("pause");
    return 0;
}
