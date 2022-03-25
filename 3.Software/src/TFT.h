/**
 * --------------����"��������K60�ײ��"�Ĺ��̣�Smart_Car��-----------------
 * @file TFT.h
 * @version 0.0
 * @date 2015-2-7
 * @brief ���ڸù��̵�����
 *
 * ��Ȩ����:�������칤ҵѧԺ ��ʮ���˼����  ����ͷ2�� 
 * Ӳ��ƽ̨:  MK60FX512
 * 
 */
#ifndef __TFT_H__
#define __TFT_H__

#include "common.h"
#include "global.h"

/* TFT��ɫ */
#define COLOR_White          0xFFFF
#define COLOR_Black          0x0000
#define COLOR_Gray           0xF7DE
#define COLOR_Blue           0x001F
#define COLOR_Red            0xF800
#define COLOR_Magenta        0xF81F
#define COLOR_Green          0x07E0
#define COLOR_Cyan           0x7FFF
#define COLOR_Yellow         0xFFE0

/* �������� */
void TFT_Init(void);
void TFT_SetCursor( uint8 x, uint8 y );
void TFT_SetWindows( uint8 x0, uint8 y0, uint8 x1, uint8 y1 );
void TFT_SetPoint( uint8 x, uint8 y, uint16 color);
void TFT_FillBackground( uint8 x0, uint8 y0, uint8 x1, uint8 y1, uint16 color );
void TFT_ClearScreen(uint16 color);
void TFT_DrawU8Gray( uint8 x0, uint8 y0, uint8 x1, uint8 y1, uint8 color[][H]);
void TFT_DrawLine( uint8 x0, uint8 y0, uint8 x1, uint8 y1 , uint16 color);
void TFT_ShowChar( uint8 x0, uint8 y0, uint8 ascii, uint16 charColor, uint16 bkColor );
void TFT_ShowNum( uint8 x0, uint8 y0, int32 num, uint16 charColor, uint16 bkColor );
void TFT_ShowString( uint8 x0, uint8 y0, uint8 *str, uint16 charColor, uint16 bkColor );

uint16 TFT_U8GrayToRGB(uint8 color);

#endif /* __TFT_H__ */