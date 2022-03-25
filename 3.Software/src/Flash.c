/**
 * --------------����"��������K60�ײ��"�Ĺ��̣�Smart_Car��-----------------
 * @file Global.h
 * @version 0.0
 * @date 2015-2-7
 * @brief ���ڸù��̵�����
 *
 * ��Ȩ����:�������칤ҵѧԺ ��ʮ���˼����  ����ͷ2�� 
 * Ӳ��ƽ̨:  MK60FX512
 * 
 */
#include "common.h"
#include "Flash.h"

/*
 * ���ݴ洢Flash����
   *Ҫд���ADDR������
   *XҪ�洢�����ݱ���
   *��Ҫ���ƺ궨��
    //Flash�궨��
     #define FLASH_TEST_SECTOR   (127)
     #define FLASH_TEST_ADDR     (FLASH_TEST_SECTOR*2048)// FLASH_TEST_SECTOR*(2048)127*2048=260096
     #define DATA_SIZE           (2)���ڴ����֧��uint16�͵��ǻ���Ҳ������
     DNΪ
     �������Ϊ��λ��0,4,8,12,16,20��4�ı���
     FXΪ
     �������Ϊ��λ��0,8,16,24,32,40��8�ı���
 */
void Write_flash(uint32 ADDR,uint8 offset,uint16 date)
{
  //Flash�������� 
  uint8 write_buffer1[2]; //����д������
  uint32 addr;
  addr=ADDR+offset;
  
  write_buffer1[0]=date/256;
  write_buffer1[1]=date%256;
  LPLD_Flash_ByteProgram((uint32)addr, (uint32*)write_buffer1, 2);
}


/*
 * ���ݶ�ȡFlash����
  *mҪ��ȡ��������
  *���ڲ���Ϊ��ȡ�洢���ݵ�ֵ
 */

uint16 Read_flash(uint32 ADDR,uint8 offset)
{
  //Flash�������� 
  uint8 read_buffer1[2];  //�����������
  uint8 *ptr;
  int8 len;
  uint16 utter;//����
  
  ptr = (uint8*)(ADDR+offset);
  for( len = 0 ; len < 2 ; len++)
  {
    read_buffer1[len] = *(ptr + len);
  }
  
  utter=read_buffer1[0]*256+read_buffer1[1];
  return utter;
}
