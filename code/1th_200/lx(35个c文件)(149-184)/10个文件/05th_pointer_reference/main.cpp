

#include <iostream>

using namespace std;

int add_one(int a)
{
	a = a +1;
	return a;
}

int add_one(int *a)
{
	*a = *a + 1;
	return *a;
}

int add_one_refer(int &b)
{
	b = b +1;
	return b;
}

int main(int argc,char **argv)
{
	int a = 99;
	cout << add_one(a) <<endl;
	cout << "a = " << a <<endl;

	cout << add_one(&a) <<endl;
	cout << "a = " << a <<endl;

	
	cout << add_one_refer(a) <<endl;
	cout << "a = " << a <<endl;

	return 0;
}


