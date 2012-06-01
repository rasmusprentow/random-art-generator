#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


int h = 7500;
int w = 5000;

// width point - Aka. upper right corner
long int wp = 0;
// starting point point - Aka. upper left corner
long int sp = 0;
long int size;
long int iterations = 1000000000;
int seedRenew       = 1000;
int printPercent    = 1000000;
int verbose = 0;
int printBmpTemp = 0;
unsigned char initialRed = 127;
unsigned char initialGreen = 127;
unsigned char initialBlue = 127;

char *outputfilename;
int preferedWalker;
int preferedRating;
int forceYes = 0;



#endif // MAIN_H_INCLUDED
