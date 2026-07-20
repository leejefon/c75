/* Is what? */

#include<stdio.h>
//#include<stdlib.h>

int is_lower(char c);
int is_upper(char c);
int is_number(char c);

int main()
{
 	 char input;

    system("cls");

    printf("Enter a character: ");    
    input = getchar();
    
    if (is_lower(input)) printf("\nThat's a lower case character!");
    else if (is_upper(input)) printf("\nThat's an upper case character!");
    else if (is_number(input)) printf("\nThat's a number!");

    getchar();
    getchar();
    main();
    //system("pause");
    return 0;
}

int is_upper(char c)
{
 	 if (c>=65 && c<=90) return 1;
 	 else return 0;
}

int is_lower(char c)
{
 	 if (c>=97 && c<=122) return 1;
 	 else return 0;
}

int is_number(char c)
{
 	 if (c>=48 && c<=57) return 1;
 	 else return 0;
}
