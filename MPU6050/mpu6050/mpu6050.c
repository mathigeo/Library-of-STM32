#include "MPU6050.h"
#include "system.h"
#include "systick.h"
#include "usart.h"  



/**
 * @brief ��ʼ��MPU6050
 * @param None
 * @retval ����0,�ɹ�
 * 	����,�������
 */
u8 MPU6050_Init(void)
{ 
	u8 res;
	//��ʼ��IIC����
	IIC_Init();
	//��λMPU6050
	MPU6050_Write_Byte(MPU6050_PWR_MGMT1_REG,0X80);	
    delay_ms(100);
	//����MPU6050
	MPU6050_Write_Byte(MPU6050_PWR_MGMT1_REG,0X00);	
	//�����Ǵ�����,��2000dps  ���ٶ�
	MPU6050_Set_Gyro_Fsr(3);
	//���ٶȴ�����,��2g
	MPU6050_Set_Accel_Fsr(0);
	//���ò�����50Hz
	MPU6050_Set_Rate(50);	
	//�ر������ж�
	MPU6050_Write_Byte(MPU6050_INT_EN_REG,0X00);	
	//I2C��ģʽ�ر�
	MPU6050_Write_Byte(MPU6050_USER_CTRL_REG,0X00);	
	//�ر�FIFO
	MPU6050_Write_Byte(MPU6050_FIFO_EN_REG,0X00);	
	//INT���ŵ͵�ƽ��Ч
	MPU6050_Write_Byte(MPU6050_INTBP_CFG_REG,0X80);
	
	res=MPU6050_Read_Byte(MPU6050_DEVICE_ID_REG);
	
	//����ID����
	if(res !=MPU6050_ADDR)
		return 1;
	//����CLKSEL, x������PLL��Ϊʱ��Դ���Ի�ø��߾��ȵ�ʱ��
	MPU6050_Write_Byte(MPU6050_PWR_MGMT1_REG,0X01);	
	//���ٶ��������Ƕ�����
	MPU6050_Write_Byte(MPU6050_PWR_MGMT2_REG,0X00);	
	//���ò�����Ϊ50Hz
	MPU6050_Set_Rate(50);						

	return 0;
}


/**
 * @brief ����MPU6050�����Ǵ����������̷�Χ
 * @param fsr 0,��250dps; 1,��500dps; 2,��1000dps; 3,��2000dps
 * @retval ����0,���óɹ�
 * 	����,����ʧ�� 
 */ 
u8 MPU6050_Set_Gyro_Fsr(u8 fsr)
{
	//���������������̷�Χ
	return MPU6050_Write_Byte(MPU6050_GYRO_CFG_REG,fsr<<3);  
}


/**
 * @brief ����MPU6050���ٶȴ����������̷�Χ
 * @param fsr 0,��2g; 1,��4g; 2,��8g; 3,��16g
 * @retval ����0,���óɹ�
 * 	����,����ʧ�� 
 */   
u8 MPU6050_Set_Accel_Fsr(u8 fsr)
{
	//���ü��ٶȴ����������̷�Χ  
	return MPU6050_Write_Byte(MPU6050_ACCEL_CFG_REG,fsr<<3);
}


/**
 * @brief ����MPU6050�����ֵ�ͨ�˲���
 * @param lpf ���ֵ�ͨ�˲�Ƶ��(Hz)
 * @retval ����0,���óɹ�
 * 	����,����ʧ�� 
 */
u8 MPU6050_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	//�������ֵ�ͨ�˲���  
	return MPU6050_Write_Byte(MPU6050_CFG_REG,data);
}

/**
 * @brief ����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
 * @param rate 4~1000(Hz)
 * @retval ����0,���óɹ�
 * 	����,����ʧ�� 
 */   
u8 MPU6050_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	//�������ֵ�ͨ�˲���
	data=MPU6050_Write_Byte(MPU6050_SAMPLE_RATE_REG,data);	
	//�Զ�����LPFΪ�����ʵ�һ��
 	return MPU6050_Set_LPF(rate/2);	
}


/**
 * @brief �õ��¶�ֵ
 * @param None
 * @retval �¶�ֵ(������100��)
 */
short MPU6050_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU6050_Read_Len(MPU6050_ADDR,MPU6050_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}


/**
 * @brief �õ�������ֵ(ԭʼֵ)
 * @param gx ������x���ԭʼ����(������)
 * @param gy ������y���ԭʼ����(������)
 * @param gz ������z���ԭʼ����(������)
 * @retval ����0,�ɹ�
 * 	����,�������
 */   
u8 MPU6050_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;  
	res=MPU6050_Read_Len(MPU6050_ADDR,MPU6050_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}


/**
 * @brief �õ����ٶ�ֵ(ԭʼֵ)
 * @param gx ������x���ԭʼ����(������)
 * @param gy ������y���ԭʼ����(������)
 * @param gz ������z���ԭʼ����(������)
 * @retval ����0,�ɹ�
 * 	����,�������
 */  
u8 MPU6050_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU6050_Read_Len(MPU6050_ADDR,MPU6050_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}



/**
 * @brief IIC����д
 * @param addr ������ַ 
 * @param reg �Ĵ�����ַ
 * @param len д�볤��
 * @param buf ������
 * @retval ����0,����
 *	����,�������
 */    
u8 MPU6050_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    IIC_Start(); 
	//����������ַ+д����	
	IIC_Send_Byte((addr<<1)|0);
	//�ȴ�Ӧ��
	if(IIC_Wait_Ack())	
	{
		IIC_Stop();		 
		return 1;		
	}
	//д�Ĵ�����ַ
    IIC_Send_Byte(reg);	
	//�ȴ�Ӧ��
    IIC_Wait_Ack();		
	for(i=0;i<len;i++)
	{
		//��������
		IIC_Send_Byte(buf[i]);	
		//�ȴ�ACK
		if(IIC_Wait_Ack())		
		{
			IIC_Stop();	 
			return 1;		 
		}		
	}    
    IIC_Stop();	 
	return 0;	
} 



/**
 * @brief IIC������
 * @param addr ������ַ
 * @param reg Ҫ��ȡ�ļĴ�����ַ
 * @param len Ҫ��ȡ�ĳ���
 * @param buf ��ȡ�������ݴ洢��
 * @retval ����0,����
 * 	����,�������
 */  
u8 MPU6050_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	IIC_Start(); 
	//����������ַ+д����	
	IIC_Send_Byte((addr<<1)|0);
	//�ȴ�Ӧ��
	if(IIC_Wait_Ack())	
	{
		IIC_Stop();		 
		return 1;		
	}
	//д�Ĵ�����ַ
    IIC_Send_Byte(reg);
	//�ȴ�Ӧ��
    IIC_Wait_Ack();		
    IIC_Start();
	//����������ַ+������	
	IIC_Send_Byte((addr<<1)|1);
	//�ȴ�Ӧ�� 
    IIC_Wait_Ack();		
	while(len)
	{
		//������,����nACK 
		if(len==1)*buf=IIC_Read_Byte(0);
		//������,����ACK  
		else *buf=IIC_Read_Byte(1);		
		len--;
		buf++; 
	}   
	//����һ��ֹͣ���� 
    IIC_Stop();	
	return 0;	
}



/**
 * @brief IICдһ���ֽ� 
 * @param reg �Ĵ�����ַ
 * @param data ����
 * @retval ����0,����
 * 	����,�������
 */   
u8 MPU6050_Write_Byte(u8 reg,u8 data) 				 
{ 
    IIC_Start(); 
	//����������ַ+д����	
	IIC_Send_Byte((MPU6050_ADDR<<1)|0);
	//�ȴ�Ӧ��
	if(IIC_Wait_Ack())	
	{
		IIC_Stop();		 
		return 1;		
	}
	//д�Ĵ�����ַ
    IIC_Send_Byte(reg);
	//�ȴ�Ӧ�� 	
    IIC_Wait_Ack();	
	//��������	
	IIC_Send_Byte(data);
	//�ȴ�ACK
	if(IIC_Wait_Ack())	
	{
		IIC_Stop();	 
		return 1;		 
	}		 
    IIC_Stop();	 
	return 0;
}


/**
 * @brief IIC��һ���ֽ� 
 * @param reg �Ĵ�����ַ 
 * @retval ���ض���������
 */
u8 MPU6050_Read_Byte(u8 reg)
{
	u8 res;
    IIC_Start(); 
	//����������ַ+д����	
	IIC_Send_Byte((MPU6050_ADDR<<1)|0);
	//�ȴ�Ӧ�� 
	IIC_Wait_Ack();	
	//д�Ĵ�����ַ
    IIC_Send_Byte(reg);	
	//�ȴ�Ӧ��
    IIC_Wait_Ack();		
    IIC_Start();
	//����������ַ+������
	IIC_Send_Byte((MPU6050_ADDR<<1)|1);	
	//�ȴ�Ӧ�� 
    IIC_Wait_Ack();		
	//��ȡ����,����nACK 
	res=IIC_Read_Byte(0);
	//����һ��ֹͣ���� 
    IIC_Stop();			
	return res;		
}


