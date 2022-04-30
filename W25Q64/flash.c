#include "flash.h" 
#include "spi.h"
#include "systick.h"   

/**
 * @brief 4KbytesΪһ��Sector
 * @note 16������Ϊ1��Block
 *	W25X16
 *	����Ϊ2M�ֽ�,����32��Block,512��Sector 
 */
u16 SPI_FLASH_TYPE=W25Q64;//Ĭ�Ͼ���25Q64





/**
 * @brief ��ʼ��SPI FLASH��IO��
 * @param None
 * @retval None
 */
void SPI_Flash_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );

	//SPI CS
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;  
	//�����������
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
	//��ʼ��SPI
	SPI1_Init();		  
	//����Ϊ18Mʱ��,����ģʽ
	SPI1_SetSpeed(SPI_BaudRatePrescaler_4);	
	//��ȡFLASH ID.
	SPI_FLASH_TYPE=SPI_Flash_ReadID();
}  




/**
 * @brief ��ȡSPI_FLASH��״̬�Ĵ���
 * @param None
 * @retval ��ȡ��ֵ
 * @note	
 *	BIT7  6   5   4   3   2   1   0
 *	SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 *	SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
 *	TB,BP2,BP1,BP0:FLASH����д��������
 *	WEL:дʹ������
 *	BUSY:æ���λ(1,æ;0,����)
 *	Ĭ��:0x00
 */
u8 SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	//ʹ������ 
	SPI_FLASH_CS=0;          
	//���Ͷ�ȡ״̬�Ĵ�������    
	SPI1_ReadWriteByte(W25X_ReadStatusReg);   
	//��ȡһ���ֽ�  
	byte=SPI1_ReadWriteByte(0Xff);   
	//ȡ��Ƭѡ   
	SPI_FLASH_CS=1;                              
	return byte;   
} 



/**
 * @brief дSPI_FLASH״̬�Ĵ���
 * @param sr Ҫд���ֵ
 * @retval None
 * @note ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
 */
void SPI_FLASH_Write_SR(u8 sr)   
{   
	//ʹ������   
	SPI_FLASH_CS=0; 
	//����дȡ״̬�Ĵ�������
	SPI1_ReadWriteByte(W25X_WriteStatusReg);  
	//д��һ���ֽ�  
	SPI1_ReadWriteByte(sr);  
	//ȡ��Ƭѡ    
	SPI_FLASH_CS=1;                             	      
}   



/**
 * @brief SPI_FLASHдʹ��,��WEL��λ
 * @param None
 * @retval None
 */
void SPI_FLASH_Write_Enable(void)   
{
	//ʹ������  
	SPI_FLASH_CS=0;    
	//����дʹ��  
    SPI1_ReadWriteByte(W25X_WriteEnable);    
	//ȡ��Ƭѡ    
	SPI_FLASH_CS=1;                             	      
} 



/**
 * @brief SPI_FLASHд��ֹ,��WEL����
 * @param None
 * @retval None
 */
void SPI_FLASH_Write_Disable(void)   
{  
	//ʹ������  
	SPI_FLASH_CS=0;  
	//����д��ָֹ��
    SPI1_ReadWriteByte(W25X_WriteDisable);  
	//ȡ��Ƭѡ 
	SPI_FLASH_CS=1;                                	      
} 			    


/**
 * @brief ��ȡоƬID W25X16��ID:0XEF14
 * @param None
 * @retval ��ȡ��ֵ
 */
u16 SPI_Flash_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_FLASH_CS=0;	
	//���Ͷ�ȡID����
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
 * @brief ��ȡSPI FLASH  
 * @param pBuffer ���ݴ洢��
 * @param ReadAddr ��ʼ��ȡ�ĵ�ַ(24bit)
 * @param NumByteToRead Ҫ��ȡ���ֽ���(���65535)
 * @retval None
 * @note ��ָ����ַ��ʼ��ȡָ�����ȵ�����
 */
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	u16 i;    	
	//ʹ������  
	SPI_FLASH_CS=0; 
	//���Ͷ�ȡ����   
    SPI1_ReadWriteByte(W25X_ReadData); 
	//����24bit��ַ
    SPI1_ReadWriteByte((u8)((ReadAddr)>>16));      
    SPI1_ReadWriteByte((u8)((ReadAddr)>>8));   
    SPI1_ReadWriteByte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
		//ѭ������  
        pBuffer[i]=SPI1_ReadWriteByte(0XFF);   
    }
	//ȡ��Ƭѡ 
	SPI_FLASH_CS=1;                                	      
}  



/**
 * @brief SPI��һҳ(0~65535)��д������256���ֽڵ�����
 * @param pBuffer ���ݴ洢��
 * @param WriteAddr ��ʼд��ĵ�ַ(24bit)
 * @param NumByteToWrite Ҫд����ֽ���(���256),
	������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	  
 * @retval None
 * @note ��ָ����ַ��ʼд�����256�ֽڵ�����
 */
void SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
	//SET WEL
    SPI_FLASH_Write_Enable();     
	//ʹ������   
	SPI_FLASH_CS=0;      
	//����дҳ���� 
    SPI1_ReadWriteByte(W25X_PageProgram);  
	//����24bit��ַ
    SPI1_ReadWriteByte((u8)((WriteAddr)>>16));     
    SPI1_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPI1_ReadWriteByte((u8)WriteAddr);   
	//ѭ��д��
    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]); 
	//ȡ��Ƭѡ
	SPI_FLASH_CS=1;   
	//�ȴ�д�����
	SPI_Flash_Wait_Busy();					   
} 



/**
 * @brief �޼���дSPI FLASH 
 * @param pBuffer ���ݴ洢��
 * @param WriteAddr ��ʼд��ĵ�ַ(24bit)
 * @param NumByteToWrite Ҫд����ֽ���(���65535)
 * @retval None
 * @note ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,
	�����ڷ�0XFF��д������ݽ�ʧ��!�����Զ���ҳ���� 
	��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
 */
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	  
	//��ҳʣ����ֽ���
	pageremain=256-WriteAddr%256; 
	//������256���ֽ�
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		//д�������
		if(NumByteToWrite==pageremain)
			break;
		//NumByteToWrite>pageremain
	 	else 
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	
			//��ȥ�Ѿ�д���˵��ֽ���
			NumByteToWrite-=pageremain;	
			//һ�ο���д��256���ֽ�
			if(NumByteToWrite>256)pageremain=256; 
			//����256���ֽ���
			else pageremain=NumByteToWrite; 	  
		}
	};	    
} 




u8 SPI_FLASH_BUF[4096];



/**
 * @brief дSPI FLASH  
 * @param pBuffer ���ݴ洢��
 * @param WriteAddr ��ʼд��ĵ�ַ(24bit)
 * @param NumByteToWrite Ҫд����ֽ���(���65535)  
 * @retval None
 * @note ��ָ����ַ��ʼд��ָ�����ȵ�����
	�ú�������������!
 */
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	
	//������ַ 0~511 for w25x16
	secpos=WriteAddr/4096;
	//�������ڵ�ƫ��
	secoff=WriteAddr%4096;
	//����ʣ��ռ��С
	secremain=4096-secoff;   
	
	//������4096���ֽ�
	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;
	while(1) 
	{	
		//������������������
		SPI_Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);
		//У������
		for(i=0;i<secremain;i++)
		{
			//��Ҫ����  	  
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;
		}
		//��Ҫ����
		if(i<secremain)
		{
			//�����������
			SPI_Flash_Erase_Sector(secpos);
			//����
			for(i=0;i<secremain;i++)	   
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			//д����������  
			SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);

		}
		else 
			//д�Ѿ������˵�,ֱ��д������ʣ������.
			SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain); 	
		//д�������
		if(NumByteToWrite==secremain)
			break;
		//д��δ����
		else
		{
			//������ַ��1
			secpos++;
			//ƫ��λ��Ϊ0 	 
			secoff=0;
			
			//ָ��ƫ��
		   	pBuffer+=secremain;  
			//д��ַƫ��
			WriteAddr+=secremain;	 
			//�ֽ����ݼ�
		   	NumByteToWrite-=secremain;				
			if(NumByteToWrite>4096)
				//��һ����������д����
				secremain=4096;	
			else 
				//��һ����������д����
				secremain=NumByteToWrite;			
		}	 
	} 	 
}



/**
 * @brief ��������оƬ
 * @param None
 * @retval None
 * @note ��Ƭ����ʱ��:
	W25X16:25s 
	W25X32:40s 
	W25X64:40s 
	�ȴ�ʱ�䳬��...
 */
void SPI_Flash_Erase_Chip(void)   
{                     
	//SET WEL 
    SPI_FLASH_Write_Enable();                  
    SPI_Flash_Wait_Busy();  
	//ʹ������
  	SPI_FLASH_CS=0;         
	//����Ƭ��������  
    SPI1_ReadWriteByte(W25X_ChipErase);     
	//ȡ��Ƭѡ
	SPI_FLASH_CS=1;  
	//�ȴ�оƬ��������
	SPI_Flash_Wait_Busy();   				  
}   




/**
 * @brief ����һ������
 * @param Dst_Addr ������ַ 0~511 for w25x16
 * @retval None
 * @note ����һ������������ʱ��:150ms
 */
void SPI_Flash_Erase_Sector(u32 Dst_Addr)   
{   
	Dst_Addr*=4096;
	//SET WEL 
    SPI_FLASH_Write_Enable();                  	 
    SPI_Flash_Wait_Busy(); 
	//ʹ������
  	SPI_FLASH_CS=0; 
	//������������ָ��   
    SPI1_ReadWriteByte(W25X_SectorErase);      
	//����24bit��ַ 
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>16));   
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>8));   
    SPI1_ReadWriteByte((u8)Dst_Addr);  
	//ȡ��Ƭѡ 
	SPI_FLASH_CS=1;   
	//�ȴ��������
    SPI_Flash_Wait_Busy();   				   
}  



/**
 * @brief �ȴ�����
 * @param None
 * @retval None
 */
void SPI_Flash_Wait_Busy(void)   
{   
	// �ȴ�BUSYλ���
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   
}  


/**
 * @brief �������ģʽ
 * @param None
 * @retval None
 */
void SPI_Flash_PowerDown(void)   
{ 
	//ʹ������ 
  	SPI_FLASH_CS=0;
	//���͵�������
    SPI1_ReadWriteByte(W25X_PowerDown);        
	//ȡ��Ƭѡ   
	SPI_FLASH_CS=1;   
	//�ȴ�TPD
    delay_us(3);                                 
}   



/**
 * @brief ����
 * @param None
 * @retval None
 */
void SPI_Flash_WAKEUP(void)   
{  
	//ʹ������
  	SPI_FLASH_CS=0;     
	//send W25X_PowerDown command 0xAB 
    SPI1_ReadWriteByte(W25X_ReleasePowerDown);  
	//ȡ��Ƭѡ
	SPI_FLASH_CS=1;
	//�ȴ�TRES1
    delay_us(3);                               
}   



