/* This program copies a file */

#include<stdio.h>

int main()
{
    char c, anitalin[100], jefflee[100];
    FILE *anita;
    FILE *jeff;
    
	 printf("Open: ");
	 gets(anitalin);
    
    anita = fopen(anitalin, "r");
    if(anita == NULL){
             printf("the file does not exist\n\n");
             system("pause");
             return -1;
    }
    
    printf("Save as: ");
	 gets(jefflee);

    jeff = fopen(jefflee,"w");
    if(jeff == NULL){
             printf("the directory is invalid\n\n");
             system("pause");
             return -1;
    }
    
    while (fscanf(anita, "%c", &c) != EOF) {
          fprintf(jeff, "%c", c);
          putchar(c);
    }
    
    printf("\nDone!!\n\n");
    
    fclose(anita);
    fclose(jeff);
    
    getch();
    return 0;
}
