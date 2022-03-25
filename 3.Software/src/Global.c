/**
 * --------------����"��������K60�ײ��"�Ĺ��̣�Smart_Car��-----------------
 * @file Global.c
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

uint8 buff[BUFF_SIZE];

uint8 Image[V][H];                   //ͼ��
uint8 Image_show[V][H];            //ͼ��
uint32 Which_pic = 0;                //Ҫ����ĵڼ�֡ͼƬ856
uint8 printf_flag;       
uint8 frame;

uint8 Flag_DispPhoto = 0;
uint8 Stop_Flag = 1;

int16 D_Pwm_Center = 1865;              //���������У��
int16 D_Kp_a = 180;
int16 D_Kp_b = 28;
int16 D_Kp;                     
int16 D_Kd = 100;                      
int32 D_PWM;                          //���PWM����ֵ

int16 S_L_Kp = 300;                  
int16 S_L_Ki = 10;                     
int16 S_L_Kd = 20;                    

int16 S_R_Kp = 300;                  
int16 S_R_Ki = 10;                    
int16 S_R_Kd = 20;                     

int32 S_L_PWM = 0;                    //��������PWMֵ
int32 S_R_PWM = 0;                    //�ҵ������PWMֵ

int16 Get_L_Speed = 0;                //����ʵ���ٶ�
int16 Get_R_Speed = 0;                //����ʵ���ٶ�

int16 Speed;

int16 Straight_High_Speed = 300;        //ֱ������ٶ�
int16 Straight_Low_Speed = 250;         //ֱ������ٶ�

int16 S_C_High_Speed = 250;             //ֱ����������ٶ�
int16 S_C_Low_Speed = 155;              //ֱ����������ٶ�

int16 Curve_High_Speed = 200;           //�������ٶ�
int16 Curve_Low_Speed = 125;            //�������ٶ�

int16 S_a;                             //����ٶȶ��ι�ϵ�Ķ�����
int16 S_b;                             //����ٶȶ��ι�ϵ�ĳ�����

int16 Set_L_Speed = 0;                 //�����ٶ�
int16 Set_R_Speed = 0; 

uint16 Send_Data[4] = {0};                                 //��������

int16 Line_Array[End_Column-Start_Column][3];              //�洢���б��ߺ�����-->��ʽ��Line_Array[][0]--�����     Line_Array[][1]--����   Line_Array[][2]--�ұ���
int16 Center_Line = 94;                                   //���� 
int16 Active_Lines = 0;                                    //��Ч����
int16 Str_Cur_Offset = 0;
int8 Left_Flag = 0;
int8 Right_Flag = 0;
int8 Str_Flag = 0;
uint8 Track_Type = 0;                                      //��������
