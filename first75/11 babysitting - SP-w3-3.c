/* Babysitting Charge */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int hr, hr_1, hr_2, c;
    float min, min_1, min_2, d;
    
    printf ("Enter a start time: ");
    scanf ("%d %f", &hr, &min);
    printf ("Enter an end time: ");
    scanf ("%d %f", &hr_1, &min_1);
    
    if (hr<6 && hr_1<6){
       hr += 12;
       hr_1 += 12;}
    else if (hr_1<6 && hr>=6)
       hr_1 += 12; 
    
    if ((hr_1 - hr) <0 || min>59 || min_1>59){
       printf ("\nYou entered an invalid time.\n\n");
    system ("pause");
    return -1;
}

    if (min_1<min){
       hr_1 -= 1;
       min_1 += 60;
}
    
    hr_2 = hr_1 - hr;
    min_2 = min_1 - min;
    c = (hr_2 + (min_2)/60)*4.5;
    d = (hr_2 + (min_2)/60)*4.5;
    
    if (d>c)
    printf ("Charge: $%d\n\n", c+1);
    else
    printf ("Charge: $%d\n\n", c);
    
    system("pause");
    return 0;
}
