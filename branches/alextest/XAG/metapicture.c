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



void verifyPictureWhenRedOnly(struct metapicture * mp)
{
    //printf("verify\n");
    int i;
    for( i = 0; i < mp->size; i++){
        if(mp->pic[0].green != 127){
            printf("Error green");
        }

        if(mp->pic[0].blue != 127){
            printf("Error blue");
        }
        if(mp->pic[0].alpha != 0){
            printf("Error blue");
        }
    }

}
