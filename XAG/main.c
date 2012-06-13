
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "main.h"

#include "bmpwrap.h"


#include "walker.h"


#define DEBUG


void printUsage(char * name){
	printf("Usage: %s [-options] \n", name);
	printf("Options: \n");
	printf(" -v \t Verbose \n");
	printf(" -h \t Height: -h XX \n");
	printf(" -w \t Width:  -w XX \n");
	printf(" -o \t Output file name: -o name.bnp \n");
	printf(" -i \t Iterations: -i M E. \n\t\t(M is mantisa as whole number, \n\t\t E is the exponent) \n");
	printf(" -p \t printPercent: -p I. Indicates when percent should be displayed. \n\t\t Also used for printBmpTmp \n");
	printf(" -t \t printBmp: -t. Prints the bmp at each printpercent time \n");
	printf(" -s \t Seed renew: -t. When seed is renewed \n");
	printf(" -r \t Initial red \n");
	printf(" -g \t Initial green \n");
	printf(" -b \t Initial blue \n");
}

int main(int argc, char *argv[]){
   // int h = 7500;
   // int w = 5000;

    // width point - Aka. upper right corner
   // long int wp = 0;
    // starting point point - Aka. upper left corner
   // long int sp = 0;
    //long int size;
    //long int iterations = 1000000000;
    //int seedRenew       = 1000;
    //int printPercent    = 1000000;
  //  int verbose = 0;
   // int printBmpTemp = 0;
    unsigned char initialRed = 127;
    unsigned char initialGreen = 127;
    unsigned char initialBlue = 127;
    int forceYes = 0;
    struct metapicture mp = {
        .size = 400*400,
        .width = 400,
        .height = 400,
        .name = "image",
        .pic = NULL,
        .iterations = 7500000,  //.iterations = 6500000,
        .verbose = 1,
        .printBmpTemp = 0,
        .seedRenew = 1000,
        .printPercentage = 1000000
    };


	int oi;
	for(oi = 1; oi < argc; oi++){
		if(	strstr(argv[oi], "--help") != NULL){
			printUsage( argv[0]);
			exit(1);
		}
		if(strstr(argv[oi], "-") != NULL){
			switch(argv[oi][1]){

				case 'h':
					mp.height = atoi(argv[oi+1]);
					break;
				case 'w':
					mp.width = atoi(argv[oi+1]);
					break;
				case 'o':
                    strcpy(argv[oi+1],mp.name);

					break;
				case 'i':
					mp.iterations = pow(atoi(argv[oi+1]),atoi(argv[oi+2]));
					break;
				case 'v':
					mp.verbose = 1;
					break;
				case 'p':
					mp.printPercentage = atoi(argv[oi+1]);
					mp.verbose = 1;
					break;
				case 't':
					mp.printBmpTemp  = 1;
					break;
				case 's':
					mp.seedRenew = atoi(argv[oi+1]);
					break;
				case 'r':
					initialRed = atoi(argv[oi+1]);
					break;
				case 'g':
					initialGreen = atoi(argv[oi+1]);
					break;
				case 'b':
					initialBlue = atoi(argv[oi+1]);
					break;
				case 'f':
					forceYes = 1;
					break;
				default :
					printf("Unknown param: %s\n",argv[oi]);
					exit(1);
			}
		}
	}
	//seed();

    mp.size = mp.height * mp.width;

	printf("Height: \t\t%d \nWidth:  \t\t%d \n", mp.height, mp.width);
	printf("Iterations: \t\t%li \noutputfile: \t\t%s \n", mp.iterations, mp.name);
	printf("SeedRenew: \t\t%li\t(%li times) \nPrintPercent: \t\t%li\t(%li times)", mp.seedRenew, mp.iterations/mp.seedRenew,mp.printPercentage, mp.iterations/mp.printPercentage);
	if(mp.printBmpTemp){
		printf("NB: you get a copy for each");
	}
//	printf("\n%d\n",sizeof(BITMAPINFOHEADER));
	printf("\nEstimated HD usage: \t%f (KiB)\n", mp.printBmpTemp ? (double)(1+(mp.iterations/mp.printPercentage))*((mp.size*4)/1024) : (double)(mp.size*4)/1024);
	printf("Est. memory usage: \t%f (KiB)\n", (double)(mp.size*4)/1024);
	printf("Save tmp files: \t%s \n", mp.printBmpTemp ? "Yes":"No" );
	printf("Verbose: \t\t%s \n", mp.verbose ? "Yes":"No" );
	printf("Initial color: \t\t%d %d %d \n", initialRed,initialGreen, initialBlue );
	printf("Draw picture (y/n):" );
	if(!forceYes){
		if(getchar() != 'y'){
			exit(0);
		}
	}
	printf("Starting to draw: \n");
	preparePicture(initialRed, initialGreen, initialBlue, &mp);
	verifyPictureWhenRedOnly(&mp);
    walk(&mp);

	return 0;
}
