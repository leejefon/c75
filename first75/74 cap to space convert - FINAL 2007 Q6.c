#include <stdio.h>

void convert(const char *from, char *to);

int main()
{
    char string[100], string2[200];
    
    gets(string);
    
    convert(string,string2);
    
    printf("Converted string is %s\n",string2);
 
    system("pause");   
    return 0;
}

void convert(const char *from, char *to)
{
     int i=0, j=i;
     
     while (*(from+i) != '\0') {
        if (*(from+i) >= 'A' && *(from+i) <='Z') {
           *(to+i+j++)=' ';
           *(to+i+j)=*(from+i)+32;
        }
        else *(to+i+j)=*(from+i);
        
        i++;
     }
     
     *(to+i+j)=0;
     
     return;
}
