#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;



class Person {

public:
	Person() : name(""), address("") { };
	Person(string n, string a) : name(n), address(a) { }
	Person(string n) : name(n) { }
	explicit Person(std::istream& is) { read(is); }

	string GetName() const { return name; }
	string getAddress() const { return address; }

	std::ostream& print(std::ostream& os = cout);
	std::istream& read(std::istream& is = cin);




private:
	string name;
	string address;
};


#endif