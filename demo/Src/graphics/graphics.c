#include "graphics.h"
#include "malloc.h"



/**
 * @brief 创建一个位图
 * @param width 宽
 * @param height 高
 * @param p 图片数据的首地址
 * @retval 位图指针
 */
BMP_T *CreatBMP(unsigned char width,unsigned char height,unsigned char *p)
{
	BMP_T *bmp;
	bmp = (BMP_T *)malloc(sizeof(BMP_T));
	bmp->biHeight=height;
	bmp->biWidth=width;
	bmp->data=p;
	return bmp;
}



/**
 * @brief 销毁图像
 * @param p 图像指针
 * @retval None
 */
void destroyBMP(BMP_T *p)
{
	free(p);
}


