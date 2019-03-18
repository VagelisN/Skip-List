#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "list.h"

struct listnode* listinsert(struct listnode* head , struct student* st)//insert at start O(1)
{
	if(head==NULL)//if no elements are in the list
	{
		head=malloc(sizeof(struct listnode));
		if (head==NULL)exit(-2);
		head->st=st;
		head->next=NULL;
		return head;
	}
	else
	{
		struct listnode* temp=head;
		if(temp->next==NULL)//if only one is in the list
		{
			temp->next=malloc(sizeof(struct listnode));
			if (temp==NULL)	exit(-2);
			temp->next->st=st;
			temp->next->next=NULL;
			return head;
		}
		else//any other occasion
		{
			struct listnode* temp2=malloc(sizeof(struct listnode));
			temp2->st=st;
			temp2->next=temp->next;
			temp->next=temp2;
			return head;
		}

	}
}


void printlist(struct listnode* head)//print all the elements of the list
{
	if (head==NULL)
	{
		fprintf(stderr,"empty list given\n");
		return;
	}
	while(head->next!= NULL)
	{
		studentprint(head->st);
		head=head->next;
	}
	studentprint(head->st);
	
}

struct listnode* deletelistnode(struct listnode* head, int studid,int* error)
{
	struct listnode *temp=head;
	if(head->st->studid==studid)//in this occasion the deletes are done by the skiplist so to avoid double free the list deletess are commented
	{
		head=head->next;//delete head
		//deletestudent(temp->st);
		free(temp);
		return head;
	}
	else
	{
		struct listnode *temp=head , *starttemp=head;	
		while(head!=NULL&&head->st->studid!=studid)//traverse the list until studid is found 
		{
				temp=head;
				head=head->next;
		}
		if (head->st->studid==studid)/*its found*/
		{
			temp->next=head->next;
			//deletestudent(head->st);
			free(head);
			return starttemp;
		}
		else
		{
			fprintf(stderr,"student id not int the list\n");
			*error=1;
			return head;
		}
	}
}

void listcomputeavg(struct listnode* head,int postcode)//compute the average gpa of the students that live in postcode
{
	if(head==NULL)
	{
		fprintf(stderr,"no students with this postcode\n");
	}
	else
	{
		int count=0;
		float sum=0;
		while(head!=NULL)
		{
			if(head->st->postcode==postcode)//other postcodes might hash in the same position .skip them
			{
				count++;
				sum+=head->st->gpa;
			}
			head=head->next;
		}
		printf("%.2f\n",(sum/count));
	}
}

void coursestotake(struct listnode* head, int postcode ,char* deprt)//find all the students that live in postcode and study at deprt and compute the courses they need to take 
{
	int counter=0,sum=0;
	if(head==NULL)
	{
		fprintf(stderr,"not found\n");
		return;
	}
	while(head!=NULL)
	{
		
		if(head->st->postcode==postcode)//other postcodes might hash in the same position
		{	
			if(strcmp(head->st->deprt,deprt)==0)//if he lives in postcode if he studies in deprt
			{	
				counter++;//counter is used in the end to tell if there where no students meeting the requirements
				studentprint(head->st);
				sum+=head->st->numofcourses;
			}	
		}
		head=head->next;
	}
	if(counter==0)fprintf(stderr,"not found\n");
	else printf("%d\n",sum);
}


int countstudents(struct listnode* head,int postcode)//counts how many students live in postcode 
{
	int count=0;
	while(head!=NULL)
	{
		if(head->st->postcode==postcode)count++;
		head=head->next;
		
	}
	return count;
}



void listtaverage(struct listnode* head,int k,int postcode)//finds the k best students that live in postcode  O(n*k)
{
	if(head==NULL)
	{
		fprintf(stderr,"not found\n");
		return;
	}
	struct student **starray=malloc(k*sizeof(struct student*));//create an array with k places 
	int minplace=0;
	int i=0,j,z;
	float mingpa=110.0;
	while(head!=NULL)
	{
		if(head->st->postcode==postcode)//other postcodes might hash in the same position
		{
			if(i<k)//fills the array kith the first students it finds 
			{
				starray[i]=head->st;
				if(starray[i]->gpa<mingpa)//computes the minimum and finds its place
				{
					mingpa=starray[i]->gpa;
					minplace=i;
				}
				i++;	
			}
			else//k places are filled 
			{
				if(head->st->gpa>mingpa)//a student enters the array if its bigger than the minimum 
				{
					starray[minplace]=head->st;
					mingpa=11.0;
					for (j = 0; j < i; j++)//new minimum is computed
					{
						if(starray[j]->gpa<mingpa)
						{
							mingpa=starray[j]->gpa;
							minplace=j;
						}
					}
				}
				
			}
		}
		head=head->next;
	}
	struct student* swap;//bubblesort from http://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
	for (j = 0 ; j < (i-1); j++)
	{
		for (z = 0 ; z < i -j-1 ; z++)
		{
			if (starray[z]->gpa < starray[z+1]->gpa) 
			{
				swap = starray[z];
				starray[z] = starray[z+1];
				starray[z+1] = swap;
			}
		}
	}
	

	for (j = 0; j <i ; j++)
	{
		studentprint(starray[j]);
	}
	free(starray);
}

void deletelist(struct listnode* head)//in this occasion the deletes are done only by the skiplist to avoid double free
{
	if(head!=NULL)
	{
		struct listnode *temp;
		while(head->next!=NULL)
		{
			temp=head;
			head=head->next;
			//deletestudent(temp->st);
			temp->st=NULL;
			free(temp);
		}
		temp=NULL;
		//deletestudent(head->st);
		head->st=NULL;//delete the last node
		free(head);
		head=NULL;
	}
}
