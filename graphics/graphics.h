#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#pragma	pack(1)
typedef struct _BMP_T
{
	unsigned char biWidth;		/*¿í*/
	unsigned char biHeight;		/*¸ß*/
	unsigned char *data;	
}BMP_T;
#pragma pack()


void initBMP(BMP_T *bmp,unsigned char width,unsigned char height,unsigned char *p);

#endif //__GRAPHICS_H



