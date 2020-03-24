#include <stdio.h>
#define TRUE  1
#define FALSE 0

int main(void)
{
	int leap_year,year;
	scanf("%d",&year);
	if (year%400 == 0) 
		leap_year = TRUE;
	else if (year % 100 == 0)
		leap_year = FALSE;
	else if (year % 4 == 0)
		leap_year = TRUE;
	else
		{

		}
	return 0;
}
