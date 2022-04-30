#include "24cxx.h" 
#include "systick.h"


/**
 * @brief ��ʼ��IIC�ӿ�
 * @param None
 * @retval None
 */
void AT24CXX_Init(void)
{
	IIC_Init();
}


/**
 * @brief ��AT24CXXָ����ַ����һ������
 * @param ReadAddr ��ʼ�����ĵ�ַ  
 * @retval ����������
 */
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		/*����д����*/
		IIC_Send_Byte(0XA0);	   
		IIC_Wait_Ack();
		/*���͸ߵ�ַ*/
		IIC_Send_Byte(ReadAddr>>8);
		IIC_Wait_Ack();		 
	}
	else 
	{
		/*����������ַ0XA0,д����*/	 
		IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   
	}

	IIC_Wait_Ack(); 
	/*���͵͵�ַ*/
    IIC_Send_Byte(ReadAddr%256);   
	IIC_Wait_Ack();	    
	IIC_Start();  	
	/*�������ģʽ*/		
	IIC_Send_Byte(0XA1);              
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);	
	/*����һ��ֹͣ����*/
    IIC_Stop();   
	return temp;
}


/**
 * @brief ��AT24CXXָ����ַд��һ������
 * @param WriteAddr д�����ݵ�Ŀ�ĵ�ַ    
 * @param DataToWrite Ҫд�������
 * @retval None
 */
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		/*����д����*/
		IIC_Send_Byte(0XA0);	    
		IIC_Wait_Ack();
		/*���͸ߵ�ַ*/
		IIC_Send_Byte(WriteAddr>>8);
 	}
	else
	{
		/*����������ַ0XA0,д���� */
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   
	}	 
	IIC_Wait_Ack();	   
	/*���͵͵�ַ*/
    IIC_Send_Byte(WriteAddr%256);   
	IIC_Wait_Ack(); 
	/*�����ֽ�*/
	IIC_Send_Byte(DataToWrite);     					   
	IIC_Wait_Ack();  
	/*����һ��ֹͣ����*/
    IIC_Stop();
	delay_ms(10);	 
}


/**
 * @brief ��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
 * @param WriteAddr ��ʼд��ĵ�ַ  
 * @param DataToWrite ���������׵�ַ
 * @param Len Ҫд�����ݵĳ���2,4
 * @retval None
 * @note �ú�������д��16bit����32bit������.
 */
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}


/**
 * @brief ��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
 * @param ReadAddr ��ʼ�����ĵ�ַ 
 * @param Len Ҫ�������ݵĳ���2,4
 * @retval ����
 * @note �ú������ڶ���16bit����32bit������.
 */
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

/**
 * @brief ���AT24CXX�Ƿ�����
 * @param None
 * @retval ״̬
 *	����1:���ʧ��
 *	����0:���ɹ�
 * @note ��������24XX�����һ����ַ(255)���洢��־��
 *	���������24Cϵ��,�����ַҪ�޸�
 */
u8 AT24CXX_Check(void)
{
	u8 temp;
	/*����ÿ�ο�����дAT24CXX*/
	temp=AT24CXX_ReadOneByte(255);		   
	if(temp==0X55)
	{
		return 0;	
	}		
	/*�ų���һ�γ�ʼ�������*/
	else
	{
		
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}


/**
 * @brief ��AT24CXX�����ָ����ַ��ʼ����ָ������������
 * @param ReadAddr ��ʼ�����ĵ�ַ ��24c02Ϊ0~255
 * @param pBuffer ���������׵�ַ
 * @param NumToRead Ҫ�������ݵĸ���
 * @retval None
 */
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  

/** 
 * @brief ��AT24CXX�����ָ����ַ��ʼд��ָ������������
 * @param WriteAddr ��ʼд��ĵ�ַ ��24c02Ϊ0~255
 * @param pBuffer ���������׵�ַ
 * @param NumToWrite Ҫд�����ݵĸ���
 * @retval None
 */
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











