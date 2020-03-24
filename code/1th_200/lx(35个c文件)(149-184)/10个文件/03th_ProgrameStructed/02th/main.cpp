
#include <stdio.h>
#include "Person.h"
#include "Dog.h"

using namespace A;
using namespace C;



int main(int argc,char **argv)
{
	Person per;
	per.setName("zhangsan");
	per.setAge(16);
	per.printInfo();

	Dog dog;
	dog.setName("wangcai");
	dog.setAge(1);
	
	A::printVersion();
	C::printVersion();
	return 0;
}
