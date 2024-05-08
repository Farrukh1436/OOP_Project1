#pragma once
#include<iostream>
using namespace std;

class user
{
public:
	string name,id,password,gender,user_type;
	unsigned short int age;
	user();
	user(string name, string id, string password, unsigned short int age,
		string gender, string user_type) :name(name), id(id), password(password),
		age(age), gender(gender), user_type(user_type) {}


};
class student:public user
{
public:
	student();
	string group, course_lvl; 
	float gpa;
	student(string name, string id, unsigned short int age,
		string gender,float gpa,string group,string course_lvl) :user(name, id, 
			"NULL", age,
			gender, "Student"), gpa(gpa), group(group), course_lvl(course_lvl) {}

};
class professor : public user
{

private:
	vector<string> subjects;
public:  // Use a pointer to an array of strings
	unsigned int number_subjects;
	professor() {}
	professor(string name, string id, string password, unsigned short int age,
		string gender, string user_type,int number_subjects) :
		user(name, id, password, age, gender, user_type),number_subjects(number_subjects)
	{
		subjects.resize(number_subjects); // Resize the subjects vector
		// Allocate memory for the subjects array
	}
	void get_subject(const string& subject, int index) 
	{
		if (index >= 0 && index < number_subjects)
		{
			subjects[index] = subject; // Store subject at index if within range
		}
		else 
		{
			cout << "Invalid index for subject." << endl;
		}
	}
	vector<string> show_subjects()const
	{
		return subjects;
	}
};