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

	uint32_t filesz = 54 + (mp->size * sizeof(struct dot));

	struct bmpfile_header bmp_header = {
		.filesz = filesz,
		.creator1 = 0,
	    .creator2 = 0,
		.bmp_offset = 54
	};


	BITMAPINFOHEADER dib_header =
	{
		.header_sz = 40,
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

	fwrite(&magic, sizeof(struct bmpfile_magic), 1,fp);
	fwrite(&bmp_header, sizeof(struct bmpfile_header), 1,fp);
	fwrite(&dib_header, sizeof(BITMAPINFOHEADER), 1,fp);
	int i;
    for( i = 0; i < mp->size; i++){
        fwrite(&mp->pic[i], 4, 1,fp);
    }


	/*
	long int i;
	for( i = 0; i < size; i++)
	{
		((struct dot)*pic).alpha = 0;
		fwrite(&pic[i].red, 1,1,fp);
		fwrite(&pic[i].green, 1,1,fp);
		fwrite(&pic[i].blue, 1,1, fp);
		fwrite(&pic[i].alpha, 1,1, fp);
	}
	*/
	fclose(fp);


}
