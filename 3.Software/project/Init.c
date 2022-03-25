/**
 * --------------����"��������K60�ײ��"�Ĺ��̣�Smart_Car��-----------------
 * @file Init.c
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
#include "gui.h"
#include "interrupt.h"
#include "mt9v034.h"

/* �ṹ������ */
GPIO_InitTypeDef gpio_init_struct;    /* GPIO�ṹ�� */
GPIO_InitTypeDef pta_init_struct;     /* ����ͷ���ж� */
GPIO_InitTypeDef ptb_init_struct;     /* ����ͷ�����ź� */ 
DMA_InitTypeDef dma_init_struct;      /* DMA */
FTM_InitTypeDef ftm_init_struct;      /* FTM */
FTM_InitTypeDef qd_init_struct;       /* �������� */
/*-----------------------------------------------------------------------
* init_gpio    : GPIO��ʼ��
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
static void GPIO_Init()
{
  gpio_init_struct.GPIO_PTx = PTC;                                                 
  gpio_init_struct.GPIO_Pins = GPIO_Pin3;
  gpio_init_struct.GPIO_Dir = DIR_INPUT;
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_DIS|IRQC_RI;
  gpio_init_struct.GPIO_Isr = Stop_isr;
  LPLD_GPIO_Init(gpio_init_struct);
  //����
  gpio_init_struct.GPIO_PTx = PTE;                                                //PTE28--KEY1
  gpio_init_struct.GPIO_Pins = GPIO_Pin28;
  gpio_init_struct.GPIO_Dir = DIR_INPUT;
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
  gpio_init_struct.GPIO_PTx = PTA;                                               //PTA5--KEYB��  PTA13--KEYC��  PTA7-��  PTA14--KEYA PTA6--start PTA12--OK
  gpio_init_struct.GPIO_Pins = GPIO_Pin5 | GPIO_Pin6 | GPIO_Pin7| GPIO_Pin12 | GPIO_Pin13;
  gpio_init_struct.GPIO_Dir = DIR_INPUT;
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
  //���뿪��
  gpio_init_struct.GPIO_PTx = PTC;                                                                                
  gpio_init_struct.GPIO_Pins = GPIO_Pin0 | GPIO_Pin1 | GPIO_Pin2 | GPIO_Pin7 | GPIO_Pin11 | GPIO_Pin13 | GPIO_Pin15 | GPIO_Pin16;
  gpio_init_struct.GPIO_Dir = DIR_INPUT;
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
  //LED
  gpio_init_struct.GPIO_PTx = PTE;
  gpio_init_struct.GPIO_Pins = GPIO_Pin24;
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpio_init_struct.GPIO_Output = OUTPUT_H;
  gpio_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
  //BUZZ
  gpio_init_struct.GPIO_PTx = PTB;
  gpio_init_struct.GPIO_Pins = GPIO_Pin18;
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpio_init_struct.GPIO_Output = OUTPUT_L;
  gpio_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct); 
  //����ͷ���ݿڳ�ʼ����PTB0~PTB7
  gpio_init_struct.GPIO_PTx = PTB;
  gpio_init_struct.GPIO_Dir = DIR_INPUT;
  gpio_init_struct.GPIO_Pins = GPIO_Pin0_7;
  gpio_init_struct.GPIO_PinControl = IRQC_DIS|INPUT_PULL_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
  //����ͷ���źŽӿڳ�ʼ����PTB9
  gpio_init_struct.GPIO_PTx = PTB;
  gpio_init_struct.GPIO_Dir = DIR_INPUT;
  gpio_init_struct.GPIO_Pins = GPIO_Pin9;
  gpio_init_struct.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN;      
  gpio_init_struct.GPIO_Isr = VS_isr;
  LPLD_GPIO_Init(gpio_init_struct); 
  //����ͷ���źŽӿڳ�ʼ����PTA26,ע�����¶���һ���ṹ��
  pta_init_struct.GPIO_PTx = PTA;
  pta_init_struct.GPIO_Dir = DIR_INPUT;
  pta_init_struct.GPIO_Pins = GPIO_Pin26;
  pta_init_struct.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN;
  pta_init_struct.GPIO_Isr = HS_isr;
  LPLD_GPIO_Init(pta_init_struct); 
  //����ͷPCLK�źŽӿڳ�ʼ����PTB11,ע�����¶���һ���ṹ��
  ptb_init_struct.GPIO_PTx = PTB;
  ptb_init_struct.GPIO_Dir = DIR_INPUT;
  ptb_init_struct.GPIO_Pins = GPIO_Pin11;
  ptb_init_struct.GPIO_PinControl = IRQC_DMARI|INPUT_PULL_DIS;  
  LPLD_GPIO_Init(ptb_init_struct); 
  
  LPLD_GPIO_ClearIntFlag(PORTB);      //��PORTB�жϱ�־
  enable_irq(PORTB_IRQn);             //ʹ��PORTB�ж�
  enable_irq(PORTC_IRQn);
}
/*-----------------------------------------------------------------------
* ftm_init   : FTM��ʼ��
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
static void FTM_Init()
{
  //��ʼ��FTM���PWM
  ftm_init_struct.FTM_Ftmx = FTM3;	        //ʹ��FTM3ͨ��
  ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	//ʹ��PWMģʽ
  ftm_init_struct.FTM_PwmFreq = 10000;	        //PWMƵ��10000Hz
  LPLD_FTM_Init(ftm_init_struct);
  //��ʼ��FTM���PWM
  ftm_init_struct.FTM_Ftmx = FTM0;	        //ʹ��FTM0ͨ��
  ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	//ʹ��PWMģʽ
  ftm_init_struct.FTM_PwmFreq = 120;	        //PWMƵ��120Hz
  LPLD_FTM_Init(ftm_init_struct);
  /*               
  *�������             
  *            ��             ��
  *        PTE6  PTE7    PTE8   PTE9
  * ��ת    0    pwm      0      pwm
  * ��ת   pwm    0      pwm      0
  *
  */
  LPLD_FTM_PWM_Enable(FTM3,                     //ʹ��FTM3
                      FTM_Ch1,                  //ʹ��Ch1ͨ��
                      0,                        //ռ�ձ�
                      PTE6,                     //ʹ��Ch1ͨ����PTE6����
                      ALIGN_LEFT                //���������
                      ); 
  LPLD_FTM_PWM_Enable(FTM3,                     //ʹ��FTM3
                      FTM_Ch2,                  //ʹ��Ch2ͨ��
                      0,                        //ռ�ձ�                              
                      PTE7,                     //ʹ��Ch2ͨ����PTE7����
                      ALIGN_LEFT                //���������
                      );    
  LPLD_FTM_PWM_Enable(FTM3,                     //ʹ��FTM3
                      FTM_Ch3,                  //ʹ��Ch3ͨ��
                      0,                        //ռ�ձ�                              
                      PTE8,                     //ʹ��Ch3ͨ����PTE8����
                      ALIGN_LEFT                //���������
                      );   
  LPLD_FTM_PWM_Enable(FTM3,                     //ʹ��FTM3
                      FTM_Ch4,                  //ʹ��Ch4ͨ��
                      0,                        //ռ�ձ�                              
                      PTE9,                     //ʹ��Ch4ͨ����PTE9����
                      ALIGN_LEFT                //���������
                      );   
  LPLD_FTM_PWM_Enable(FTM0,                     //ʹ��FTM0
                      FTM_Ch7,                  //ʹ��Ch7ͨ��
                      1865,                     //ռ�ձȣ���ʱ�������           
                                                                                  /* ��    ��    ��       
                                                                                   1665  1865  2065 */
                      PTD7,                     //ʹ��Ch7ͨ����PTD7����
                      ALIGN_LEFT                //���������
                      );  
}
/*-----------------------------------------------------------------------
* dam_init   : DMA��ʼ��
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
static void DMA_Init()
{
  //DMA��������
  dma_init_struct.DMA_CHx = DMA_CH0;                           //CH0ͨ��
  dma_init_struct.DMA_Req = PORTB_DMAREQ;                      //PORTBΪ����Դ
  dma_init_struct.DMA_MajorLoopCnt = H;                        //��ѭ������ֵ���вɼ����������
  dma_init_struct.DMA_MinorByteCnt = 1;                        //��ѭ���ֽڼ�����ÿ�ζ���1�ֽ�
  dma_init_struct.DMA_SourceAddr = (uint32)&PTB->PDIR;         //Դ��ַ��PTB0~7
  dma_init_struct.DMA_DestAddr = (uint32)Image;                //Ŀ�ĵ�ַ�����ͼ�������
  dma_init_struct.DMA_DestAddrOffset = 1;                      //Ŀ�ĵ�ַƫ�ƣ�ÿ�ζ�������1
  dma_init_struct.DMA_AutoDisableReq = TRUE;                   //�Զ���������
  //��ʼ��DMA
  LPLD_DMA_Init(dma_init_struct);
}
/*-----------------------------------------------------------------------
* qd_init   : ���������ʼ��
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
static void QD_Init()
{
  //�����������빦�ܲ���
  qd_init_struct.FTM_Ftmx = FTM1;              //ֻ��FTM1��FTM2���������빦��
  qd_init_struct.FTM_Mode = FTM_MODE_QD;       //�������빦��
  qd_init_struct.FTM_QdMode = QD_MODE_CNTDIR;  //�����ͷ������ģʽ
  //��ʼ��FTM
  LPLD_FTM_Init(qd_init_struct);
  //ʹ��AB������ͨ��
  //PTA8���Ž�A�����롢PTA9���Ž�B������
  LPLD_FTM_QD_Enable(FTM1, PTA8, PTA9);
  //�����������빦�ܲ���
  qd_init_struct.FTM_Ftmx = FTM2;              //ֻ��FTM1��FTM2���������빦��
  qd_init_struct.FTM_Mode = FTM_MODE_QD;       //�������빦��
  qd_init_struct.FTM_QdMode = QD_MODE_CNTDIR;  //�����ͷ������ģʽ
  //��ʼ��FTM
  LPLD_FTM_Init(qd_init_struct);
  //ʹ��AB������ͨ��
  //PTA10���Ž�A�����롢PTA11���Ž�B������
  LPLD_FTM_QD_Enable(FTM2, PTA10, PTA11);
}
/*-----------------------------------------------------------------------
* Init   : ϵͳ��ʼ��
*
* ���룺��
*
* �������
-----------------------------------------------------------------------*/
void Init()
{
  MT9V034_Init();
  GPIO_Init();       //GPIO��ʼ��
  FTM_Init();        //FTM��ʼ��
  DMA_Init();        //DMA��ʼ��
  QD_Init();         //���������ʼ��
  GUI_Init();
}