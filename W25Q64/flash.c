#include "flash.h" 
#include "spi.h"
#include "systick.h"   

/**
 * @brief 4Kbytes为一个Sector
 * @note 16个扇区为1个Block
 *	W25X16
 *	容量为2M字节,共有32个Block,512个Sector 
 */
u16 SPI_FLASH_TYPE=W25Q64;//默认就是25Q64





/**
 * @brief 初始化SPI FLASH的IO口
 * @param None
 * @retval None
 */
void SPI_Flash_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );

	//SPI CS
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;  
	//复用推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
	//初始化SPI
	SPI1_Init();		  
	//设置为18M时钟,高速模式
	SPI1_SetSpeed(SPI_BaudRatePrescaler_4);	
	//读取FLASH ID.
	SPI_FLASH_TYPE=SPI_Flash_ReadID();
}  




/**
 * @brief 读取SPI_FLASH的状态寄存器
 * @param None
 * @retval 读取的值
 * @note	
 *	BIT7  6   5   4   3   2   1   0
 *	SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 *	SPR:默认0,状态寄存器保护位,配合WP使用
 *	TB,BP2,BP1,BP0:FLASH区域写保护设置
 *	WEL:写使能锁定
 *	BUSY:忙标记位(1,忙;0,空闲)
 *	默认:0x00
 */
u8 SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	//使能器件 
	SPI_FLASH_CS=0;          
	//发送读取状态寄存器命令    
	SPI1_ReadWriteByte(W25X_ReadStatusReg);   
	//读取一个字节  
	byte=SPI1_ReadWriteByte(0Xff);   
	//取消片选   
	SPI_FLASH_CS=1;                              
	return byte;   
} 



/**
 * @brief 写SPI_FLASH状态寄存器
 * @param sr 要写入的值
 * @retval None
 * @note 只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
 */
void SPI_FLASH_Write_SR(u8 sr)   
{   
	//使能器件   
	SPI_FLASH_CS=0; 
	//发送写取状态寄存器命令
	SPI1_ReadWriteByte(W25X_WriteStatusReg);  
	//写入一个字节  
	SPI1_ReadWriteByte(sr);  
	//取消片选    
	SPI_FLASH_CS=1;                             	      
}   



/**
 * @brief SPI_FLASH写使能,将WEL置位
 * @param None
 * @retval None
 */
void SPI_FLASH_Write_Enable(void)   
{
	//使能器件  
	SPI_FLASH_CS=0;    
	//发送写使能  
    SPI1_ReadWriteByte(W25X_WriteEnable);    
	//取消片选    
	SPI_FLASH_CS=1;                             	      
} 



/**
 * @brief SPI_FLASH写禁止,将WEL清零
 * @param None
 * @retval None
 */
void SPI_FLASH_Write_Disable(void)   
{  
	//使能器件  
	SPI_FLASH_CS=0;  
	//发送写禁止指令
    SPI1_ReadWriteByte(W25X_WriteDisable);  
	//取消片选 
	SPI_FLASH_CS=1;                                	      
} 			    


/**
 * @brief 读取芯片ID W25X16的ID:0XEF14
 * @param None
 * @retval 读取的值
 */
u16 SPI_Flash_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_FLASH_CS=0;	
	//发送读取ID命令
	SPI1_ReadWriteByte(0x90);	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	 			   
	Temp|=SPI1_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI1_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS=1;				    
	return Temp;
}   		    



/**
 * @brief 读取SPI FLASH  
 * @param pBuffer 数据存储区
 * @param ReadAddr 开始读取的地址(24bit)
 * @param NumByteToRead 要读取的字节数(最大65535)
 * @retval None
 * @note 在指定地址开始读取指定长度的数据
 */
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	u16 i;    	
	//使能器件  
	SPI_FLASH_CS=0; 
	//发送读取命令   
    SPI1_ReadWriteByte(W25X_ReadData); 
	//发送24bit地址
    SPI1_ReadWriteByte((u8)((ReadAddr)>>16));      
    SPI1_ReadWriteByte((u8)((ReadAddr)>>8));   
    SPI1_ReadWriteByte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
		//循环读数  
        pBuffer[i]=SPI1_ReadWriteByte(0XFF);   
    }
	//取消片选 
	SPI_FLASH_CS=1;                                	      
}  



/**
 * @brief SPI在一页(0~65535)内写入少于256个字节的数据
 * @param pBuffer 数据存储区
 * @param WriteAddr 开始写入的地址(24bit)
 * @param NumByteToWrite 要写入的字节数(最大256),
	该数不应该超过该页的剩余字节数!!!	  
 * @retval None
 * @note 在指定地址开始写入最大256字节的数据
 */
void SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
	//SET WEL
    SPI_FLASH_Write_Enable();     
	//使能器件   
	SPI_FLASH_CS=0;      
	//发送写页命令 
    SPI1_ReadWriteByte(W25X_PageProgram);  
	//发送24bit地址
    SPI1_ReadWriteByte((u8)((WriteAddr)>>16));     
    SPI1_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPI1_ReadWriteByte((u8)WriteAddr);   
	//循环写数
    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]); 
	//取消片选
	SPI_FLASH_CS=1;   
	//等待写入结束
	SPI_Flash_Wait_Busy();					   
} 



/**
 * @brief 无检验写SPI FLASH 
 * @param pBuffer 数据存储区
 * @param WriteAddr 开始写入的地址(24bit)
 * @param NumByteToWrite 要写入的字节数(最大65535)
 * @retval None
 * @note 必须确保所写的地址范围内的数据全部为0XFF,
	否则在非0XFF处写入的数据将失败!具有自动换页功能 
	在指定地址开始写入指定长度的数据,但是要确保地址不越界!
 */
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	  
	//单页剩余的字节数
	pageremain=256-WriteAddr%256; 
	//不大于256个字节
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		//写入结束了
		if(NumByteToWrite==pageremain)
			break;
		//NumByteToWrite>pageremain
	 	else 
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	
			//减去已经写入了的字节数
			NumByteToWrite-=pageremain;	
			//一次可以写入256个字节
			if(NumByteToWrite>256)pageremain=256; 
			//不够256个字节了
			else pageremain=NumByteToWrite; 	  
		}
	};	    
} 




u8 SPI_FLASH_BUF[4096];



/**
 * @brief 写SPI FLASH  
 * @param pBuffer 数据存储区
 * @param WriteAddr 开始写入的地址(24bit)
 * @param NumByteToWrite 要写入的字节数(最大65535)  
 * @retval None
 * @note 在指定地址开始写入指定长度的数据
	该函数带擦除操作!
 */
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	
	//扇区地址 0~511 for w25x16
	secpos=WriteAddr/4096;
	//在扇区内的偏移
	secoff=WriteAddr%4096;
	//扇区剩余空间大小
	secremain=4096-secoff;   
	
	//不大于4096个字节
	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;
	while(1) 
	{	
		//读出整个扇区的内容
		SPI_Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);
		//校验数据
		for(i=0;i<secremain;i++)
		{
			//需要擦除  	  
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;
		}
		//需要擦除
		if(i<secremain)
		{
			//擦除这个扇区
			SPI_Flash_Erase_Sector(secpos);
			//复制
			for(i=0;i<secremain;i++)	   
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			//写入整个扇区  
			SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);

		}
		else 
			//写已经擦除了的,直接写入扇区剩余区间.
			SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain); 	
		//写入结束了
		if(NumByteToWrite==secremain)
			break;
		//写入未结束
		else
		{
			//扇区地址增1
			secpos++;
			//偏移位置为0 	 
			secoff=0;
			
			//指针偏移
		   	pBuffer+=secremain;  
			//写地址偏移
			WriteAddr+=secremain;	 
			//字节数递减
		   	NumByteToWrite-=secremain;				
			if(NumByteToWrite>4096)
				//下一个扇区还是写不完
				secremain=4096;	
			else 
				//下一个扇区可以写完了
				secremain=NumByteToWrite;			
		}	 
	} 	 
}



/**
 * @brief 擦除整个芯片
 * @param None
 * @retval None
 * @note 整片擦除时间:
	W25X16:25s 
	W25X32:40s 
	W25X64:40s 
	等待时间超长...
 */
void SPI_Flash_Erase_Chip(void)   
{                     
	//SET WEL 
    SPI_FLASH_Write_Enable();                  
    SPI_Flash_Wait_Busy();  
	//使能器件
  	SPI_FLASH_CS=0;         
	//发送片擦除命令  
    SPI1_ReadWriteByte(W25X_ChipErase);     
	//取消片选
	SPI_FLASH_CS=1;  
	//等待芯片擦除结束
	SPI_Flash_Wait_Busy();   				  
}   




/**
 * @brief 擦除一个扇区
 * @param Dst_Addr 扇区地址 0~511 for w25x16
 * @retval None
 * @note 擦除一个扇区的最少时间:150ms
 */
void SPI_Flash_Erase_Sector(u32 Dst_Addr)   
{   
	Dst_Addr*=4096;
	//SET WEL 
    SPI_FLASH_Write_Enable();                  	 
    SPI_Flash_Wait_Busy(); 
	//使能器件
  	SPI_FLASH_CS=0; 
	//发送扇区擦除指令   
    SPI1_ReadWriteByte(W25X_SectorErase);      
	//发送24bit地址 
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>16));   
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>8));   
    SPI1_ReadWriteByte((u8)Dst_Addr);  
	//取消片选 
	SPI_FLASH_CS=1;   
	//等待擦除完成
    SPI_Flash_Wait_Busy();   				   
}  



/**
 * @brief 等待空闲
 * @param None
 * @retval None
 */
void SPI_Flash_Wait_Busy(void)   
{   
	// 等待BUSY位清空
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   
}  


/**
 * @brief 进入掉电模式
 * @param None
 * @retval None
 */
void SPI_Flash_PowerDown(void)   
{ 
	//使能器件 
  	SPI_FLASH_CS=0;
	//发送掉电命令
    SPI1_ReadWriteByte(W25X_PowerDown);        
	//取消片选   
	SPI_FLASH_CS=1;   
	//等待TPD
    delay_us(3);                                 
}   



/**
 * @brief 唤醒
 * @param None
 * @retval None
 */
void SPI_Flash_WAKEUP(void)   
{  
	//使能器件
  	SPI_FLASH_CS=0;     
	//send W25X_PowerDown command 0xAB 
    SPI1_ReadWriteByte(W25X_ReleasePowerDown);  
	//取消片选
	SPI_FLASH_CS=1;
	//等待TRES1
    delay_us(3);                               
}   



