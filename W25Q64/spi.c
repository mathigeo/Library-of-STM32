#include "spi.h"  


SPI_InitTypeDef  SPI_InitStructure;



/**
 * @brief SPI初始化
 * @param	
 * @retval
 */
void SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*-GPIO初始化-*/
  
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA,ENABLE);	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	/*-SPI初始化-*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	 //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
	//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	
	//设置SPI的数据大小:SPI发送接收8位帧结构	
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	
	//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	
	//数据捕获于第二个时钟沿	
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	
	//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		
	//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	
	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	//CRC值计算的多项式
	SPI_InitStructure.SPI_CRCPolynomial = 7;	
	//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	SPI_Init(SPI1, &SPI_InitStructure);  
	
	//使能SPI外设
	SPI_Cmd(SPI1, ENABLE); 
	//启动传输		 
	SPI1_ReadWriteByte(0xff);
}   


/**
 * @brief SPI 速度设置
 * @param SpeedSet
 *	SPI_BaudRatePrescaler_2   2分频   (SPI 36M@sys 72M)
 *	SPI_BaudRatePrescaler_8   8分频   (SPI 9M@sys 72M)
 * 	SPI_BaudRatePrescaler_16  16分频  (SPI 4.5M@sys 72M)
 * 	SPI_BaudRatePrescaler_256 256分频 (SPI 281.25K@sys 72M)
 * @retval None
 */
void SPI1_SetSpeed(u8 SpeedSet)
{
	SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
  	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
} 



/**
 * @brief SPIx 读写一个字节
 * @param TxData 要写入的字节
 * @retval 读取到的字节
 */
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)
			return 0;
	}			  
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)
			return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据					    
}




