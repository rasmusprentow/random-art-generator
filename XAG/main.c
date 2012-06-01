
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "main.h"

#include "bmpwrap.h"


#include "walker.h"





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
	int oi;
	for(oi = 1; oi < argc; oi++){
		if(	strstr(argv[oi], "--help") != NULL){
			printUsage( argv[0]);
			exit(1);
		}
		if(strstr(argv[oi], "-") != NULL){
			switch(argv[oi][1]){

				case 'h':
					h = atoi(argv[oi+1]);
					break;
				case 'w':
					w = atoi(argv[oi+1]);
					break;
				case 'o':
					outputfilename = argv[oi+1];
					break;
				case 'i':
					iterations = pow(atoi(argv[oi+1]),atoi(argv[oi+2]));
					break;
				case 'v':
					verbose = 1;
					break;
				case 'p':
					printPercent = atoi(argv[oi+1]);
					verbose = 1;
					break;
				case 't':
					printBmpTemp  = 1;
					break;
				case 's':
					seedRenew = atoi(argv[oi+1]);
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

    seed();


	printf("Height: \t\t%d \nWidth:  \t\t%d \n", h, w);
	printf("Iterations: \t\t%li \noutputfile: \t\t%s \n", iterations, outputfilename);
	printf("SeedRenew: \t\t%d\t(%li times) \nPrintPercent: \t\t%d\t(%li times)", seedRenew, iterations/seedRenew,printPercent, iterations/printPercent);
	if(printBmpTemp){
		printf("NB: you get a copy for each");
	}
//	printf("\n%d\n",sizeof(BITMAPINFOHEADER));
	printf("\nEstimated HD usage: \t%f (KiB)\n", printBmpTemp ? (double)(1+(iterations/printPercent))*((size*4)/1024) : (double)(size*4)/1024);
	printf("Est. memory usage: \t%f (KiB)\n", (double)(size*4)/1024);
	printf("Save tmp files: \t%s \n", printBmpTemp ? "Yes":"No" );
	printf("Verbose: \t\t%s \n", verbose ? "Yes":"No" );
	printf("Initial color: \t\t%d %d %d \n", initialRed,initialGreen, initialBlue );
	printf("Draw picture (y/n):" );
	if(!forceYes){
		if(getchar() != 'y'){
			exit(0);
		}
	}
	printf("Starting to draw: \n");
    walk();

	return 0;
}
