#include <stdio.h>
#include <windows.h>
#include <conio.h>

void setcolor(unsigned short color)
{
     HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hcon,color);
}

int main()
{
    int i=1;
    
    for(;i<=500;i++) {
       setcolor(i);
       printf("Halo!%d\t", i);
       if(i%5==0) printf("\n\n");
    }
    
    getch();
    return 0;
}
