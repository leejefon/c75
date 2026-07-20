#include<stdio.h>
#include<time.h>

int data(int a, int b)
{
    FILE *garb;
    char record;
    time_t now=time(NULL);
    int i=1;
    
    if (a==1) {
       garb = fopen("text\\record.dat", "r");
       if (garb == NULL) printf("file not exist!");
       while (fscanf(garb, "%c", &record) != EOF) {
          printf("%c", record);
       }
    }
    else if (a==2) {
       garb = fopen("text\\record.dat", "w");
       if (garb == NULL) printf("file not exist!");
       fprintf(garb, "");
    }
    else {
       garb = fopen("text\\record.dat","r");
       if (garb == NULL) printf("file not exist!");
       while (fscanf(garb, "%c", &record) != EOF) {
          if (record == '\n') i++;
       }
       fclose(garb);
       garb = fopen("text\\record.dat","a");
       fprintf(garb, "\n%d\t3*%d = %3d\t\t%.24s", i, a, b, ctime(&now));
    }  
    
    fclose(garb);
    return 1;
}

int enter(int i)
{
    int j, sum;
    
    printf("\nEnter a number: ");
    scanf("%d", &j);
        
    data(j, i*j);
}

int main()
{
    int choice, k;
    
    printf("1. enter\n2. read\n3. clear data\n4. exit\n\n");
    printf("Enter a choice: ");
    scanf("%d", &choice);
   
    if (choice == 1) enter(3);
    else if (choice == 2) data(1,0);
    else if (choice == 3) data(2,0);
    else exit(0);
    
    printf("\n\n\aDone!");
    getch();
    system("cls");
    main();
    return 0;
}
