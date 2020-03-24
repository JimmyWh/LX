#include <stdio.h>

typedef struct a {
	int a[5];
	char name[20];
}p_str;

int main()
{
	p_str *p = NULL;
	printf("a = %p\n",&p->a);
	printf("name = %p\n",&p->name);
	return 0;
}

