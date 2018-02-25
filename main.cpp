#include <iostream>
#include <thread>
#include <stdlib.h>
#include <unistd.h>
#define clear() printf("\033[H\033[J")

using namespace std;

class Person
{
	float weight;
	int age;
	double size;
	string name;
public:
	Person(float weight, int age, string name)
	{
		this->weight = weight;
		this->age = age;
		this->name = name;
	}

	float getWeight()
	{
		return weight;
	}

	int getAge()
	{
		return age;
	}

	string getName()
	{
		return name;
	}

	int getSize()
	{
		this->size = name.length();
		return name.length();
	}

	void print()
	{
		cout << weight << endl;
		cout << age << endl;
		cout << name << endl;
	}
};

void serialize(Person* person, char* data);
void deserialize(Person* person, char* data);

int main()
{
	Person person(10.2, 20, "Joseph");
	// initializing data with Person's size + the string length, size it's
	// dynamic and we don't know the size of it, before its first usage.
	char data[(sizeof(Person)+person.getSize())];

	cout << "size: " << sizeof(double) << endl;
	serialize(&person, data);
	deserialize(&person, data);
}

void serialize(Person* person, char* data)
{
    /* point the new f pointer to the first block of the data char pointer
    data[weight(size 4)][age (size 4][size][name]


    */

	float* f = (float*)data;
	*f = person->getWeight(); f++;
    int* g = (int*)f;
	*g = person->getAge(); g++;
	double* h = (double*)g;
	*h = person->getSize(); h++;

	char* c = (char*)h;

	for (auto& x: person->getName())
	{
		*c = x;
		c++;
	}
}

void deserialize(Person* person, char* data)
{
	float weight;
	int age;
	double size;
	string name;

	float* f = (float*)data;
	weight = *f; f++;
	int* g = (int*)f;
	age = *g; g++;
	double* h = (double*)g;
	size = *h; h++;
	char* n = (char*)h;

	for (int x=0; x<size; x++)
	{
		name+= *n;
		n++;
	}

	person = new Person(weight, age, name);

	person->print();
}
