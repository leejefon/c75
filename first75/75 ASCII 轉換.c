/* ASCII convert */
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char str[100], *ptr;
    int i;

    printf("\n   To ASCII: ");
    gets(str);
    
    printf("\n\t");
    for(i=0;i<strlen(str);i++) printf("%d ",str[i]);

    printf("\n\n   ASCII To: ");
    gets(str);
    ptr= strtok(str," ");
    
    printf("\n\t");
    while(ptr!=NULL) {
       sscanf(ptr,"%d", &i);
       printf("%c",i);
       ptr=strtok(NULL," ");
    }

    printf("\n\n\n");
    system("pause");
    return 0;
}
