


struct metapicture* getMetaPicture(int w ,int h, char name[20]){


    struct metapicture mp = {
        .size = h*w,
        .width = w,
        .height = h,
        .name = name

    };


    long int size = h*w;
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
}
