#include "graphics.h"
#include "malloc.h"



/**
 * @brief ����һ��λͼ
 * @param width ��
 * @param height ��
 * @param p ͼƬ���ݵ��׵�ַ
 * @retval λͼָ��
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
 * @brief ����ͼ��
 * @param p ͼ��ָ��
 * @retval None
 */
void destroyBMP(BMP_T *p)
{
	free(p);
}


