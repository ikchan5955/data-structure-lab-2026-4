#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pet {
protected:
	string name;
	int age;
	string type;

public:
	//생성자 함수
	Pet(string n, int a, string t)
		: name(n), age(a), type(t) {
	}
	string getName() {
		return name;
	}
	int getAge() {
		return age;
	}
	string getType() {
		return type;
	}
};

class Puppy : public Pet {
private:
	string breed;
public:
	Puppy(string n, int a, string t, string b)
		: Pet(n, a, t), breed(b) {
	}
	string getBreed() {
		return breed; 
	}

};