/* Calculate Grade */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *input;
    FILE *output;
    int n, a=0, b=0, c=0, d=0, f=0, i=0, as, bs, cs, ds, fs, sum=0;
    
    input = fopen("text\\38 garbage numbers.txt","r");
    output = fopen("text\\33 new stat.txt","w");
    
    printf("A: 80-100\nB: 70-79\nC: 60-69\nD: 50-59\nF: 0-49\n\n");
        
    while(fscanf(input,"%d", &n) != EOF) {
       if(n>=80 && n<=100) a++;
       else if(n>=70) b++;
       else if(n>=60) c++;
       else if(n>=50) d++;
       else f++;
       
       sum+=n;
       i++;
    }
    
    printf("total # students: %d\n", i);
    printf("      # A's: %d\n", a);
    printf("      # B's: %d\n", b);
    printf("      # C's: %d\n", c);
    printf("      # D's: %d\n", d);
    printf("      # F's: %d\n", f);
    
    printf("\n   Average: %.2f %\n", 1.*sum/i);
    
    fprintf(output, "total # students: %d\n", i);
    fprintf(output, "      # A's: %d\n", a);
    fprintf(output, "      # B's: %d\n", b);
    fprintf(output, "      # C's: %d\n", c);
    fprintf(output, "      # D's: %d\n", d);
    fprintf(output, "      # F's: %d\n", f);
    
    fprintf(output, "\n   Average: %.2f %\n", 1.*sum/i);
    
    as=a; bs=b; cs=c; ds=d; fs=f;
    
    printf("\nA: ");
    fprintf(output, "\nA: ");
    while (a>0) {
       a-=5;
       printf("*");
       fprintf(output, "*");
    }
    printf("  %d\n\n", as);
    fprintf(output, "%d\n\n", as);
    
    printf("B: ");
    fprintf(output, "B: ");
    while (b>0) {
       b-=5;
       printf("*");
       fprintf(output, "*");
    }
    printf("  %d\n\n", bs);
    fprintf(output, "%d\n\n", bs);
    
    printf("C: ");
    fprintf(output, "C: ");
    while (c>0) {
       c-=5;
       printf("*");
       fprintf(output, "*");
    }
    printf("  %d\n\n", cs);
    fprintf(output, "%d\n\n", cs);
    
    printf("D: ");
    fprintf(output, "D: ");
    while (d>0) {
       d-=5;
       printf("*");
       fprintf(output, "*");
    }
    printf("  %d\n\n", ds);
    fprintf(output, "%d\n\n", ds);
    
    printf("F: ");
    fprintf(output, "F: ");
    while (f>0) {
       f-=5;
       printf("*");
       fprintf(output, "*");
    }
    printf("  %d\n\n", fs);
    fprintf(output, "%d\n\n", fs);
    
    fclose(input);
    fclose(output);
    
    system("pause");
    return 0;
}
