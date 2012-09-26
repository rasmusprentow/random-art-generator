#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "bmpwrap.h"

void printPic(int count, struct metapicture * mp){

	struct bmpfile_magic magic;
	magic.magic[0] = 66;
	magic.magic[1] = 77;

	uint32_t filesz = sizeof(struct bmpfile_magic)+ sizeof(struct bmpfile_header) +sizeof(BITMAPINFOHEADER2) + (mp->size * sizeof(struct dot));

	struct bmpfile_header bmp_header = {
		.filesz = filesz,
		.creator1 = 0,
	    .creator2 = 0,
		.bmp_offset =  sizeof(struct bmpfile_magic)+ sizeof(struct bmpfile_header) +sizeof(BITMAPINFOHEADER2)
	};


	BITMAPINFOHEADER2 dib_header =
	{
		.header_sz = sizeof(BITMAPINFOHEADER2),
		.width = mp->width,
		.height = mp->height,
		.nplanes = 1,
		.bitspp = 32,
		.compress_type = 0,
		.bmp_bytesz = mp->size * sizeof(struct dot),
		.hres = 2835,
		.vres = 2835,
		.ncolors = 0,
		.nimpcolors = 0
	};



	char * ofn = malloc(sizeof(mp->name) + 30);
	strcpy(ofn,mp->name);
	if(count > 0){


		char * num = malloc(20*sizeof(char));
		int zero_to_add;
		if(count < 10){
			zero_to_add = 5;
		} else
		if(count < 100){
			zero_to_add = 4;
		}else
		if(count < 1000){
				zero_to_add = 3;
		}
		else
		if(count < 10000){
			zero_to_add = 2;
		} else
		if(count < 100000){
			zero_to_add =1;
		}
		else {
			zero_to_add = 0;
		}
		int c;
		for(c = 0; c < zero_to_add; c++){
			strcat(ofn, "0");
		}
		sprintf(num,"%d", count);
		strcat(ofn, num);



	}
	if(strstr(ofn, ".bmp") == NULL){
		strcat(ofn, ".bmp");
	}
	FILE *fp = fopen(ofn, "w");

	fwrite(&magic, 1,sizeof(struct bmpfile_magic),fp);
	fwrite(&bmp_header, 1,sizeof(struct bmpfile_header),fp);
	fwrite(&dib_header, 1,sizeof(BITMAPINFOHEADER2),fp);
   // fwrite(&mp->pic,4, mp->size  , fp);
    struct dot * p = mp->pic;
	long int i;
    for( i = 0; i < mp->size/100; i++){
        	//mp->pic[i].alpha =0;
            fwrite(p, 4, 100,fp);
            p = p + 100;
    }

    printf("Total: %li \n", sizeof(struct bmpfile_magic)+ sizeof(struct bmpfile_header) +sizeof(BITMAPINFOHEADER2) + (mp->size * sizeof(struct dot)));
    printf("bmpfile_header: %li \n", sizeof(struct bmpfile_header));
    printf("Bitmapinfoheader: %li \n", sizeof(BITMAPINFOHEADER2));
    printf("bmpfile_magic: %li \n", sizeof(struct bmpfile_magic));
    printf("size: %li \n", mp->size);
    printf("Size time dot: %li \n",(mp->size * sizeof(struct dot)));
    printf("dot: %li \n",sizeof(struct dot));

/*
	long int i;
	for( i = 0; i < mp->size; i++)
	{
		mp->pic[i].alpha = 0;
		fwrite(&mp->pic[i].red, 1,1,fp);
		fwrite(&mp->pic[i].green, 1,1,fp);
		fwrite(&mp->pic[i].blue, 1,1, fp);
		fwrite(&mp->pic[i].alpha, 1,1, fp);
	}
*/
	fclose(fp);


}
