

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
 
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
} BITMAPINFOHEADER;



int main(){

	struct bmpfile_magic magic;
	magic.magic[0] = 'B';
	magic.magic[1] = 'M';
	
	uint32_t filesz = sizeof(struct bmpfile_magic) + sizeof(struct bmpfile_header) +  sizeof(BITMAPINFOHEADER) + 16;
	uint32_t bmp_offset = sizeof(struct bmpfile_magic) +  sizeof(struct bmpfile_header) + sizeof(BITMAPINFOHEADER);
	struct bmpfile_header bmp_header = {
		.filesz = filesz,
		.creator1 = 0,
	    .creator2 = 0,
		.bmp_offset = bmp_offset
	};
	
	
	BITMAPINFOHEADER dib_header = 
	{
		.header_sz = sizeof(BITMAPINFOHEADER),
		.width = 2,
		.height = 2,
		.nplanes = 1,
		.bitspp = 32
	};
	
	uint32_t row1[4] = {  16777215,16711680,16777215,16777215 };
							
	FILE *fp = fopen("test.bmp", "w");

	fwrite(&magic, sizeof(struct bmpfile_magic), 1,fp);
	fwrite(&bmp_header, sizeof(struct bmpfile_header), 1,fp);
	fwrite(&dib_header, sizeof(BITMAPINFOHEADER), 1,fp);
	fwrite(&row1, sizeof(uint32_t ), 16,fp);
	fclose(fp);
}
