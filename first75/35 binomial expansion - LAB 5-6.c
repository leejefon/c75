/* Binomial Expansion */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    double  x, y, xp, yp, sum=0, term;
    int n, i=0, j, k=0, l=1;
    long int f1, f2, f3, np;
    
    do{
       printf("Enter x: ");
       scanf("%lf", &x);
       printf("Enter y: ");
       scanf("%lf", &y);
       printf("Enter n: ");
       scanf("%d", &n);
    } while (n<0);
    
    if (n==0) {
       printf("(%lf + %lf)^%d = 1\n\n", x, y, n);
       system ("pause");
       return -1;
    }
    
    j=n;
    
    while (i<=n) {
       
		 for(f3=1, l=1;l<=j;l++) f3*=l;
       
		 xp = pow(x, j); j--;
       
       for(f1=1, l=1;l<=k;l++) f1*=l;   
       
		 yp = pow(y, k); k++;
       
       for(f2=1, l=n;l>0;l--) f2*=l;
       
       term = xp*yp*f2/f3/f1;
       sum += term;
       
       i++;
    }
    
    printf("\n(%.2lf + %.2lf)^%d = %.2lf\n\n", x, y, n, sum);
    
    system("pause");
    return 0;
}


/* 
int main()
{
    float a, b, sum;
    int n;
    
    printf("Enter a: ");
    scanf("%f", &a);
    printf("Enter b: ");
    scanf("%f", &b);
    printf("Enter n: ");
    scanf("%d", &n);
    
    sum = pow((a+b), n);
    
    printf("(%f + %f) rasied to the power of %d is %f\n\n", a, b, n, sum);
    
    system("pause");
    return 0;
}
*/
