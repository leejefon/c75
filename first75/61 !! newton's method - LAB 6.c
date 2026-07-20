/* ¸Ñ¤èµ{ */

#include<stdio.h>
#include<math.h>

double ori_func(double a[], double);
double dri_func(double a[], double);

int main()
{
	 int i;
	 double a[12], ans, temp_ans, new_ans;

	 printf("ax^5+bx^4+cx^3+dx^2+ex+f\n");
	 printf("------------------------ = 0\n");
	 printf("gx^5+hx^4+ix^3+jx^2+kx+l\n");
	 
	 printf("\nEnter (a b c d e f): ");
	 scanf("%lf %lf %lf %lf %lf %lf", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5]);
	 printf("\nEnter (g h i j k l): ");
	 scanf("%lf %lf %lf %lf %lf %lf", &a[6], &a[7], &a[8], &a[9], &a[10], &a[11]);

	 printf("\nGive an approx ans: ");
	 scanf("%lf", &ans);
	 
	 do {
		 new_ans = ans - ori_func(a,ans)/dri_func(a,ans);
		 temp_ans = ans;
		 ans = new_ans;
	 } while (fabs(ans-temp_ans)>1e-5);
	 
	 printf("\nThe ans is %.3f", ans);
	 
    getch();
    return 0;
}

double ori_func(double a[], double ans)
{
	  double i, j;

	  i = a[0]*pow(ans,5)+a[1]*pow(ans,4)+a[2]*pow(ans,3)+a[3]*ans*ans+a[4]*ans+a[5];
	  j = a[6]*pow(ans,5)+a[7]*pow(ans,4)+a[8]*pow(ans,3)+a[9]*ans*ans+a[10]*ans+a[11];
	  return i/j;
}

double dri_func(double a[], double ans)
{
	  double i, j, id, jd;

     i = a[0]*pow(ans,5)+a[1]*pow(ans,4)+a[2]*pow(ans,3)+a[3]*ans*ans+a[4]*ans+a[5];
	  j = a[6]*pow(ans,5)+a[7]*pow(ans,4)+a[8]*pow(ans,3)+a[9]*ans*ans+a[10]*ans+a[11];
	  id = 5*a[0]*pow(ans,4)+4*a[1]*pow(ans,3)+3*a[2]*pow(ans,2)+2*a[3]*ans+a[4];
	  jd = 5*a[6]*pow(ans,4)+4*a[7]*pow(ans,3)+3*a[8]*pow(ans,2)+2*a[9]*ans+a[10];
	  
	  return (id*j-jd*i)/j/j;
}
