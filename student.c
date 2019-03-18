#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"


struct student* createstudent(int studid,char* lastname,char* firstname,float gpa,int numofcourses,char* deprt,int postcode)
{
	if(postcode<10000 ||postcode>99999)
	{
		fprintf(stderr,"postcode given is not valid\n");
		return NULL;
	}
	if(numofcourses<0 ||numofcourses>52)
	{
		fprintf(stderr,"numofcourses given is not valid\n");
		return NULL;
	}
	struct student *st =malloc(sizeof(struct student));
	if(st==NULL)exit(-2);
	st->studid=studid;
	st->lastname=malloc(sizeof(char)*(strlen(lastname)+1));
	if(st->lastname==NULL)exit(-2);
	strcpy(st->lastname,lastname);
	st->firstname=malloc(sizeof(char)*(strlen(firstname)+1));
	if(st->firstname==NULL)exit(-2);
	strcpy(st->firstname,firstname);
	st->gpa=gpa;
	st->numofcourses=numofcourses;
	st->deprt=malloc(sizeof(char)*(strlen(deprt)+1));
	if(st->deprt==NULL)exit(-2);
	strcpy(st->deprt,deprt);
	st->postcode=postcode;
	return st;
}

void studentprint(struct student*st)
{
	if(st!=NULL) printf("%d %s %s %.2f %d %s %d\n",st->studid,st->lastname,st->firstname,st->gpa,st->numofcourses,st->deprt,st->postcode);
}

struct student* modify(struct student* st,float gpa,int numofcourses)
{
	if (st==NULL)
	{
		fprintf(stderr,"cant modify a NULL student\n");
		return NULL;
	}
	if(numofcourses<0 ||numofcourses>52)
	{
		fprintf(stderr,"numofcourses given is not valid\n");
		return NULL;
	}
	st->gpa=gpa;
	st->numofcourses=numofcourses;
	return st;
}

void deletestudent(struct student* st)
{
	if (st!=NULL)
	{
		if(st->lastname!=NULL) 
		{
			free(st->lastname);
			st->lastname=NULL;
		}
		if(st->firstname!=NULL) 
		{
			free(st->firstname);
			st->firstname=NULL;
		}
		if(st->deprt!=NULL)
		{
			free(st->deprt);
			st->deprt=NULL;
		}
		free(st);
		st=NULL;	
	}
}
