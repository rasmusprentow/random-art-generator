#include "metapicture.h"


struct metapicture* getMetaPicture(int w ,int h, char name[20] ,int initialRed, int initialBlue, int initialGreen){



    long int size = h*w;
	if(size < 0)
	{
		printf("We cannot handle such bit drawings yet\n");
		exit(0);
	}
    struct dot * pic = malloc(size*sizeof(struct dot));
    struct metapicture mp = {
        .size = h*w,
        .width = w,
        .height = h,
        .name = name,
        .pic = pic
    };


	//printf("Initializing picture \n");

	long int i;
	for( i = 0; i < size; i++)
	{
		mp.pic[i].red = initialRed;
		mp.pic[i].blue = initialBlue;
		mp.pic[i].green = initialGreen;
		mp.pic[i].alpha = 0;
	}
}
