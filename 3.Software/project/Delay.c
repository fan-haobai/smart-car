/**
 * --------------����"��������K60�ײ��"�Ĺ��̣�Smart_Car��-----------------
 * @file Delay.c
 * @version 0.0
 * @date 2015-2-7
 * @brief ���ڸù��̵�����
 *
 * ��Ȩ����:�������칤ҵѧԺ ��ʮ���˼����  ����ͷ2�� 
 * Ӳ��ƽ̨:  MK60FX512
 * 
 */
#include "common.h"

/*
 * Delayms
 * ��ʱ
 * ������ 
 *    ms--����
 *
 * ���:
 *    ��
 */
void Delayms(uint16 ms)
{
  uint16 i;
  while(ms--)
  {
    for(i=0; i<400; i++)
    {
      asm("nop");
    }
  }
}
/*
 * Delayus
 * ��ʱ
 */
void Delayus(uint16 us)
{	
  while(us) 
    us--; 
}