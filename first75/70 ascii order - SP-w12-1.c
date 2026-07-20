/* ASCII Order  */

#include<stdio.h>
#include<string.h>

void ASCII_order(char *string);

int main()
{
	 char string[10000];
	 
	 printf("Enter anything: ");
	 gets(string);
	 
	 ASCII_order(string);
	 
	 printf("In ASCII order: %s", string);

    getch();
    return 0;
}

void ASCII_order(char *string)
{
	  int i;
	  char temp, *stringcpy;
	  
	  stringcpy = (char *)malloc(strlen(string)+1);
	  
	  do {
		  strcpy(stringcpy, string);
		  
	  	  for (i=0;i<strlen(string)-1;i++)
				if (*(string+i)>*(string+i+1)) {
					temp=*(string+i);
					*(string+i)=*(string+i+1);
					*(string+i+1)=temp;
				}
				
     } while(strcmp(stringcpy, string)!=0);


	  return;
}
