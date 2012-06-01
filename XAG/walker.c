#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

#include <sys/time.h>

#include "walker.h"




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



void seed()
{
    struct timeval  tp;

    gettimeofday(&tp ,NULL);

    srand( ( tp.tv_sec  * tp.tv_usec));

}

long int getX(long int p,  struct metapicture mp){
	return (long int)(p)%mp.width;
}





void walk(struct metapicture* mp){
    long int dr = abs(rand()* rand()* rand());
    long int ur =  abs(rand()* rand()* rand());//seed();
    long int dg =  abs(rand()* rand()* rand());//seed();
    long int ug =  abs(rand()* rand()* rand());//seed();
    long int db = abs( rand()* rand()* rand());//seed();
    long int ub = abs( rand()* rand()* rand());//seed();
	struct walker walkers[6] = { 	{ (dr%mp->size)  , &downRed },
	 							 	{ (ur%mp->size)  , &downRed },
									{ (dg%mp->size)  , &downGreen },
									{ (ug%mp->size)  , &downGreen },
									{ (db%mp->size)  , &downBlue },
									{ (ub%mp->size)  , &downBlue }
								};

	/*struct walker walkers[6] = { 	{ (dr%size)  , &downRed },
	 							 	{ (ur%size)  , &upRed },
									{ (dg%size)  , &downGreen },
									{ (ug%size)  , &upGreen },
									{ (db%size)  , &downBlue },
									{ (ub%size)  , &upBlue }
								};
*/
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
        int k ;
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
}


long int move (long int p, struct metapicture mp)
{
     int w = mp.width;
     int h = mp.height;
     long int size = w * h;
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
			if(getX(p, mp) == 0){
				p = p + w - 1;
			} else {
				p = p - 1;
			}
		break;
        case 3: // RIGHT
			if(getX(p, mp) == w - 1){
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
