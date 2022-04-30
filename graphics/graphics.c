#include "graphics.h"


/**
 * @brief 创建一个位图
 * @param bmp 位图指针
 * @param width 宽
 * @param height 高
 * @param p 图片数据的首地址
 * @retval None
 */
void initBMP(BMP_T *bmp,unsigned char width,unsigned char height,unsigned char *p)
{
	bmp->biHeight=height;
	bmp->biWidth=width;
	bmp->data=p;
}




