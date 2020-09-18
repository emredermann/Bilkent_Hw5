#include "Person.h"
/*
*Author: Emre Derman
*Date: 01.05.2020
* Id : 21703508
*/
Person::Person()
{
	name = "unknown person";
	id = 0;
	counter = 0;
	connectionHolder = NULL;
	degree = 0;
}
// that part commented due to the errors.
/*
Person::~Person()
{
	delete[] connectionHolder;
}
*/
Person::Person(string name, int Id,int degree)
{
	this->name = name;
	id = Id;
	this->degree = degree;
	connectionHolder = new int[degree];
	counter = 0;
}


Person::Person(const Person& obj)
{
	id = obj.id;
	name = obj.name;
	degree = obj.degree;
}

int Person::getId()
{
	return id;
}

string Person::getName()
{
	return name;
}

void Person::addConnection(int Id)
{
	if (counter < degree) {
		connectionHolder[counter] = Id;
		counter++;
	}
}

int Person::getDegree()
{
	return degree;
}

int Person::getConnection(int location)
{
	if (counter > 0) {
		return connectionHolder[location];
	}
	else
		return -1;
}

