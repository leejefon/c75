#include<stdio.h>
#include<string.h>

void getText(char text[]);
void morsecode(char text[], char morse[][5]);

int i;

int main()
{
    char morse[26][5]={ {".-"},{"-..."},{"-.-."},{"-.."},{"."},
                        {"..-."},{"--."},{"...."},{".."},{".---"},
                        {"-.-"},{".-.."},{"--"},{"-."},{"---"},
                        {".--."},{"--.-"},{".-."},{"..."},{"-"},
                        {"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},
                        {"--.."} },
         text[100];
                        
    getText(text);
    morsecode(text, morse);
    
    getch();
}

void getText(char text[])
{
     scanf("%[^!]", text);
     
     for (i=0;i<strlen(text);i++)
         if (text[i] >= 'a' && text[i] <= 'z')
            text[i] -= 32;
}

void morsecode(char text[], char morse[][5])
{
     for (i=0;i<strlen(text);i++) {
         if (text[i] == ' ') printf("\n");
         else printf("%s ", morse[text[i]-'A']);
     }
}
