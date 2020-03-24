#include <stdio.h>

int main()
{
	enum Color{red,yellow,blue,white,black};
	enum Color i,j,k,pri;
	int n,loop;
	n = 0;
	for (i =red; i <= black;i++)
	{
		for (j= red;j <=black;j++)
		{
			if (i!=j)
			{
				for(k=red;k<=black;k++)
				if ((k!=i) &&(k!=j))
				{
					n = n + 1;
					printf("%-4d",n);
					for (loop =1;loop <=3;loop++)
					{

						switch (loop)
						{
						  case  1:
						  	pri = i;
							break;

							case  2:
						  	pri = j;
							break;

							case  3:
						  	pri = k;
							break;

							default:
								break;
						}
					}

					switch (pri)
					{
					 case red:
					 	printf("%d",red);
						break;

					case yellow:
					   printf("%d",yellow);
					   break;

					case blue:
					   printf("%d",blue);
					   break;
					   
					case white:
					   printf("%d",white);
					   break;

					case black:
					   printf("%d",black);
					   break;

					default:
						break;
					   
							
					}
				}
			}
			
			printf("\n");
		}	
	}
	printf("\ntotal :%5d\n",n);
	return 0;

}
