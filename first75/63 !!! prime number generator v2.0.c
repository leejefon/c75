/* Check prime 2 */

#include<stdio.h>
#include<time.h>
#include<math.h>

int check(int n)
{
    int j, p=1;   // 1 stands for "it's a prime"
    
    //if (n<2) return 0;
    if (n == 2) return 1;
    if (n%2 == 0) return 0;
    
    for (j=3;j<=sqrt(n);j+=2)
        if (n%j == 0) p=0;
    
    return p;
}
       

int main()
{
    long long int prime, i=2, i_ori=i, filenum=i/2/1e5+1, startnum=i/10e5, endnum;
    FILE *prim;
    clock_t start, finish;
    char filename[60], filestart[12], fileend[12];

    system("title Prime Number Generator");
    system("mode con cols=37 lines=9");

	 printf("\n   (Start from %d)\n", i);
	 
	 printf("\n   Enter: ");
    scanf("%lld", &prime);
    printf("\n   ");
    
    endnum = prime/1e5;

	 sprintf(filename, "%d", filenum);
	 strcat(filename," prime ");
	 sprintf(filestart, "%d", startnum);
	 strcat(filestart,"x10^5 to ");
	 sprintf(fileend, "%d", endnum);
	 strcat(fileend,"x10^5.txt");
	 strcat(filename,filestart);
	 strcat(filename,fileend);

    prim = fopen(filename, "w");
    
    if (prim == NULL) {
	    printf("\n   No such directory!!");
		 getch();
		 system("cls");
		 main();
	 }
    
	 start = clock();

	 for (;i<prime;i++) {
  	 	  printf("%3.0f%c complete...\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", (float)(i-i_ori)/(prime-i_ori)*100, 37);
        if (check(i)) fprintf(prim, "%10lld\n", i);
    }
    
	 finish = clock();

	 fclose(prim);
  	 printf("\a100%c complete in %.2f second!", 37, (double)(finish-start)/CLOCKS_PER_SEC);

    getch();
    return 0;
}
