#include "system.h"  
#include "systick.h"
#include "ctypes.h"
#include "oled.h"
#include "malloc.h"
#include "menu.h"
#include "usart.h"
#include "bootbmp.h"


/**
 * @brief  主函数
 * @param  无  
 * @retval 无
 */
int main(void)
{		
	BMP_T *btBmp;
	int i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART_Config(115200);
	OLED_Init();
	btBmp = CreatBMP(128,64,bootbmp);
	for(i=0;i<0X3F;i++)
	{
		showBmp(0,0,btBmp);
	}
	OLED_Clear();
	for(i=0;i<0XFF;i++)
	{
		showGBK(1,3,mateName[0]);
		showGBK(1,4,mateName[1]);
		showGBK(1,5,mateName[2]);
		showGBK(2,3,mateName[0]);
		showGBK(2,4,mateName[1]);
		showGBK(2,5,mateName[2]);
		showGBK(3,3,mateName[0]);
		showGBK(3,4,mateName[1]);
		showGBK(3,5,mateName[2]);
		showGBK(4,3,mateName[0]);
		showGBK(4,4,mateName[1]);
		showGBK(4,5,mateName[2]);
	}
	OLED_Clear();
	destroyBMP(btBmp);
	while(1)
	{
		mainMenu();
	}
}

