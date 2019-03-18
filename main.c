#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"
#include "list.h"
#include "hash.h"
#include "skiplist.h"
#include "stucs.h"

int main(int argc, char *argv[])
{
	int hashsize;
	char* filename=NULL;
	if(argc==3)
	{
		if(strcmp(argv[1],"-b")==0)
		{
			hashsize=atoi(argv[2]);//1 arguement is given
			if(hashsize<=0)
			{
				fprintf(stderr,"hashmap size needs to be at least 1\n");
				exit(-1);
			}
		}
		else
		{
			fprintf(stderr,"command line arguements: -b to set hashmap size -l to set inputfile\n");
			exit(-1);
		}
	}
	else if(argc==5)//or else 2 arguements are given 
	{
		if(strcmp(argv[1],"-b")==0)
		{
			if(strcmp(argv[3],"-l")==0)
			{
				hashsize=atoi(argv[2]);
				if(hashsize<=0)
				{
					fprintf(stderr,"hashmap size needs to be at least 1\n");
					exit(-1);
				}
				filename=malloc(sizeof(char)*(strlen(argv[4])+1));
				if(filename==NULL)exit(-2);
				strcpy(filename,argv[4]);			
			}
			else
			{
				fprintf(stderr,"command line arguements: -b to set hashmap size -l to set inputfile\n");
				exit(-1);
			}
		}
		else if(strcmp(argv[1],"-l")==0)
		{
			if(strcmp(argv[3],"-b")==0)
			{
				hashsize=atoi(argv[4]);
				if(hashsize<=0)
				{
					fprintf(stderr,"hashmap size needs to be at least 1\n");
					exit(-1);
				}
				filename=malloc(sizeof(char)*(strlen(argv[2])+1));
				if(filename==NULL)exit(-2);
				strcpy(filename,argv[2]);
			}
			else
			{
				fprintf(stderr,"command line arguements: -b to set hashmap size -l to set inputfile\n");
				exit(-1);
			}	
		}
		else
		{
			fprintf(stderr,"command line arguements: -b to set hashmap size -l to set inputfile\n");
			exit(-1);
		}
	}
	else
	{
		fprintf(stderr,"command line arguements: -b to set hashmap size -l to set inputfile\n");
		exit(-1);
	}
	FILE*fp;
	char *tok=NULL;
	char* line=NULL;
	size_t len =0;
	char* tokar[8]={NULL};
	int i,exitflag=1;
	struct student* st=NULL;
	struct stucs* stu=NULL;
	srand(time(NULL));
	fp=fopen(filename,"r");
	if(filename!=NULL) free(filename);//open filename given
	if(fp==NULL)//if no file given read from stdin
	{
		//fprintf(stderr,"No valid file given as arguement! Give the instructions manually \n");
		fp =stdin;
	}
	stu=initstucs(stu,hashsize);
	int counter=0;
	char ch;
	while ((getline(&line, &len, fp)) != -1)
	{
		ch=line[0];
		if(ch!='i') fprintf(stderr,"%s",line);
		for(tok=strtok(line," \n");tok!=NULL; tok=strtok(NULL," \n"))//split input in tokens
		{
			tokar[counter]=malloc(sizeof(char)*(strlen(tok)+1));
			if(tokar[counter]==NULL)exit(-2);
			strcpy(tokar[counter],tok);
			counter++;
		}
	
		if(tokar[0]!=NULL)//if input not empty 
		{
			if(strcmp(tokar[0],"i")==0)//create the student and insert it to the structs
			{
				if(counter==8)
				{	
					st=createstudent(atoi(tokar[1]),tokar[2],tokar[3],atof(tokar[4]),atoi(tokar[5]),tokar[6],atoi(tokar[7]));
					studentprint(st);
					if(st!=NULL)
					{
						if(skipinsert(stu->slist,st)==0)
						{
							 hashinsert(stu->map,st);//only if it was succesfuly inserted in the skiplist insert it to the map
						}
						else deletestudent(st);//if already int the list delete it 
					}
						
				}
				else fprintf(stderr,"i has 7 arguements\n");
			}
			else if(strcmp(tokar[0],"q")==0)//find the student
			{
				if(counter==2)
				{
					st=skipsearch(stu->slist,atoi(tokar[1]));
					studentprint(st);
				}
				else fprintf(stderr,"q has 1 arguement\n");
			}
			
			else if(strcmp(tokar[0],"m")==0)//modify the student
			{
				if(counter==4)
				{
					st=skipsearch(stu->slist,atoi(tokar[1]));
					if(st!=NULL)
					{
						st=modify(st,atof(tokar[2]),atoi(tokar[3]));
						studentprint(st);
					}
					else fprintf(stderr,"not found\n");
				}
				else fprintf(stderr,"m has 3 arguements\n");
			}
			else if(strcmp(tokar[0],"d")==0)//delete the student
			{
				if(counter==2)
				{
					st=NULL;
					st=retdeleteskipnode(stu->slist,atoi(tokar[1]));//return the student before deleting it in order to find it in the hashmap
					studentprint(st);
					if(st!=NULL);
					{	
						deletehashelem(stu->map,st);
						deletestudent(st);//if also found in the hashmap delete it	
					}
				}
				else fprintf(stderr,"d has 2 arguements\n");
			}
			else if(strcmp(tokar[0],"ra")==0)//compute average gpa of students between studida and studidb
			{
				if( counter ==3)
				{
					if(atoi(tokar[2])>atoi(tokar[1]))
					{	
						computeavg(stu->slist,atoi(tokar[1]),atoi(tokar[2]));
					}
					else fprintf(stderr,"arguement 1 of ra has to be bigger than arguement 2\n");
				}
				else fprintf(stderr,"ra has 2 arguements\n"); 
			}
			
			else if(strcmp(tokar[0],"a")==0)//coumpute average gpa of students that live in postcode
			{
				if(counter==2) hashcomputeavg(stu->map,atoi(tokar[1]));
				else fprintf(stderr,"a has 1 arguement\n");
			}
			
			else if(strcmp(tokar[0],"ta")==0)//find the k best students tha live in postcode
			{
				if(counter==3)taverage(stu->map,atoi(tokar[1]),atoi(tokar[2]));
				else fprintf(stderr,"ta has 2 arguements\n");
			}
			
			else if(strcmp(tokar[0],"b")==0)//find the k worst students of EKPA
			{
				if(counter==2)bottom(stu->slist,atoi(tokar[1]));
				else fprintf(stderr,"b has 1 arguement\n");
			}
			
			else if(strcmp(tokar[0],"ct")==0)//show all the students tha live in postcode study in deprt and the courses they need to take
			{
				if(counter==3) hashcoursestotake(stu->map,atoi(tokar[1]),tokar[2]);
				else fprintf(stderr,"ct has 2 arguements\n");
			}
			else if(strcmp(tokar[0],"f")==0)//show all students that need to take the max number of courses and their gpa is > than gpa given
			{
				if(counter==2)findgpa(stu->slist,atof(tokar[1]));
				else fprintf(stderr,"f has 1 arguement\n");
			}
			
			else if(strcmp(tokar[0],"p")==0)//compute the percentage of students that live in postcode
			{ 
				if(counter==2)percentille(stu->map,atoi(tokar[1]));
				else fprintf(stderr,"p has 1 arguement\n");
			}
			else if(strcmp(tokar[0],"pe")==0)//for every postcode compute the average of students that live in it
			{
				if(counter==1)percentilles(stu->slist,stu->map->nofelements);
				else fprintf(stderr,"pe has no arguements\n");
			}
			
			else if(strcmp(tokar[0],"e")==0)//exit
			{
				if(counter==1)
				{
					deletestucs(stu);
					exitflag=0;
				}
				else fprintf(stderr,"e has no arguements\n");	
			}
			else
			{
				fprintf(stderr,"wrong command given \n");
			}
		}
		else
		{
			fprintf(stderr,"wrong command given \n");
		}
		for(i =0; i <counter; i++)
		{
			free(tokar[i]);
			tokar[i]=NULL;
		}
		counter=0;
		if (exitflag==0)break;
	}
	free(line);
	line=NULL;
	if(fp!=NULL) fclose(fp);
	return 0;
}
