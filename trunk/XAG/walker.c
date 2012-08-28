#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

#include <sys/time.h>
#include <pthread.h>
#include "walker.h"





void downRed(long int d, struct metapicture* mp){
	if(mp->pic[d].red > 0){
		mp->pic[d].red -= 1;
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

    srand( ( tp.tv_sec  * tp.tv_usec));

}

long int getX(long int p,  struct metapicture* mp){
	return (long int)(p)%mp->width;
}

long int getY(long int p,  struct metapicture* mp){
	return (long int)(p)/mp->height;
}





void walk(struct metapicture* mp){
    seed();




    long int dr = abs(rand()* rand()* rand());
    long int ur =  abs(rand()* rand()* rand());//seed();
    long int dg =  abs(rand()* rand()* rand());//seed();
    long int ug =  abs(rand()* rand()* rand());//seed();
    long int db = abs( rand()* rand()* rand());//seed();
    long int ub = abs( rand()* rand()* rand());//seed();
	struct walker walkers[6] = { 	{ (dr%mp->size)  , &downRed, mp },
	 							 	{ (ur%mp->size)  , &upRed, mp },
									{ (dg%mp->size)  , &downGreen , mp},
									{ (ug%mp->size)  , &upGreen, mp },
									{ (db%mp->size)  , &downBlue, mp },
									{ (ub%mp->size)  , &upBlue, mp }
								};

	pthread_t threads[6];
	int irets[6];
	int k = 0;
    for(k = 0; k < 6; k++)
    {
        irets[k] = pthread_create( &threads[k], NULL,walk_walker, (void*) &walkers[k]);
    }


    for(k = 0; k < 6; k++)
    {

        pthread_join(threads[k], NULL);
    }

    if(mp->printBmp){

        printf("Starting to print: %s\n", mp->name);
         //verifyPictureWhenRedOnly(mp);
        printPic(0,mp );
	}
	mp->done = 1;
    printf("\nDone\n");

}

void *walk_walker(void * w){
    struct walker * walker = (struct walker *) w;
    struct metapicture * mp = walker->mp;

	long int j;
	int p = 1;
	for(j = 0; j < mp->iterations; j++){
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




        if(walker->p < 0){
            printf("Too low");
            exit(0);
        }
        if(walker->p > mp->size){
        //	printf("Too high p-sp:%li, Size %li, getX(p):  %li",(walkers[k].p - sp),mp->size, getX(walkers[k].p, mp));
            exit(0);
        }
        walker->p = move(walker->p,mp);
        walker->colorf(walker->p, mp);


        if(j % mp->seedRenew == 0 && j != 0)
        {
            //verifyPictureWhenRedOnly(mp);
             seed();
        }
	}




    return NULL;
}


long int move (long int p, struct metapicture* mp)
{

     switch (rand() % 4) {
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
