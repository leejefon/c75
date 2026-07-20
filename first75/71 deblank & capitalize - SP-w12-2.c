/* Deblank and Capitalize */

#include<stdio.h>

void noBlanks (char *a);

int main ()
{
    char a[1000];

    gets(a);
    noBlanks(a);

    system ("pause");
    return 0;
}

void noBlanks (char *a)
{
     char b[1000], *temp1;
     int i=0, temp2;

     if (*a>='a' && *a<='z') *a -= ('a'-'A');

     while (*a!='\0') {
        if (*a==' ') {
           temp1 = a;
           temp2 = i;

           while (*++a!='\0') b[i++] = *a;

           a = temp1;
           i = temp2;

           if (*++a>='a' && *a<='z') *a -= ('a'-'A');
        }
        else b[i++] = *a++;
     }

     b[i] = '\0';
     puts(b);

     return;
}
