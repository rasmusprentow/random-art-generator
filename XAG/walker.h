#ifndef WALKER_H_INCLUDED
#define WALKER_H_INCLUDED

#include "metapicture.h"
#include "bmpwrap.h"

void walk(struct metapicture *);
void seed();
long int move(long int, struct metapicture*);
long int getX(long int , struct metapicture*);


struct walker {
	long int p;
	void (*colorf)(long int, struct metapicture*);
};

#endif // WALKER_H_INCLUDED
