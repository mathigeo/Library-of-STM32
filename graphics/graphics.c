#include "graphics.h"


/**
 * @brief ����һ��λͼ
 * @param bmp λͼָ��
 * @param width ��
 * @param height ��
 * @param p ͼƬ���ݵ��׵�ַ
 * @retval None
 */
void initBMP(BMP_T *bmp,unsigned char width,unsigned char height,unsigned char *p)
{
	bmp->biHeight=height;
	bmp->biWidth=width;
	bmp->data=p;
}




