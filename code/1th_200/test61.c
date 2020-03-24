#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float new_guess;
	float last_guess;
	float number;

	printf("Please Enter the number : ");
	scanf("%f",&number);
	if (number < 0)
	{
		printf("number input err!\n");
		return EXIT_FAILURE;
	}	


	new_guess = 1;
	do{
		last_guess = new_guess;
		new_guess = (last_guess + number /last_guess) /2;
		printf("%.15e\n",new_guess);
	}while(new_guess != last_guess);

	printf("Square root of %g is %g\n",number,new_guess);
	
	return EXIT_SUCCESS;
}
