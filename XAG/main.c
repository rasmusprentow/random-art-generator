
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "main.h"

#include "bmpwrap.h"


#include "walker.h"

long int move (long int);

long int getY(long int p){
	return (long int)floor((p)/w);
}

long int getX(long int p){
	return (long int)(p)%w;
}


void downRed(long int d){
	if(pic[d].red > 0){
		pic[d].red -= 1;
	}
}

void upRed(long int d){
	if(pic[d].red < 255){
		pic[d].red += 1;
	}
}


void upGreen(long int d){
	if(pic[d].green < 255){
		pic[d].green += 1;
	}
}

void downGreen(long int d){
	if(pic[d].green > 0){
		pic[d].green -= 1;
	}
}

void downBlue(long int d){
	if(pic[d].blue > 0){
		pic[d].blue -= 1;
	}
}

void upBlue(long int d){
	if(pic[d].blue < 255){
		pic[d].blue += 1;
	}
}


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
	size = h*w;
	if(size < 0)
	{
		printf("We cannot handle such bit drawings yet\n");
		exit(0);
	}


	printf("Initializing picture \n");
	pic = malloc(size*sizeof(struct dot));
	long int i;
	for( i = 0; i < size; i++)
	{
		pic[i].red = initialRed;
		pic[i].blue = initialBlue;
		pic[i].green = initialGreen;
		pic[i].alpha = 0;
	}


    seed();
    long int dr = abs(rand()* rand()* rand());
    long int ur =  abs(rand()* rand()* rand());//seed();
    long int dg =  abs(rand()* rand()* rand());//seed();
    long int ug =  abs(rand()* rand()* rand());//seed();
    long int db = abs( rand()* rand()* rand());//seed();
    long int ub = abs( rand()* rand()* rand());//seed();
    /// LOL lav da en function til det der.



	struct walker walkers[6] = { 	{ (dr%size)  , &downRed },
	 							 	{ (ur%size)  , &upRed },
									{ (dg%size)  , &downGreen },
									{ (ug%size)  , &upGreen },
									{ (db%size)  , &downBlue },
									{ (ub%size)  , &upBlue }
								};


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

	long int j;
	int p = 1;
	for(j = 0; j < iterations; j++){
		if(j % printPercent == 0 )
		{
			if(printBmpTemp){
				printPic(p,w,h,outputfilename);
				p++;
			}
			if(verbose){
				printf("%f \n", ((double)j/iterations)*100);
			}
		}
		int k = 0;
		for(k = 0; k < 1; k++)
		{


			if(walkers[k].p < 0){
				printf("Too low");
				exit(0);
			}
			if(walkers[k].p > size){
				printf("Too high p-sp:%li, Size %li, getX(p):  %li",(walkers[k].p - sp),size, getX(walkers[k].p));
				exit(0);
			}
			walkers[k].p = move(walkers[k].p);
			walkers[k].colorf(walkers[k].p);
		}

        if(j % seedRenew == 0 && j != 0)
        {
             seed();
        }
	}
 	printf("Starting to print: %s\n", outputfilename);
	printPic(0, w,h,outputfilename );


	return 0;
}

long int move (long int p)
{

     switch (rand() % 4) {
        case 0: // UP
			if(p > w - 1) //
			{
				// Go one row up
			//	printf("up1");
				p = p - w;
			}
			else
			{
				// Go back to down row
			//	printf("up2");
				p = (p + size) - w;
			}
		break;
		case 1: // DOWN
			if(p < ((size) - w)) // getY(p) < h
			{
				// Go one row up
			//	printf("down1");
				p = p + w;
			}
			else
			{
				// Go back to buttom row
				p = (p - size) + w;
				//	printf("down2");
			}
		break;
        case 2: // LEFT
			//	printf("l");
			if(getX(p) == 0){
				p = p + w - 1;
			} else {
				p = p - 1;
			}
		break;
        case 3: // RIGHT
			if(getX(p) == w - 1){
				p = p - w + 1;
		//		printf("r1");
			} else {
		//		printf("r2");
				p = p + 1;
			}
		break;
		default:

            printf("ERROR IN MOVE");
            exit(0);
        break;
	}
	return p;
}
