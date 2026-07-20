/* Factor a number */

#include<stdio.h>
#include<math.h>

void save_number(long long int n)
{
     long long int i=2, j=n, k=0, n_ori=n;
     char y_or_n;
	  FILE *saved;
	  
	  printf("\n\n   -------------------------------------");

	  getchar();   // Get some garbage stored in memory
	  
	  do {
     	  printf("\n\n\n   Wanna save this number?? (y/n)");
     	  scanf("%c", &y_or_n);

        if (y_or_n=='y' || y_or_n=='Y') break;
        else if (y_or_n=='n' || y_or_n=='N') main();
        else continue;
        
	  } while(1);
	  
	  saved = fopen("text\\saved number.txt", "a");
	  if (saved == NULL) printf("\n\n   File not exist!");

	  fprintf(saved, "\n\n   %lld = ", n);

     for (;i<n;i++,j=n) {
			while (j%i==0) {
          	j/=i;
				k++;
   		}

     		if (k==0) continue;
   		else if (k==1) fprintf(saved, " %lld ", i);
			else fprintf(saved, " %lld^%lld ", i, k);

			for (;k>0;k--) n/=i;

			if (n!=1) fprintf(saved, "x");
			else break;

			if (check(n)) continue;    			// From here
			else {                     			// ...
			   fprintf(saved, " %lld", n);   	// ...
			   break;                  			// To here
			}                          			// ...save the time to find the last prime, which is the largest prime
     }   // End of the loop

	  if (n == n_ori) fprintf(saved, "\b\bis a prime!");
	  
	  fclose(saved);
	  printf("\n   The number is saved!");
	  getch();
	  main();
}

void factor(long long int n)
{
	  long long int i=2, j=n, k=0, n_ori=n;
	  
	  printf("\n\n   It can be factored as: \n\n\n     ");
	  
     for (;i<n;i++,j=n) {
			while (j%i==0) {
          	j/=i;
				k++;
   		}

     		if (k==0) continue;
   		else if (k==1) printf(" %lld ", i);
			else printf(" %lld^%lld ", i, k);

			for (;k>0;k--) n/=i;
			
			if (n!=1) printf("x");
			else break;
			
			if (check(n)) continue;    // From here
			else {                     // ...
			   printf(" %lld", n);     // ...
			   break;                  // To here
			}                          // ...save the time to find the last prime, which is the largest prime
     }   // End of the loop
     
     printf("\n\n\n   So It's not a prime!");
     save_number(n_ori);
}

int check(long long int n)   // check if the number has factors
{
    long long int p=0, i=3;   // p=0 ==> n has no factors
    
	 if (n==2) return 0;
	 if (n%2==0) return 1;
    
    for (;i<=sqrt(n);i+=2)   // i starts from 3 and only check odd numbers, speed is doubled
        if (n%i==0) {
		     p=1;
		     break;
		  }

    return p;
}

int main()
{
    long long int num, k;
    char c;
    FILE *open;

	 system("cls");
	 printf("\n   // Enter 0 to quit \n   // Enter 1 to read saved data\n");
    printf("\n   Enter a number: ");
    scanf("%lld", &num);
    
    if (num == 0) exit(0);
    else if (num == 1) {
		 open = fopen("text\\saved number.txt","r");
		 if (open == NULL) printf("\n\n   File not exist!");
		 
		 printf("\n   ------------------------------------------\n");
		 while (fscanf(open, "%c", &c) != EOF) printf("%c", c);
		 
		 fclose(open);
		 getch();
		 main();
	 }

    if (check(num)) factor(num);
    else {
       printf("\n   It's a prime!");
       save_number(num);
    }

	 main();
} 
