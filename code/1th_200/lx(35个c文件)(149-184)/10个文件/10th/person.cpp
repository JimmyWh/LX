

#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

class Person{
private:
	static int cnt;
	char *name;
	int   age;
 
public:

	static int getCount();
	
	Person(){
		cout << "Person()" << endl;
		name = NULL;
		cnt ++;
	}
	Person(char *name)
	{
		cout << "Person(char *name)" << endl;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name,name);
		cnt ++;
	}
	
	Person(char *name,int age )
	{
		cout << "Persnon(char *,int), name = " << name << ", age  "<<age<<endl;
		this->age = age;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name,name);
		
		cnt ++;
	}

	Person(Person &per)
	{
		cout << "Person &" << endl;
		this->age = per.age;

		this->name = new char[strlen(per.name) + 1];
		strcpy(this->name,per.name);		
		cnt ++;
	
	}


	~Person()
	{
		cout << "~Person()" << endl;
		if (this->name)
		{
			cout << "name = " << name << endl;
			delete this->name;
		}
		
	}

	void setName(char *name)
	{
		if (this->name){
			delete this->name;
		}
		
		this->name = new char[strlen(name) + 1];
		strcpy(this->name,name);
	}

	int  setAge(int  age)
	{
		if (age < 0 || age> 150)
		{
			this->age = 0;
			return -1;
		}
		
		this->age = age;
		return 0;
	}
	
	void printInfo(void)
	{
		
	cout << " name = " << name << " age = " << age << endl;
	}
};

class Student{
private:
	Person father;
	Person mother;
	int student_id;
	
public:
	Student()
	{
		cout << "Student()" <<endl;
	}

	
	Student(int id,char *father,char *mother, int father_age =40,int mother_age = 39):father(father,father_age),mother(mother,mother_age)
	{
		cout << "(int id,char *father,char *mother, int father_age =40,int mother_age = 39)" <<endl;
	}
	
	~Student()
	{
		cout << "~Student()" <<endl;
	}

	
};

int Person::cnt = 0;

int Person::getCount()
{
	//cout << name;
	return cnt;
}


class Student:public Person{
	


};




int main(int agrc,char **argv)
{

	Student s;
	s.setName("zhangsan");
	s.setAge(16);
	s.prinInfo();
	return 0;
}

 




