#ifndef LIST_H
#define LIST_H




struct listnode
{
	struct student* st;
	struct listnode* next;
};

struct listnode* listinsert(struct listnode* , struct student* );
struct listnode* listinsertbypcode(struct listnode*, struct student*);
void printlist(struct listnode*);
struct listnode* deletelistnode(struct listnode*,int,int*);
void listcomputeavg(struct listnode*,int);
void coursestotake(struct listnode*, int ,char*);
int countstudents(struct listnode*,int);
void listtaverage(struct listnode*,int,int);
void deletelist(struct listnode*);


#endif
