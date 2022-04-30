#include "oled.h"
#include "oledfont.h"
#include "stdarg.h"
#include "stdio.h"
#include "systick.h"



#ifdef 	USE_IIC

/**
 * @brief 引脚初始化
 * @param None
 * @retval None
 */
void OLED_Dev_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(OLED_SCL_PORT_CLK|OLED_SDA_PORT_CLK, ENABLE);
	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = SCL_PIN;
 	GPIO_Init(SCL_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;
 	GPIO_Init(SDA_PORT, &GPIO_InitStructure);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}



/**
 * @brief I2C开始
 * @param None
 * @retval None
 */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}



/**
 * @brief I2C停止
 * @param None
 * @retval None
 */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}



/**
 * @brief I2C发送一个字节
 * @param Byte 要发送的一个字节
 * @retval None
 */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//额外的一个时钟，不处理应答信号
	OLED_W_SCL(0);
}



/**
 * @brief OLED写命令
 * @param Command 要写入的命令
 * @retval None
 */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}



/**
 * @brief OLED写数据
 * @param Data 要写入的数据
 * @retval None
 */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}
#endif //USE_IIC



#ifdef 	USE_SPI

/**
 * @brief 引脚初始化
 * @param None
 * @retval None
 */
void OLED_Dev_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(D0_PORT_CLK|D1_PORT_CLK|RES_PORT_CLK\
							|DC_PORT_CLK|CS_PORT_CLK, ENABLE);
		
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = D0_PIN;
 	GPIO_Init(D0_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = D1_PIN;
 	GPIO_Init(D1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = RES_PIN;
 	GPIO_Init(RES_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DC_PIN;
 	GPIO_Init(DC_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = CS_PIN;
 	GPIO_Init(CS_PORT, &GPIO_InitStructure);
	
	OLED_W_D0(1);
	OLED_W_D1(1);
	OLED_W_RES(1);
	OLED_W_DC(1);
	OLED_W_CS(1);
}



/**
 * @brief SPI发送一个字节
 * @param Byte 要发送的一个字节
 * @retval None
 */
void OLED_SPI_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_D0(0);
		OLED_W_D1(Byte & (0x80 >> i));
		OLED_W_D0(1);
	}
}



/**
 * @brief OLED写命令
 * @param Command 要写入的命令
 * @retval None
 */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_W_CS(0);
	OLED_W_DC(0);
	OLED_SPI_SendByte(Command);
	OLED_W_CS(1);
}



/**
 * @brief OLED写数据
 * @param Data 要写入的数据
 * @retval None
 */
void OLED_WriteData(uint8_t Data)
{
	OLED_W_CS(0);
	OLED_W_DC(1);
	OLED_SPI_SendByte(Data);
	OLED_W_CS(1);
}
#endif //USE_SPI



/**
 * @brief OLED设置光标位置
 * @param Y 以左上角为原点，向下方向的坐标，范围：0~7
 * @param X 以左上角为原点，向右方向的坐标，范围：0~127
 * @retval None
 */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置低4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置高4位
}



/**
 * @brief OLED清屏
 * @param None
 * @retval None
 */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}


/**
 * @brief 显示汉字
 * @param row 行位置 范围 1-4
 * @param col 列位置 范围 1-16
 * @param gbk汉字存储的首地址
 * @retval None
 */
int showGBK(unsigned char row,unsigned char col,uint8_t *gbk)
{
	int i,j;	
	for(i=0;i<2;i++)
	{
		OLED_SetCursor((row-1)*2+i,(col-1)*16);
		for(j=0;j<16;j++)
		{
			OLED_WriteData(gbk[i*16+j]);
		}
	}
	return 0;
}



/**
 * @brief 显示一个图像
 * @param x 横坐标
 * @param y 纵坐标
 * @param bmp 位图
 * @retval 程序状态，0为成功
 */
int showBmp(unsigned char x,unsigned char y,BMP_T *bmp)
{
	int i,j;
	
	if(bmp->biHeight>64)	//如果超宽
		return -1;
	if(bmp->biWidth>128)	//如果超高
		return -3;
	if(bmp->biHeight%8 != 0)//如果高不是8的倍数
		return -5;
	if(y%8 != 0)			//如果纵坐标不是8的倍数
		return -6;
	
	for(i=0;i<bmp->biHeight/8;i++)
	{
		OLED_SetCursor(y+i,x);
		for(j=0;j<bmp->biWidth;j++)
		{
			OLED_WriteData(bmp->data[i*bmp->biWidth+j]);
		}
	}
	return 0;
}



/**
 * @brief OLED显示一个字符
 * @param row 行位置，范围：1~4
 * @param col 列位置，范围：1~16
 * @param Chr 要显示的一个字符，范围：ASCII可见字符
 * @param inv 黑白反显,0为不反显，1为反显
 * @retval None
 */
void OLED_ShowChar(uint8_t row,uint8_t col,char Chr,uint8_t inv)
{      	
	uint8_t i;
	//设置光标位置在上半部分
	OLED_SetCursor((row - 1) * 2, (col - 1) * 8);	
	for (i = 0; i < 8; i++)
	{
		//显示上半部分内容
		if(inv)
		{
			OLED_WriteData(~OLED_F8x16[Chr - ' '][i]);
		}
		else
		{
			OLED_WriteData(OLED_F8x16[Chr - ' '][i]);
		}
	}
	//设置光标位置在下半部分
	OLED_SetCursor((row - 1) * 2 + 1, (col - 1) * 8);
	for (i = 0; i < 8; i++)
	{
		//显示下半部分内容
		if(inv)
		{
			OLED_WriteData(~OLED_F8x16[Chr - ' '][i + 8]);
		}
		else 
		{
			OLED_WriteData(OLED_F8x16[Chr - ' '][i + 8]);
		}
	}
}



/**
 * @brief OLED显示字符串
 * @param row 起始行位置，范围：1~4
 * @param col 起始列位置，范围：1~16
 * @param str 要显示的字符串，范围：ASCII可见字符
 * @param inv 黑白反显,0为不反显，1为反显
 * @retval None
 */
void OLED_ShowString(uint8_t row,uint8_t col,char *str,uint8_t inv)
{
	uint8_t i;
	for (i = 0; str[i] != '\0'; i++)
	{
		OLED_ShowChar(row, col + i,str[i],inv);
	}
}



/**
 * @brief OLED初始化
 * @param None
 * @retval None
 */
void OLED_Init(void)
{	
	/*端口初始化*/
	OLED_Dev_Init();			
	
	delay_ms(100);
	OLED_WriteCommand(0xAE);	//--display off
	OLED_WriteCommand(0x00);	//---set low column address
	OLED_WriteCommand(0x10);	//---set high column address
	OLED_WriteCommand(0x40);	//--set start line address  
	OLED_WriteCommand(0xB0);	//--set page address
	OLED_WriteCommand(0x81); 	// contract control
	OLED_WriteCommand(0xFF);	//--128   
	OLED_WriteCommand(0xA1);	//set segment remap 
	OLED_WriteCommand(0xA6);	//0xA6--normal / 0xA7--reverse
	OLED_WriteCommand(0xA8);	//--set multiplex ratio(1 to 64)
	OLED_WriteCommand(0x3F);	//--1/32 duty
	OLED_WriteCommand(0xC8);	//Com scan direction
	OLED_WriteCommand(0xD3);	//-set display offset
	OLED_WriteCommand(0x00);	//
	
	OLED_WriteCommand(0xD5);	//set osc division
	OLED_WriteCommand(0x80);	//
	
	OLED_WriteCommand(0xD8);	//set area color mode off
	OLED_WriteCommand(0x05);	//
	
	OLED_WriteCommand(0xD9);	//Set Pre-Charge Period
	OLED_WriteCommand(0xF1);	//
	
	OLED_WriteCommand(0xDA);	//set com pin configuartion
	OLED_WriteCommand(0x12);	//
	
	OLED_WriteCommand(0xDB);	//set Vcomh
	OLED_WriteCommand(0x30);	//
	
	OLED_WriteCommand(0x20);	//set memory addressing mode
	OLED_WriteCommand(0x02);	//page addressing mode
	
	OLED_WriteCommand(0x8D);	//set charge pump enable
	OLED_WriteCommand(0x14);	//
	
	OLED_WriteCommand(0xAF);	//--turn on oled panel
		
	OLED_Clear();				//clear
}



/**
 * @brief 打印
 * @param row 行(序号从1开始)
 * @param col 列(序号从1开始)
 * @param formate 含或不含有有占位符的字符串
 * @param ...不定参数
 * @retval vsprintf的状态
 */
int oledPrint(u8 row,u8 col,const char *formate,...)
{
	char buf[32]={'\0'};
	int ret=0;
	va_list ap;
	va_start(ap,formate);
	ret = vsprintf(buf,formate,ap);
	va_end(ap);
	OLED_ShowString(row,col,buf,0);
	return ret;
}
