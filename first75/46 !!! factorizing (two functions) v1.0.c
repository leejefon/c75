/* Check Prime */

#include<stdio.h>
#include<math.h>

void factor(long long int n)
{
	  long long int i=2, j=n, k=0;
	  
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
    long long int num;
 
    do {

       printf("\n   Enter a number (0 to quit): ");
       scanf("%lld", &num);
    
       if (num == 0)
          exit(0);
       else if (num<2)
	      printf("\n   Please enter something larger than 1!\n");

    } while (num<2);

    if (check(num)) factor(num);
    else printf("\n   It's a prime!");

    getch();
    return 0;
} 
