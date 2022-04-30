#include "system.h"  
#include "systick.h"
#include "TFTLCD.h"
#include "flash.h"

//要写入到W25Q64的字符串数组
const u8 TEXT_Buffer[]={"MiniSTM32 SPI TEST"};


#define SIZE sizeof(TEXT_Buffer)	


 int main(void)
 { 
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
    u16 id = 0;  
	 
 	LCD_Init();		 	
	SPI_Flash_Init();  		//SPI FLASH 初始化 	 
	
	while(1)
	{
		//读取器件ID
		id = SPI_Flash_ReadID();
		if (id == W25Q64 || id == NM25Q64)
			break;
		LCD_Print(0,0,"W25Q64 Check Failed!");
		delay_ms(500);
		LCD_Print(0,16,"Please Check!        ");
		delay_ms(500);
	}
	LCD_Print(0,32,"25Q64 Ready!");

	FLASH_SIZE=8*1024*1024;	//FLASH 大小为8M字节 

#if 0   
 	LCD_Print(0,48,"Start Write W25Q64....");
	SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		
	LCD_Print(0,64,"W25Q64 Write Finished!");	
#else
 	LCD_Print(0,80,"Start Read W25Q64.... ");
	SPI_Flash_Read(datatemp,FLASH_SIZE-100,SIZE);				
	LCD_Print(0,96,"The Data Readed Is:  ");	
	LCD_Print(0,112,"%s",datatemp);					
#endif		
	while(1)
	{
	
	}
}

