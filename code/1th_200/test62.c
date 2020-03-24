#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float new_Guess,old_Guess,number;

	printf("Please enter the number : ");
	scanf("%f",&number);

	if (number < 0)
	{
		printf("the number err!\n");
		return EXIT_FAILURE;
	}
	
	new_Guess = 1;
	do{
		old_Guess = new_Guess;
		new_Guess = (old_Guess + number / old_Guess)/2;
		printf("%.15e\n",new_Guess);
	}while(old_Guess != new_Guess);

	printf("Squre root of %g is %g\n",number,new_Guess);
	return EXIT_SUCCESS;
}

