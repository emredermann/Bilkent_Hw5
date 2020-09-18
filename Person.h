#pragma once
#include<string>
#include<iostream>
using namespace std;
/*
*Author: Emre Derman
*Date: 01.05.2020
* Id : 21703508
*/

class Person
{

public:
	Person();
	// part commented due to the errors.
	//~Person();
	Person(string name, int Id,int degree);
	Person(const Person& obj);
	int getId();
	string getName();
	void addConnection(int);
	int getDegree();
	int getConnection(int);
private:
	int id;
	string name;
	int degree;
	int counter;
	int* connectionHolder;
	};

