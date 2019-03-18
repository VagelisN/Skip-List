#ifndef STUDENT_H
#define STUDENT_H


struct student 
{
	int studid;
	char* lastname;
	char* firstname;
	float gpa;
	int numofcourses;
	char* deprt;
	int postcode;
};

struct student* createstudent(int,char*,char*,float,int,char*,int);
struct student* modify(struct student*,float,int);
void studentprint(struct student*);
void deletestudent(struct student*);

#endif
