#ifndef HASH_H
#define HASH_H


struct hashmap
{
	struct listnode** entries;
	int mapsize,nofelements;
};

struct hashmap* initmap(int);
void deletemap(struct hashmap*);
int hashfun(struct hashmap* ,int);
void hashinsert(struct hashmap* , struct student*);
void hashprint(struct hashmap*);
void deletehashelem(struct hashmap*,struct student*);
void hashcomputeavg(struct hashmap*,int );
void hashcoursestotake(struct hashmap*,int,char*);
void percentille(struct hashmap*,int);
void taverage(struct hashmap*,int,int);

#endif


