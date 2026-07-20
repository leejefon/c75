/* Quadratic Equation */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float a, b, c, x_1, x_2, x_3, x_4;
    
    printf ("\nax^2 + bx + c =0\n\n");
    
    printf ("\ta= ");
    scanf ("%f", &a);
    printf ("\tb= ");
    scanf ("%f", &b);
    printf ("\tc= ");
    scanf ("%f", &c);
    
    x_1 = (-b + sqrt(b*b - 4*a*c))/(2*a);
    x_2 = (-b - sqrt(b*b - 4*a*c))/(2*a);
    x_3 = -b/(2*a);
    x_4 = sqrt((4*a*c - b*b)/(4*a*a));
    
    if (a == 0 && b == 0 && c != 0)
       printf ("\n'c' must be 0.\n\n");
    else if (a == 0 && b == 0 && c == 0)
       printf ("\nAll zero...stop fooling around...\n\n");
    else if (a == 0)
       printf ("\nThe solution of the equation is %.2f.\n\n", (-c/b));
    else if ((b*b - 4*a*c) > 0)
       printf ("\nThe solutions of the equation are %.2f, and %.2f.\n\n", x_1, x_2);
    else if ((b*b - 4*a*c) == 0)
       printf ("\nThe only solution is %.2f.\n\n", x_1);
    else
       printf ("\nThe solutions are (%.2f + %.3fi), and (%.2f - %.3fi).\n\n", x_3, x_4, x_3, x_4);
        
    system ("pause");
    main();
}
