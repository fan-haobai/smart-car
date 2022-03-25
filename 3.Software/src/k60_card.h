/**
 * @file k60_card.h
 * @version 3.1[By LPLD]
 * @date 2015-01-11
 * @brief ��������K60���İ������ļ�
 *
 * ���Ľ���:�ɸ��ݹ��������޸�
 *
 * **������ÿ�����̵�app�ļ����ڰ������ļ���**
 * ��ͷ�ļ�Ϊ��������K60�ײ��������������ļ���
 * ��������MCU�ͺš���Ƶ��������Ϣ�Ȳ�����
 *
 * ��Ȩ����:�����������µ��Ӽ������޹�˾
 * http://www.lpld.cn
 * mail:support@lpld.cn
 *
 * @par
 * ����������������[LPLD]������ά������������ʹ���߿���Դ���롣
 * �����߿���������ʹ�û��Դ���롣�����μ�����ע��Ӧ���Ա�����
 * ���ø��Ļ�ɾ��ԭ��Ȩ���������������ο����߿��Լ�ע���ΰ�Ȩ�����ߡ�
 * ��Ӧ�����ش�Э��Ļ����ϣ�����Դ���롢���ó��۴��뱾��
 * �������²���������ʹ�ñ��������������κ��¹ʡ��������λ���ز���Ӱ�졣
 * ����������������͡�˵��������ľ���ԭ�����ܡ�ʵ�ַ�����
 * ������������[LPLD]��Ȩ�������߲��ý�������������ҵ��Ʒ��
 * 
 * ����LPLD��MK60DZ10����еĸ��ģ���ΪMK60F15�̼��⡣
 * @ ���ư�
 */
#ifndef __K60_CARD_H__
#define __K60_CARD_H__

/*
 * ϵͳ��Ƶ����(CORE_CLK_MHZ)
 * ��ѡ��Χ:
 * <MK60F15>
 * PLL_100       //100MHz 
 * PLL_120       //120MHz ��MK60F12�Ķ�����Ƶ�������Ϸ�˼�����ɲ��ʱ�
 * PLL_150       //150MHz ��MK60F15�Ķ�����Ƶ�������Ϸ�˼�����ɲ��ʱ�
 * PLL_180       //180MHz
 * PLL_200       //200MHz �������200�����Ⱥ����������˱�����>_>
 */
#if defined(USE_K60F15)
  #define CORE_CLK_MHZ        PLL_180
#endif


/*
 * ����Ƶ�ʶ���(BUS_CLK_MHZ)
 * ��ѡ��Χ:
 *   ������ϵͳ��Ƶ�������鲻����100������100�������ܷɡ���������
 *
*/
#if (defined(USE_K60F15))
  #define BUS_CLK_MHZ         60u
#endif   
/*
 * Flex����Ƶ�ʶ���(FLEXBUS_CLK_MHZ)
 * ��ѡ��Χ:
 *   ������50
 *
*/
#define FLEXBUS_CLK_MHZ     50u 
   
/*
 * FlashƵ�ʶ���(FLASH_CLK_MHZ)
 * ��ѡ��Χ:
 *   ������25
 *
*/
#define FLASH_CLK_MHZ       25u    


/* 
 * ѡ�������Ϣ������еĴ��ںźͲ�����
 */
#define TERM_PORT           UART0
#define TERMINAL_BAUD       115200
#define UART_R_PORT         PTB16
#define UART_T_PORT         PTB17

/*
 * �Ƿ����ô�����ʾ������Ϣ
 * ������ã����İ��������ʱͨ��UART5��ʾ���������Ϣ��ռ��PTE8��PTE9�����˿�
 * 1��ʾ  0����ʾ
 */
#define PRINT_ON_OFF    0

#if (PRINT_ON_OFF == 0)            
  #undef DEBUG_PRINT
#endif
   
/*
 * �Ƿ����ö��Ժ����жϲ����Ϸ���
 * ������ã������Ӳ��ֿ⺯������ʱ�����жϲ����ĺϷ���
 * 1ʹ��  0��ʹ��
 */
#define ASSERT_ON_OFF   0

#if (ASSERT_ON_OFF == 0)            
  #undef DEBUG_ASSERT
#endif

/*
 * �Ƿ�ʹ��uCOS II
 * 1ʹ��  0��ʹ��
 */
#define UCOS_II         0

/*
 * �Ƿ�ʹ��FatFs
 * 1ʹ��  0��ʹ��
 */
#define USE_FATFS       1

/*
 * ѡ��ǰUSB�豸������
 * USB_DEVICE_CLASS_CDC
 * USB_DEVICE_CLASS_HID
 */
//#define USB_DEVICE_CLASS USB_DEVICE_CLASS_CDC

/*
 * ����MCU�ͺ�
 */
#if defined(USE_K60F15)
  #define CPU_MK60F15
#else
  #error "δ����CPU����"
#endif  


#endif /* __K60_CARD_H__ */
