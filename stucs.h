#ifndef STUCS_H
#define STUCS_H

struct stucs
{
	struct skipnode* slist;
	struct hashmap* map;
};

struct stucs* initstucs(struct stucs* ,int);
void deletestucs(struct stucs*);


#endif
