/* Cost of Gasoline in a trip*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  float distance, fuel_efficiency, the_cost, trip_cost;
  
  printf("How far (km): ");
  scanf("%f", &distance);
  printf("Fuel efficiency (litres/100km): ");
  scanf("%f", &fuel_efficiency);
  printf("Cost of gas (cents/litres): ");
  scanf("%f", &the_cost);
  trip_cost = (distance / 100) * fuel_efficiency * (the_cost / 100); 
  
  printf("\n");
  printf("Cost of the trip: $ %.2f\n", trip_cost); 
  
  system("PAUSE");	
  return 0;
}
