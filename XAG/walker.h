#ifndef WALKER_H_INCLUDED
#define WALKER_H_INCLUDED

#include "metapicture.h"
#include "bmpwrap.h"

void walk(struct metapicture *);
void seed();
long int move(long int, struct metapicture*);
long int getX(long int , struct metapicture*);
long int getY(long int , struct metapicture*);
void *walk_walker(void * );
struct walker {
	long int p;
	void (*colorf)(long int, struct metapicture*);
	struct metapicture * mp;
};

#endif // WALKER_H_INCLUDED
