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
#ifndef __Flash_H__
#define __Flash_H__

//Flash�궨��
#define SECTOR_Speed   (127)
#define ADDR_Speed     (SECTOR_Speed*4096)  //�ٶ�Flash���� FLASH_TEST_SECTOR*(2048)127*2048=260096
#define SECTOR_Speed1   (126)
#define ADDR_Speed1     (SECTOR_Speed1*4096)  //�ٶ�Flash����
#define SECTOR_Direction   (125)
#define ADDR_Direction     (SECTOR_Direction*4096)//����Flash����
#define SECTOR_CCD   (124)
#define ADDR_CCD     (SECTOR_CCD*4096)//CCD����Flash����
#define SECTOR_Attitude   (123)
#define ADDR_Attitude     (SECTOR_Attitude*4096)//��̬Flash����
#define SECTOR_TAB   (122)
#define ADDR_TAB     (SECTOR_TAB*4096)//ֱ������Flash����
#define SECTOR_Turn  (121)
#define ADDR_Turn     (SECTOR_Turn*4096)//ֱ������Flash����
#define SECTOR_Coefficient  (120)
#define ADDR_Coefficient     (SECTOR_Coefficient*4096)//ֱ������Flash����

void Write_flash(uint32 ADDR,uint8 offset,uint16 date);
uint16 Read_flash(uint32 ADDR,uint8 offset);


#endif