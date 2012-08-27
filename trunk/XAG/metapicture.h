#ifndef METAPICTURE_H_INCLUDED
#define METAPICTURE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

struct dot {
 	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

struct metapicture {
    long int size;
    int width;
    int height;
    char name[20];
    struct dot * pic;
    long int iterations;
    long int seedRenew;
    long int printPercentage;
    int printBmpTemp;
    int printBmp;
    short int done;
    int verbose;

};

void preparePicture(int ,int , int , struct metapicture*);

/**
 * This function verifies the picture. It only makes sense to use it when red walkers are used.
 */
void verifyPictureWhenRedOnly(struct metapicture *);

#endif // METAPICTURE_H_INCLUDED
