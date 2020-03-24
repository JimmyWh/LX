#include <stdio.h>
#define ADD_TO_SUM(sum_number,value) \
		sum ## sum_number += value

int main()
{
	ADD_TO_SUM(5, 25);
	return 0;
}
