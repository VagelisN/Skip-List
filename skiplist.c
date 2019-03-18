#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"
#include "student.h"
#define maxlevel 20
#define maxvalue 9999999


struct skipnode* initskip()//initialize skip list
{
	struct skipnode *temphead ,*tempterm;
	int i;
	temphead=malloc(sizeof(struct skipnode));
	if(temphead==NULL)exit(-2);
	tempterm=malloc(sizeof(struct skipnode));
	if(tempterm==NULL)exit(-2);
	temphead->st=NULL;
	temphead->fwdptrs=malloc(maxvalue*sizeof(struct skipnode*));//dynamically allocated array to store forward pointers
	if(temphead->fwdptrs==NULL)exit(-2);
	temphead->key=0;
	for (i = 0; i <maxlevel ; i++)//all head forward pointers point to terminating node 
	{
		temphead->fwdptrs[i]=tempterm;
	}
	tempterm->key=maxvalue;//term node has the max value 
	tempterm->st=NULL;
	return temphead;
}

int skipinsert(struct skipnode* head ,struct student* st)//insert student to skiplist
{
	int key = st->studid;
	struct skipnode* update[maxlevel];//array to keep all nodes previous to the node to be inserted for each level
	struct skipnode* temp;
	temp=head;
	int i;
	for (i = maxlevel-1; i >=0 ; i--)
	{
		
		while(temp->fwdptrs[i]->key<key)//set update array
		{
			temp=temp->fwdptrs[i];
		}
		update[i]=temp;
	}
	temp=temp->fwdptrs[0];//get the next node to see if st is already in the list
	if (temp->key==key)
	{
		fprintf(stderr,"studid already in the list \n");
		return 1;
	}
	
	int level=rand()%maxlevel;//level of new node is a random number from 0 to maxlevel-1
	temp=malloc(sizeof(struct skipnode));
	if(temp==NULL)exit(-2);
	temp->fwdptrs=malloc(maxlevel*sizeof(struct skipnode*));
	if(temp->fwdptrs==NULL)exit(-2);
	temp->key=key;
	temp->st=st;
	for (i = 0; i <=level; i++)//set the new node's pointers with the help of update
	{
		temp->fwdptrs[i]=update[i]->fwdptrs[i];
		update[i]->fwdptrs[i]=temp;
	}
	return 0;
}

struct student* skipsearch(struct skipnode* head ,int key)
{
	if(head==NULL)
	{
		fprintf(stderr,"NULL skip list given\n");
		return NULL;
	}
	struct skipnode* temp=head;
	int i;
	for (i = maxlevel-1; i >=0 ; i--)//start looking for the key in each level of nodes 
	{
		while(temp->fwdptrs[i]->key <key)
		{
			temp=temp->fwdptrs[i];
		}
	}
	temp=temp->fwdptrs[0];
	if (temp->key==key)
	{
		return temp->st;
	}
	else 
	{
		fprintf(stderr,"not found\n");
		return NULL;
	}
}

void computeavg(struct skipnode* head ,int studida,int studidb)
{
	if(head!=NULL)
	{
		struct skipnode* temp=head;
		int i,count=0;
		float sum;
		for (i = maxlevel-1; i >=0 ; i--)//find studida or the one with the closest value 
		{
			while(temp->fwdptrs[i]->key <studida)
			{
				temp=temp->fwdptrs[i];
			}
		}
		temp=temp->fwdptrs[0];
		if(temp->key==maxvalue)fprintf(stderr,"not found\n");
		else
		{
			if(temp->key<=studidb)//if the one closest to studida is greater than studidb then it must be omitted
			{
				 count=1;
				 sum=temp->st->gpa;
			}
			while(temp->fwdptrs[0]->key<=studidb)
			{
				count++;
				temp=temp->fwdptrs[0];
				sum+=temp->st->gpa;			
			}
			temp=temp->fwdptrs[0];
			if(count==0) fprintf(stderr,"not found\n");
			else printf("%.2f\n",(sum/count));
		}
	}
	else fprintf(stderr,"empty skiplist given\n");
}

void skipprint(struct skipnode* head)//just print the whole list by using level 0(not used)
{
	if(head!=NULL)
	{
		head=head->fwdptrs[0];
		while(head->key!=maxvalue)
		{
			studentprint(head->st);
			head=head->fwdptrs[0];
		}
	}
}


struct student* retdeleteskipnode(struct skipnode* head, int key)//returns the student to be deleted and does all the rest
{	
	
	if (head==NULL)
	{ 
		fprintf(stderr,"empty list given\n");
		return NULL;
	}
	else
	{
		struct student* retval;
		struct skipnode* temp=head;
		struct skipnode* update[maxlevel];
		int i;
		for (i = maxlevel-1; i >=0 ; i--)
		{
			while (temp->fwdptrs[i]->key<key)
			{
				temp=temp->fwdptrs[i];
			}
			update[i]=temp;
		}
		temp=temp->fwdptrs[0];/*phgainw ston komvo pou thelw na diagrapsw*/
		if(temp->key!=key)
		{
			fprintf(stderr,"not found\n");
			retval =NULL;
			return retval;
		}
		for (i = 0; i <=maxlevel-1 ; i++)
		{
			if (update[i]->fwdptrs[i]==temp)
			{
				update[i]->fwdptrs[i]=temp->fwdptrs[i];
			}
		}
		retval=temp->st;
		temp->st=NULL;
		free(temp->fwdptrs);
		free(temp);
		temp=NULL;
		return retval;
	}
}

void findgpa(struct skipnode* head,float gpa)
{
	int maxnumofcourses=0;
	struct skipnode* temp=head;
	if(temp!=NULL)
	{
		while(temp->key!=maxvalue)//find the max number of courses that someone needs to take
		{
			if(temp->st!=NULL)
			{
				if(temp->st->numofcourses>maxnumofcourses && temp->st->gpa>gpa) maxnumofcourses=temp->st->numofcourses;
			}
			temp=temp->fwdptrs[0];
			
		}
		int counter=0;
		while(head->key!=maxvalue)// print everyone that needs to take the same amount of courses and has a greater gpa than the one given 
		{	
			if(head->st!=NULL)		
			{
				if((head->st->numofcourses==maxnumofcourses )&&(head->st->gpa>gpa))
				{
					counter++;
					studentprint(head->st);
				}
			}
			head=head->fwdptrs[0]; 
		}
		if(counter==0) fprintf(stderr,"no students found\n");
	}
	else fprintf(stderr,"uninitialized skip list given\n");
}

void bottom(struct skipnode*head,int k)
{
	int maxplace=0;
	int i =0,j,z;
	float maxgpa=0.0;
	struct student **starray =malloc(k*sizeof(struct student*));
	if(starray==NULL)exit(-2);
	head=head->fwdptrs[0];
	while(head->key!=maxvalue)
	{
			if(i<k)//while the k elements are not filled, fill them with any student found 
			{
				if(head->st!=NULL)starray[i]=head->st;
				if(starray[i]->gpa>maxgpa)//if someone has a bigger gpa than the previous max change the maxgpa and its position
				{
					maxgpa=starray[i]->gpa;
					maxplace=i;
				}
				i++;	
			}
			else
			{
				if(head->st->gpa<maxgpa)//everytime a student that has a smaller gpa than maxgpa it takes its place 
				{
					starray[maxplace]=head->st;
					maxgpa=0.0;
					for (j = 0; j < i; j++)//and the new maxgpa has to be found 
					{
						if(starray[j]->gpa>maxgpa)
						{
							maxgpa=starray[j]->gpa;
							maxplace=j;
						}
					}
				}
				
			}
			head=head->fwdptrs[0];
	}
	struct student* swap;//bubblesort from http://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
	for (j = 0 ; j < (i-1); j++)
	{
		for (z = 0 ; z < i -j-1 ; z++)
		{
			if (starray[z]->gpa > starray[z+1]->gpa) 
			{
				swap = starray[z];
				starray[z] = starray[z+1];
				starray[z+1] = swap;
			}
		}
	}
	for (j = 0; j <i ; j++)//print the students found 
	{
		studentprint(starray[j]);
	}
	if(i==0)fprintf(stderr,"no students inserted\n");
	free(starray);	
}

void percentilles(struct skipnode*head, int size)//array with two collumns. left has the postcode right has the number of students in it
{
	int **postarray=NULL;
	int **temparray=NULL;
	int i,k=0,foundflag=1,arraysize=30;
	postarray=malloc(arraysize*sizeof(int*));
	if(postarray==NULL)exit(-2);
	for (i = 0; i < arraysize; i++)
	{
		postarray[i]=malloc(2*sizeof(int));
		if(postarray[i]==NULL)exit(-2);
	}
	for (i = 0; i <arraysize ; i++)//initialize with zeros (postcodes are five digit numbers)
	{
		postarray[i][0]=0;
		postarray[i][1]=0;
	}
	head=head->fwdptrs[0];//skip head node of the skiplist
	while(head->key!=maxvalue)
	{
		foundflag=1;
		for (i = 0; i <k; i++)//if the students postcode is in the array just increase its counter
		{
			if(postarray[i][0]==head->st->postcode)
			{
				postarray[i][1]++;
				foundflag=0;
			}
		}
		if(foundflag==1)//it wasnt found
		{
			
			postarray[k][0]=head->st->postcode;//put the postcode at the end of the array
			postarray[k][1]++;
			k++;//increase the position of the last element of the array
			if(k==arraysize)//array was filled reallocate the array using temparray
			{
				temparray=malloc(arraysize*sizeof(int*));
				if(temparray==NULL)exit(-2);
				for (i = 0; i < arraysize; i++)
				{
					temparray[i]=malloc(2*sizeof(int));
					if(temparray[i]==NULL)exit(-2);
				}
				for (i = 0; i <arraysize ; i++)
				{
					temparray[i][0]=postarray[i][0];
					temparray[i][1]=postarray[i][1];
				}
				for (i = 0; i <arraysize ; i++)
				{
					free(postarray[i]);
					postarray[i]=NULL;
				}
				free(postarray);
				postarray=NULL;
				arraysize*=2;
				postarray=malloc(arraysize*sizeof(int*));
				if(postarray==NULL)exit(-2);
				for (i = 0; i <arraysize; i++)
				{
					postarray[i]=malloc(2*sizeof(int));
					if(postarray[i]==NULL)exit(-2);
				}
				for (i = 0; i <arraysize ; i++)
				{
					postarray[i][0]=0;
					postarray[i][1]=0;
				}
				for (i = 0; i <k; i++)
				{
					postarray[i][0]=temparray[i][0];
					postarray[i][1]=temparray[i][1];
				}
				for (i = 0; i <k ; i++)
				{
					free(temparray[i]);
					temparray[i]=NULL;
				}
				free(temparray);
				temparray=NULL;
			}
		}
		head=head->fwdptrs[0];
	}
	for (i = 0; i <k ; i++)//print the percentage for each postcode
	{
		printf("%d %.2f\n",postarray[i][0],postarray[i][1]/(float)size);
	}
	for (i = 0; i <arraysize ; i++)
	{
		free(postarray[i]);
		postarray[i]=NULL;
	}
	free(postarray);
	postarray=NULL;
}

void deleteskiplist(struct skipnode*head)
{
	if(head!=NULL)
	{	
		struct skipnode* temp=head;
		while(temp->key!=maxvalue)
		{
			head=temp;
			temp=temp->fwdptrs[0];
			deletestudent(head->st);
			head->st=NULL;
			free(head->fwdptrs);
			free(head);
			head=NULL;
		}
		free(temp);//terminating node was not deleted in the previous loop and has no fwdptrs allocated 
		temp=NULL;
	}
}
