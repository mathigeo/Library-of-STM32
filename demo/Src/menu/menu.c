#include "menu.h"
#include "stdarg.h"
#include "stdio.h"
#include "oled.h"
#include "usart.h"

void subMenu1(unsigned char item);	/*子菜单1*/
unsigned char menuStage=0;			/*菜单级数*/


/**
 * @brief 菜单专用打印函数
 * @param inv 高亮选项
 * @param row 行(1-4)
 * @param col 列(1-16)
 * @param fmt 含占位符的字符串
 * @retval vsprintf的返回值
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
 * @brief 主菜单
 * @param None
 * @retval None
 */
void mainMenu(void)
{
	/*选项初始化为不存在的选项*/
	static unsigned char select=0X0F;
	
	/*如果层数非本层*/
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
		/*recv==0开始确认选项*/
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
	/*recv==0开始确认选项*/	
	switch(select)
	{
		case 1:break;
		case 2:break;
		case 3:break;
		case 4:menuStage=0;OLED_Clear();select=0X0F;break;
	}
}




