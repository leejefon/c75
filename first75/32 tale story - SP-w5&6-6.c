/* Charles Dickens */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    char c;    
    FILE *story;
    FILE *acopy;
    
    story = fopen("text\\32 TaleOfTwoCities_1st_paragraph.txt","r");
    acopy = fopen("text\\32 copy.txt","w");
    
    if (story == NULL)
       printf("The file does not exist yo!\nCheck again!!\n\n");
    
    while (fscanf(story, "%c", &c) != EOF) {
          printf("%c", c);
          fprintf(acopy, "%c", c);
          
          if (c == ',' || c == '.' || c == '-') {
             printf("\n");
             fprintf(acopy,"\n");
          }
    }
    
    printf("\n\ncheck the folder too!!\n\n");
    
    system("pause");
    return 0;
}
