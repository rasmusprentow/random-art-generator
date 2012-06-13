

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

int h = 7500;
int w = 5000;

// width point - Aka. upper right corner
long int wp = 0;
// starting point point - Aka. upper left corner
long int sp = 0;
long int size;
long int iterations = 1000000000;
int seedRenew       = 10000000;
int printPercent    = 1000000;
int verbose = 0;
int printBmpTemp = 0;
unsigned char initialRed = 127;
unsigned char initialGreen = 127;
unsigned char initialBlue = 127;
struct dot * pic;
char *outputfilename;
int preferedWalker;
int preferedRating;
int forceYes = 0;


struct dot {
 	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};


struct walker {
	long int p;
	void (*colorf)(long int);
};


/* Note: the magic number has been removed from the bmpfile_header structure
   since it causes alignment problems
     struct bmpfile_magic should be written/read first
   followed by the
     struct bmpfile_header
   [this avoids compiler-specific alignment pragmas etc.]
*/

struct bmpfile_magic {
  unsigned char magic[2];
};

struct bmpfile_header {
  uint32_t filesz;
  uint16_t creator1;
  uint16_t creator2;
  uint32_t bmp_offset;
};


typedef struct {
  uint32_t header_sz;
  int32_t width;
  int32_t height;
  uint16_t nplanes;
  uint16_t bitspp;
  uint32_t compress_type;
  uint32_t bmp_bytesz;
  int32_t hres;
  int32_t vres;
  uint32_t ncolors;
  uint32_t nimpcolors;
} BITMAPINFOHEADER;



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

void printPic(int count){



	struct bmpfile_magic magic;
	magic.magic[0] = 'B';
	magic.magic[1] = 'M';

	uint32_t filesz = 54 + size * sizeof(struct dot);

	struct bmpfile_header bmp_header = {
		.filesz = filesz,
		.creator1 = 0,
	    .creator2 = 0,
		.bmp_offset = 54
	};


	BITMAPINFOHEADER dib_header =
	{
		.header_sz = 40,
		.width = w,
		.height = h,
		.nplanes = 1,
		.bitspp = 32,
		.compress_type = 0,
		.bmp_bytesz = size * sizeof(struct dot),
		.hres = 2835,
		.vres = 2835,
		.ncolors = 0,
		.nimpcolors = 0
	};


	if(outputfilename == 0) {
		outputfilename = malloc(10);
		outputfilename = "image.bmp";
	}
	char * ofn = malloc(sizeof(outputfilename) + 30);
	strcpy(ofn,outputfilename);
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
	fwrite(pic, sizeof(struct dot), size,fp);


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
	srand ( time(NULL) );
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




	struct walker walkers[6] = { 	{ (rand()%size), &downRed },
	 							 	{ (rand()%size), &upRed },
									{ (rand()%size), &downGreen },
									{ (rand()%size), &upGreen },
									{ (rand()%size), &downBlue },
									{ (rand()%size), &upBlue }
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
				printPic(p);
				p++;
			}
			if(verbose){
				printf("%f \n", ((double)j/iterations)*100);
			}
		}
		int k;
		for(k = 0; k < 6; k++){
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
		if(j % seedRenew == 0 && j != 0){
			srand(time(NULL));
		}

	}
 	printf("Starting to print: %s\n", outputfilename);
	printPic(0);


	return 0;
}

long int move (long int p)
{

	if(rand()%2) // left, right or up down
	{
		if(rand()%2) // up
		{
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
		}
		else // down
		{
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
		}
	}
	else
	{
		if(rand()%2) // left
		{
			//	printf("l");
			if(getX(p) == 0){
				p = p + w - 1;
			} else {
				p = p - 1;
			}
		}
		else  // right
		{

			if(getX(p) == w - 1){
				p = p - w + 1;
		//		printf("r1");
			} else {
		//		printf("r2");
				p = p + 1;
			}
		}
	}
	return p;
}

