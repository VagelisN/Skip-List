#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "hash.h"
#include "list.h"
#include "stucs.h"
#include "skiplist.h"
#define maxlevel 20
#define maxvalue 9999999


struct stucs* initstucs(struct stucs* stu, int hashsize)
{
	stu=malloc(sizeof(struct stucs));
	if(stu==NULL)exit(-2);
	stu->slist=initskip();
	stu->map=initmap(hashsize);
	return stu;
}

void deletestucs(struct stucs* stu)//student deletes are done only by the skiplist to avoid double free
{
	deleteskiplist(stu->slist);
	deletemap(stu->map);
	free(stu);
}
