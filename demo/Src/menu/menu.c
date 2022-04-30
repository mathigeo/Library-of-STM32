#include "menu.h"
#include "stdarg.h"
#include "stdio.h"
#include "oled.h"
#include "usart.h"

void subMenu1(unsigned char item);	/*�Ӳ˵�1*/
unsigned char menuStage=0;			/*�˵�����*/


/**
 * @brief �˵�ר�ô�ӡ����
 * @param inv ����ѡ��
 * @param row ��(1-4)
 * @param col ��(1-16)
 * @param fmt ��ռλ�����ַ���
 * @retval vsprintf�ķ���ֵ
 */
static int itemPrint(UINT8 inv,UINT8 row,UINT8 col,const char *fmt,...)
{
	char buf[32]={'\0'};
	int ret=0;
	va_list ap;
	
	va_start(ap,fmt);
	ret = vsprintf(buf,fmt,ap);
	va_end(ap);
	OLED_ShowString(row,col,buf,inv);
	return ret;
}

/**
 * @brief ���˵�
 * @param None
 * @retval None
 */
void mainMenu(void)
{
	/*ѡ���ʼ��Ϊ�����ڵ�ѡ��*/
	static unsigned char select=0X0F;
	
	/*��������Ǳ���*/
	if(menuStage!=0)
	{
		subMenu1(select);
	}
	else
	{
		if(recv<=4&&recv>0)
		{
			select = recv;
		}
		itemPrint(0		   ,1,12,"0->OK");
		itemPrint(1==select,1,1,"ADD ");
		itemPrint(2==select,2,1,"SUB ");
		itemPrint(3==select,3,1,"QUIT");
		itemPrint(4==select,4,1,"ENTER ");
		
		if(recv!=0)
			return ;
		/*recv==0��ʼȷ��ѡ��*/
		switch(select)
		{
			case 1:menuStage=1;OLED_Clear(),select=0X0F;break;
			case 2:break;	
			case 3:break;	
			case 4:break;	
		}
	}
}


void subMenu1(unsigned char item)
{
	static unsigned char select=0X0F;
	
	if(recv<=4&&recv>0)
	{
		select = recv;
	}
	itemPrint(0		   ,1,12,"0->OK");
	itemPrint(1==select,1,1,"+100");
	itemPrint(2==select,2,1,"+10");
	itemPrint(3==select,3,1,"+1");
	itemPrint(4==select,4,1,"BACK");
	
	if(recv!=0)
		return ;
	/*recv==0��ʼȷ��ѡ��*/	
	switch(select)
	{
		case 1:break;
		case 2:break;
		case 3:break;
		case 4:menuStage=0;OLED_Clear();select=0X0F;break;
	}
}




