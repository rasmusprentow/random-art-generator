#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

#include <sys/time.h>

#include "walker.h"




void downRed(long int d, struct metapicture* mp){
    struct dot debugdot = mp->pic[d];
	if(mp->pic[d].red > 0){
		mp->pic[d].red -= 1;
	}
	else
	{
	    mp->pic[d].red = mp->pic[d].red;
	}
}

void upRed(long int d, struct metapicture* mp){
	if(mp->pic[d].red < 255){
		mp->pic[d].red += 1;
	}
}


void upGreen(long int d, struct metapicture* mp){
	if(mp->pic[d].green < 255){
		mp->pic[d].green += 1;
	}
}

void downGreen(long int d, struct metapicture* mp){
	if(mp->pic[d].green > 0){
		mp->pic[d].green -= 1;
	}
}

void downBlue(long int d, struct metapicture* mp){
	if(mp->pic[d].blue > 0){
		mp->pic[d].blue -= 1;
	}
}

void upBlue(long int d, struct metapicture* mp){
	if(mp->pic[d].blue < 255){
		mp->pic[d].blue += 1;
	}
}



void seed()
{
    struct timeval  tp;

    gettimeofday(&tp ,NULL);

    //srand( ( tp.tv_sec  * tp.tv_usec));

}

int rands(int iterations)
{
    int res = 0;
    int i;
    for (i = 0 ; i < iterations; i++)
    {
        res += rand();
    }
    return res;
}

int myrand()
{
    static long int seeds = 0;
    static long int nextSeed = 10;
    static long int counter = 10;

    counter++;
    if(counter >= nextSeed)
    {
        //struct timeval  tp;
        //gettimeofday(&tp ,NULL);
        srand( rands(0) + seeds + nextSeed );
        seeds++;
        nextSeed = nextSeed/2 + rand();
        counter = 0;
    }
    return rand();
}


long int getX(long int p,  struct metapicture* mp){
	return (long int)(p)%mp->width;
}





void walk(struct metapicture* mp){
    seed();




    long int dr = abs(rand()* rand()* rand());
    long int ur =  abs(rand()* rand()* rand());//seed();
    long int dg =  abs(rand()* rand()* rand());//seed();
    long int ug =  abs(rand()* rand()* rand());//seed();
    long int db = abs( rand()* rand()* rand());//seed();
    long int ub = abs( rand()* rand()* rand());//seed();
	struct walker walkers[6] = { 	{ (dr%mp->size)  , &downRed },
	 							 	{ (ur%mp->size)  , &upRed },
									{ (dg%mp->size)  , &downGreen },
									{ (ug%mp->size)  , &upGreen },
									{ (db%mp->size)  , &downBlue },
									{ (ub%mp->size)  , &upBlue }
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
	for(j = 0; j < mp->iterations; j++){
	    if(j == 4000000-129765-1)
	    {
            j = j+1;
            j = j-1;
	    }
		if(j % mp->printPercentage == 0 )
		{
			if(mp->printBmpTemp){
				printPic(p,mp);
				p++;
			}
			if(mp->verbose){
				printf("%f \n", ((double)j/mp->iterations)*100);
			}
		}
        int k ;
		for(k = 0; k < 1; k++)
		{


			if(walkers[k].p < 0){
				printf("Too low");
				exit(0);
			}
			if(walkers[k].p > mp->size){
			//	printf("Too high p-sp:%li, Size %li, getX(p):  %li",(walkers[k].p - sp),mp->size, getX(walkers[k].p, mp));
				exit(0);
			}
			walkers[k].p = move(walkers[k].p,mp);
			walkers[k].colorf(walkers[k].p, mp);
		}

        //if(j % mp->seedRenew == 0 && j != 0)
        if (0)
        {
            verifyPictureWhenRedOnly(mp);
             seed();
        }
	}
 	printf("Starting to print: %s\n", mp->name);
 	 verifyPictureWhenRedOnly(mp);
	printPic(0,mp );
}


long int move (long int p, struct metapicture* mp)
{

     switch (myrand() % 4) {
        case 0: // UP
			if(p > mp->width - 1) //
			{
				// Go one row up
			//	printf("up1");
				p = p - mp->width;
			}
			else
			{
				// Go back to down row
			//	printf("up2");
				p = (p + mp->size) - mp->width;
			}
		break;
		case 1: // DOWN
			if(p < ((mp->size) - mp->width)) // getY(p) < h
			{
				// Go one row up
			//	printf("down1");
				p = p + mp->width;
			}
			else
			{
				// Go back to buttom row
				p = (p - mp->size) + mp->width;
				//	printf("down2");
			}
		break;
        case 2: // LEFT
			//	printf("l");
			if(getX(p, mp) == 0){
				p = p + mp->width - 1;
			} else {
				p = p - 1;
			}
		break;
        case 3: // RIGHT
			if(getX(p, mp) == mp->width - 1){
				p = p - mp->width + 1;
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
