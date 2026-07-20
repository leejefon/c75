/* ROT13 Encoder/Code reader */
 
#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *code;
    FILE *ans;
    char c;
    
    code = fopen("text\\42 a.txt","r");
    ans = fopen("text\\42 b.txt","w");
    
    if (code == NULL)
       printf("file does not exist!!   Check again!!\n\n");
    else {
       while (fscanf(code, "%c", &c) != EOF) {
          if (c>='a' && c<='m')
             fprintf(ans, "%c", c+13);
          else if (c>='n' && c<='z')
             fprintf(ans, "%c", c-13);
          else if (c>='A' && c<='M')
             fprintf(ans, "%c", c+13);
          else if (c>='N' && c<='Z')
             fprintf(ans, "%c", c-13);
          else
             fprintf(ans, "%c", c);
       }
       printf("\nDone!! Check your folder!\n\n");
    } 
    
    fclose(code);
    fclose(ans);
    
    system("pause");
    return 0;
}
