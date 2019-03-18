#ifndef SKIPLIST_H
#define SKIPLIST_H



struct skipnode
{
	int key;
	struct student* st;
	struct skipnode** fwdptrs;
};

struct skipnode* initskip();
int skipinsert(struct skipnode*,struct student*);
struct student* skipsearch(struct skipnode* ,int);
void computeavg(struct skipnode* ,int,int);
void skipprint(struct skipnode*);
struct student* retdeleteskipnode(struct skipnode* , int);
void findgpa(struct skipnode*,float);
void bottom(struct skipnode*,int);
void percentilles(struct skipnode*,int);
void deleteskiplist(struct skipnode*);


#endif

