/**
 * --------------����"��������K60�ײ��"�Ĺ��̣�Smart_Car��-----------------
 * @file Interrupt.c
 * @version 0.0
 * @date 2015-2-7
 * @brief ���ڸù��̵�����
 *
 * ��Ȩ����:�������칤ҵѧԺ ��ʮ���˼����  ����ͷ2�� 
 * Ӳ��ƽ̨:  MK60FX512
 * 
 */
#include "common.h"
#include "global.h"

int8 Flag_VS = 0;  

/*-----------------------------------------------------------------------
* Stop_isr: ͣ��
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
void Stop_isr()
{
  if(LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin3))
  {
    if(Stop_Flag == 0)
      Stop_Flag=1;
  }
}
/*-----------------------------------------------------------------------
* VS_isr: ����ͷ���ж�
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
void VS_isr()
{
  if(LPLD_GPIO_IsPinxExt(PORTB, GPIO_Pin9))
  {
     //��⵽����ʼ�źţ�����Ŀ�ĵ�ַ
     LPLD_DMA_LoadDstAddr(DMA_CH0, Image); 
     //�����жϱ�־����ֹ������Ч���ж�
     LPLD_GPIO_ClearIntFlag(PORTA);
     enable_irq(PORTA_IRQn);
  }
}
/*-----------------------------------------------------------------------
* HS_isr: ����ͷ���ж�
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
void HS_isr()
{
  if(LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin26))
  {       
    //��⵽�п�ʼ�źţ�ʹ��DMA����
     if(Flag_VS < V)
     {  
       LPLD_DMA_EnableReq(DMA_CH0);        
     }
     //�����ɼ��������ر��ж�
    else
    {
      //��GPIO�ж� 
      disable_irq(PORTA_IRQn);
      disable_irq(PORTB_IRQn);
      Flag_DispPhoto = 1;              //������ʾͼ��
      Flag_VS = 0;     
    } 
    Flag_VS ++;
  }
}
/*-----------------------------------------------------------------------
* Picture_get: ͼ��Ԥ����
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
void Picture_get(void)
{
  Flag_DispPhoto = 0;
  
  LPLD_GPIO_ClearIntFlag(PORTB);      //������ͷ���жϱ�־
  enable_irq(PORTB_IRQn);             //ʹ������ͷ���ж�   
  
  while(Flag_VS<2);
  
  for(int16 i=0;i<V;i++)
  {
    if(i<V-5)
      while(i>Flag_VS-3);
    if(i>=V-5)
      while(!Flag_DispPhoto);
  
    for(int16 h=0;h<H;h++)
    {
      buff[i*H+h]=Image[i][h];
    }
  }
}