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
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "common.h"


#define BUZZ_ON         LPLD_GPIO_Output_b(PTB,18,1)
#define BUZZ_OFF        LPLD_GPIO_Output_b(PTB,18,0) 

#define H              188                             /* ͼ���� */
#define V              120                             /* ͼ��߶� */
#define Start_Row      23                             //ͼ����ʼ��
#define End_Row        183                            //ͼ���������
#define Start_Column   0                              //ͼ����ʼ��
#define End_Column     120                             //ͼ���������

#define BUFF_SIZE   512*45
extern uint8 buff[BUFF_SIZE];

extern uint8 Image[V][H];
extern uint8 Image_show[V][H];
extern uint32 Which_pic;
extern uint8 Flag_DispPhoto;
extern uint8 Stop_Flag;
extern uint8 printf_flag;
extern uint8 frame;
extern int16 D_Pwm_Center;                                //���������У��
extern int16 D_Kp_a;
extern int16 D_Kp_b;
extern int16 D_Kp;
extern int16 D_Kd;
extern int32 D_PWM;

extern int16 S_L_Kp;                                        //�Ŵ�10��
extern int16 S_L_Ki;
extern int16 S_L_Kd;
extern int16 S_R_Kp;                                    
extern int16 S_R_Ki;                                     
extern int16 S_R_Kd;

extern int32 S_L_PWM;
extern int32 S_R_PWM;

extern int16 Get_L_Speed; 
extern int16 Get_R_Speed;

extern int16 Speed;

extern int16 Straight_High_Speed;            //ֱ������ٶ�
extern int16 Straight_Low_Speed;             //ֱ������ٶ�

extern int16 S_C_High_Speed;                 //ֱ����������ٶ�
extern int16 S_C_Low_Speed;                  //ֱ����������ٶ�

extern int16 Curve_High_Speed;                //�������ٶ�
extern int16 Curve_Low_Speed;                 //�������ٶ�


extern int16 S_a;
extern int16 S_b;

extern int16 Set_L_Speed;
extern int16 Set_R_Speed;

extern uint16 Send_Data[4];                                 //��������

extern int16 Line_Array[End_Column-Start_Column][3];        //�洢���б��ߺ�����-->��ʽ��Line_Array[][0]--�����     Line_Array[][1]--����   Line_Array[][2]--�ұ���
extern int16 Center_Line;
extern int16 Active_Lines;
extern int16 Str_Cur_Offset; 
extern int8 Left_Flag;
extern int8 Right_Flag;
extern int8 Str_Flag;
extern uint8 Track_Type; 

#endif