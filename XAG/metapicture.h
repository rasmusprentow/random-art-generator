#ifndef METAPICTURE_H_INCLUDED
#define METAPICTURE_H_INCLUDED
#include "bmpwrap.h"
struct metapicture {
    long int size;
    int width;
    int height;
    char name[20];
    struct dot * pic;

};

struct metapicture *getMetaPicture(int ,int , char[20], int ,int, int);



#endif // METAPICTURE_H_INCLUDED
