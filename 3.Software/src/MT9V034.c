/**
 * --------------����"��������K60�ײ��"�Ĺ��̣�Smart_Car��-----------------
 * @file MT9V034.c
 * @version 0.0
 * @date 2015-2-7
 * @brief ���ڸù��̵�����
 *
 * ��Ȩ����:�������칤ҵѧԺ ��ʮ���˼����  ����ͷ2�� 
 * Ӳ��ƽ̨:  MK60FX512
 * 
 */
#include "MT9V034.h"
#include "Delay.h"

//SCCBͨ�ŵ�����
/* SCL */
#define SCCB_SCL_PTX        PTB  
#define SCCB_SCL_IOX        GPIO_Pin8
#define SCCB_SCL_SET()      PTB8_O = 1 
#define SCCB_SCL_CLR()      PTB8_O = 0
/* SDA*/
#define SCCB_SDA_PTX        PTB  
#define SCCB_SDA_IOX        GPIO_Pin10
#define SCCB_SDA_O          PTB10_O 
#define SCCB_SDA_I          PTB10_I 
//����SDA�������
#define SCCB_SDA_OUT()      DDRB10 = 1
#define SCCB_SDA_IN()       DDRB10 = 0

/*
 * LPLD_SCCB_Init
 * ��ʼ��SCCB��������
 */
void LPLD_SCCB_Init(void)
{
  GPIO_InitTypeDef sccb;
  //SCL
  sccb.GPIO_PTx = SCCB_SCL_PTX;
  sccb.GPIO_Pins = SCCB_SCL_IOX;
  sccb.GPIO_Dir = DIR_OUTPUT;
  sccb.GPIO_Output = OUTPUT_H;
  sccb.GPIO_PinControl = NULL;
  LPLD_GPIO_Init(sccb);
  //SDA����
  sccb.GPIO_PTx = SCCB_SDA_PTX;
  sccb.GPIO_Pins = SCCB_SDA_IOX;
  sccb.GPIO_Dir = DIR_OUTPUT;
  sccb.GPIO_Output = OUTPUT_H;
  sccb.GPIO_PinControl = INPUT_PULL_UP;
  LPLD_GPIO_Init(sccb);
}

/*
 * LPLD_SCCB_Start
 * SCCB��ʼ�źţ��ڲ�����
 */
static uint8 LPLD_SCCB_Start(void)
{
  SCCB_SDA_O=1;
  SCCB_SCL_SET();
  Delayus(5000);
  
  SCCB_SDA_IN();
  if(!SCCB_SDA_I)
  {
    SCCB_SDA_OUT();	
    return 0;
  }
  SCCB_SDA_OUT();	
  SCCB_SDA_O=0;
  Delayus(5000);
  
  SCCB_SDA_IN();
  if(SCCB_SDA_I) 
  {
    SCCB_SDA_OUT();
    return 0;
  }
  SCCB_SDA_OUT();
  SCCB_SDA_O=0;

  return 1;
}

/*
 * LPLD_SCCB_Stop
 * SCCBֹͣ�źţ��ڲ�����
 */
static void LPLD_SCCB_Stop(void)
{
  SCCB_SCL_CLR();
  SCCB_SDA_O=0;
  Delayus(5000);
  
  SCCB_SCL_SET();
  Delayus(5000);
  SCCB_SDA_O=1;
  Delayus(5000);
}

/*
 * LPLD_SCCB_Stop
 * SCCBӦ���źţ��ڲ�����
 */
static void LPLD_SCCB_Ack(void)
{	
  SCCB_SCL_CLR();
  Delayus(5000);
  
  SCCB_SDA_O=0;
  Delayus(5000);
  
  SCCB_SCL_SET();
  Delayus(5000);
  
  SCCB_SCL_CLR();
  Delayus(5000);
}

/*
 * LPLD_SCCB_NoAck
 * SCCB��Ӧ���źţ��ڲ�����
 */
static void LPLD_SCCB_NoAck(void)
{	
  SCCB_SCL_CLR();
  Delayus(5000);
  SCCB_SDA_O=1;
  Delayus(5000);
  SCCB_SCL_SET();
  Delayus(5000);
  SCCB_SCL_CLR();
  Delayus(5000);
}

/*
 * LPLD_SCCB_WaitAck
 * SCCB�ȴ�Ӧ���źţ��ڲ�����
 */
static uint8 LPLD_SCCB_WaitAck(void) 	
{
  SCCB_SCL_CLR();
  Delayus(5000);
  SCCB_SDA_O=1;	
  Delayus(5000);
  
  SCCB_SCL_SET();
  
  SCCB_SDA_IN();
  Delayus(5000);
  
  if(SCCB_SDA_I)
  {
    SCCB_SDA_OUT();
    SCCB_SCL_CLR();
    return 0;
  }
  SCCB_SDA_OUT();
  SCCB_SCL_CLR();
  return 1;
}

/*
 * LPLD_SCCB_SendByte
 * SCCB�������ݣ��ڲ�����
 */
static void LPLD_SCCB_SendByte(uint8 data) 
{
  uint8 i=8;
  while(i--)
  {
    SCCB_SCL_CLR();
    Delayus(5000);
    if(data&0x80)
    {
      SCCB_SDA_O=1; 
    }
    else 
    {
      SCCB_SDA_O=0;   
    }
    data<<=1;
    Delayus(5000);
    SCCB_SCL_SET();
    Delayus(5000);
  }
  SCCB_SCL_CLR();
}

/*
 * LPLD_SCCB_SendByte
 * SCCB�������ݣ��ڲ�����
 */
static uint8 LPLD_SCCB_ReceiveByte(void)  
{ 
  uint8 i=8;
  uint8 ReceiveByte=0;
  
  SCCB_SDA_O=1;	
  Delayus(5000);
  
  SCCB_SDA_IN();	
  
  while(i--)
  {
    ReceiveByte<<=1;      
    SCCB_SCL_CLR();
    Delayus(5000);
    
    SCCB_SCL_SET();
    Delayus(5000);	
    
    if(SCCB_SDA_I)
    {
      ReceiveByte|=0x01;
    }
    
  }
  SCCB_SDA_OUT();
  SCCB_SCL_CLR();
  
  return ReceiveByte;
}
/*
 * LPLD_SCCB_WriteReg
 * дSCCB�豸�Ĵ���
 * 
 * ����:
 *    reg_addr--�Ĵ�����ַ,8λ
 *    data--��д����,16λ 
 *
 * ���:
 *    1-�ɹ�
 *    0-ʧ��
 */
uint8 LPLD_SCCB_WriteReg(uint8 reg_addr, uint16 data)
{		
  if(!LPLD_SCCB_Start())
  {
    return 0;
  }
  LPLD_SCCB_SendByte(SCCB_DEV_ADR);         
  if(!LPLD_SCCB_WaitAck())
  {
    LPLD_SCCB_Stop(); 
    return 0;
  }
  LPLD_SCCB_SendByte(reg_addr);   
  LPLD_SCCB_WaitAck();	
  LPLD_SCCB_SendByte((uint8)(data>>8));                        //�߰�λ����
  LPLD_SCCB_WaitAck();   
  LPLD_SCCB_SendByte((uint8)(data&0x00ff));           //�Ͱ�λ����
  LPLD_SCCB_WaitAck();  
  LPLD_SCCB_Stop(); 
  return 1;
}									 

/*
 * LPLD_SCCB_ReadReg
 * ��SCCB�豸�Ĵ���
 * 
 * ����:
 *    reg_addr--�Ĵ�����ַ
 *    *data--����������ݵ�ַ
 *
 * ���:
 *    1-�ɹ�
 *    0-ʧ��
 */          
uint8 LPLD_SCCB_ReadReg(uint8 reg_addr, uint16* data)
{
  uint8 data_l;
  if(!LPLD_SCCB_Start())
  {
    return 0;
  }
  LPLD_SCCB_SendByte(SCCB_DEV_ADR); 
  if( !LPLD_SCCB_WaitAck() )
  {
    LPLD_SCCB_Stop(); 
    return 0;
  }
  LPLD_SCCB_SendByte(reg_addr); 
  LPLD_SCCB_WaitAck();	
  LPLD_SCCB_Stop(); 
  
  if(!LPLD_SCCB_Start())
  {
    return 0;
  }
  LPLD_SCCB_SendByte(SCCB_DEV_ADR+1); 
  if(!LPLD_SCCB_WaitAck())
  {
    LPLD_SCCB_Stop(); 
    return 0;
  }
  *data = LPLD_SCCB_ReceiveByte();                //�߰�λ����
  LPLD_SCCB_Ack(); 
  data_l = LPLD_SCCB_ReceiveByte();               //�Ͱ�λ����
  *data = (*data<<8)|data_l;                      //���ܵ���16λ����
  LPLD_SCCB_NoAck();
  
  LPLD_SCCB_Stop();
  return 1;
}
/*-----------------------------------------------------------------------
* MT9V034_Init: ����ͷ��ʼ��
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
void MT9V034_Init()
{
  LPLD_SCCB_Init();
  Delayms(20);
  LPLD_SCCB_WriteReg(MTV_READ_MODE_REG_A,0x033a);       //�޸�Ϊ4��Ƶ�������ʽΪ����
  LPLD_SCCB_WriteReg(MTV_VREF_ADC_REG,0x0007);          //�޸�ADCת���Ĳο���ѹ
//LPLD_SCCB_WriteReg(MTV_MAX_GAIN_REG,0x0032);
}