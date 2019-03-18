#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "hash.h"
#include "list.h"


struct hashmap* initmap(int size)//initialize the hashmap
{
	struct hashmap* temp = malloc(sizeof(struct hashmap));
	if(temp==NULL)exit(-2);
	temp->mapsize=size;
	temp->nofelements=0;
	temp->entries=malloc(size*sizeof(struct listnode*));//create a list in each hashmap cell
	if(temp->entries==NULL)exit(-2);
	int i ;
	for (i = 0; i <size ; i++)
	{
		temp->entries[i]=NULL;
	}
	
	return temp;
}


void deletemap(struct hashmap* map)//deletes the whole map
{
	int i;
	for (i = 0; i <map->mapsize; i++)
	{
		if(map->entries[i]!=NULL)//for each list that was used delete all its items
		{
			 deletelist(map->entries[i]);
			 map->entries[i]=NULL;
		}
	}
	if(map->entries!=NULL)free(map->entries);//delete the cells
	if(map!=NULL)free(map);//delete the map
	map=NULL;
}

int hashfun(struct hashmap* map ,int postcode)//the simple hash function 
{
	int place =postcode%map->mapsize;
	return place;
}

void hashinsert(struct hashmap* map, struct student* st)//insert a student to the right list
{
	if (st==NULL) fprintf(stderr,"NULL student \n");
	int place=hashfun(map,st->postcode);//find the list
	map->entries[place]=listinsert(map->entries[place],st);//insert it in the list
	if(map->entries[place]!=NULL)map->nofelements++;//if it was succesfuly inserted increase the number of elements in the map
}

void deletehashelem(struct hashmap* map,struct student* st)//delete a single element
{
	if(st!=NULL && map!=NULL)
	{
		int error=0;
		int place=hashfun(map,st->postcode);//find in which list it might belong
		map->entries[place]=deletelistnode(map->entries[place],st->studid,&error);//deletehim if found
		if(error!=1)map->nofelements--;//decrease the number of elements in the list
	}
}

void hashprint(struct hashmap*map)//print the whole map(not used)
{
	if(map!=NULL)
	{
		int i;
		for (i = 0; i <map->mapsize ; i++)
		{
			if(map->entries[i]!=NULL) printlist(map->entries[i]);
		}
	}
}


void hashcomputeavg(struct hashmap* map,int postcode)//just calls the listcomputeavg for the correct list 
{
	int place=hashfun(map,postcode);
	listcomputeavg(map->entries[place],postcode);
}

void hashcoursestotake(struct hashmap* map,int postcode,char* deprt)//just calls the coursestotake for the correct list
{
	int place =hashfun(map,postcode);
	coursestotake(map->entries[place],postcode,deprt);		
}


void percentille(struct hashmap*map,int postcode)
{

		int place=hashfun(map,postcode);//find where is postcode
		int count=countstudents(map->entries[place],postcode);//count the students 
		if(count==0)fprintf(stderr,"no students in this area\n");
		else
		{
			float temp =count/(float)(map->nofelements);//compute their percentage
			printf("%.2f\n",temp);
		}
}

void taverage(struct hashmap*map ,int k, int postcode)//just calls the listtaverage for the correct list
{
	int place=hashfun(map,postcode);
	listtaverage(map->entries[place],k,postcode);
}
