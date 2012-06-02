#include "metapicture.h"


void preparePicture(int initialRed, int initialBlue, int initialGreen, struct metapicture * mp){



    mp->pic = malloc(mp->size*sizeof(struct dot));

	//printf("Initializing picture \n");

	long int i;
	for( i = 0; i < mp->size; i++)
	{
		mp->pic[i].red = initialRed;
		mp->pic[i].blue = initialBlue;
		mp->pic[i].green = initialGreen;
		mp->pic[i].alpha = 0;
	}

}
