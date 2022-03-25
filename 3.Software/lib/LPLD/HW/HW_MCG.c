/**
 * @file HW_MCG.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief MCG�ײ�ģ����غ���
 *
 * ���Ľ���:�������޸�
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
 */
#include "common.h"
#include "HW_MCG.h"


uint32 g_core_clock = -1ul;
uint32 g_bus_clock = -1ul;
uint32 g_flash_clock = -1ul;
uint32 g_flexbus_clock = -1ul;

/*
 * LPLD_PLL_Setup
 * ��ʼ���ں�ʱ�Ӽ�����ϵͳʱ��
 * 
 * ����:
 *    core_clk_mhz--�����ں�ʱ��Ƶ��
 *      |__PLLx--�μ�HAL_MCG.h�е�PLL_option����
 *
 * ���:
 *    �ں�Ƶ�ʣ���λMHz
 */
uint8 LPLD_PLL_Setup(PllOptionEnum_Type core_clk_mhz)
{
  uint8 pll_freq;
  uint8 prdiv, vdiv;
  uint8 core_div, bus_div, flexbus_div, flash_div;
#if (defined(CPU_MK60DZ10))
/*
 *************************************************
  ��LPLDע�⡿MCG�ؼ�ϵ��
  prdiv(PLL��Ƶϵ��): 0~31(1~32)
  vdiv(PLL��Ƶϵ��): 0~31(24~55)
  PLL�ο�ʱ�ӷ�Χ: 2MHz~4MHz
  PLL�ο�ʱ�� = �ⲿ�ο�ʱ��(CPU_XTAL_CLK_HZ)/prdiv
  CoreClk = PLL�ο�ʱ�� x PLL��Ƶϵ�� /OUTDIV1
 *************************************************
 */
 
  // ����MK60DZ10��˵��core_clk_mhz���鲻Ҫ����100����������Ϊ���200
  core_clk_mhz = (PllOptionEnum_Type)(core_clk_mhz>200u?200u:core_clk_mhz);
  
  // ����������Ƶѡ���Ƶ�ͱ�Ƶϵ��
  switch(core_clk_mhz)
  {
  case PLL_48:
    prdiv = 24u;
    vdiv = 0u;
    break;
  case PLL_50:
    prdiv = 24u;
    vdiv = 1u;
    break;
  case PLL_96:
    prdiv = 24u;
    vdiv = 24u;
    break;
  case PLL_100:
    prdiv = 24u;
    vdiv = 26u;
    break;
  case PLL_120:
    prdiv = 19u;
    vdiv = 24u;
    break;
  case PLL_150:
    prdiv = 15u;
    vdiv = 24u;
    break;
  case PLL_180:
    prdiv = 14u;
    vdiv = 30u;
    break;
  case PLL_200:
    prdiv = 12u;
    vdiv = 28u;
    break;
  default:
    return LPLD_PLL_Setup(PLL_96);
  }
#elif (defined(CPU_MK60D10)) 
  //TODO:
  
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
 /*
 *************************************************
  ��LPLDע�⡿MCG�ؼ�ϵ��
  prdiv(PLL��Ƶϵ��): 0~7(1~8)
  vdiv(PLL��Ƶϵ��): 0~31(16~47)
  PLL�ο�ʱ�ӷ�Χ: 8MHz~16MHz
  PLL�ο�ʱ�� = �ⲿ�ο�ʱ��(CPU_XTAL_CLK_HZ)/prdiv
  PLL���ʱ�ӷ�Χ: 90MHz~180MHz
  PLL���ʱ�� = PLL�ο�ʱ�� x vdiv��PLL��Ƶϵ����/2
  CoreClk = PLL���ʱ�� /OUTDIV1
 *************************************************
*/
  
  // ����MK60F12��˵��core_clk_mhz���鲻Ҫ����120����������Ϊ���200
  // ����MK60F15��˵��core_clk_mhz���鲻Ҫ����150����������Ϊ���200
  core_clk_mhz = (PllOptionEnum_Type)(core_clk_mhz>200u?200u:core_clk_mhz);
  // ����������Ƶѡ���Ƶ�ͱ�Ƶϵ��
  switch(core_clk_mhz)
  {
  case PLL_100:
    prdiv = 4u;
    vdiv = 4u;
    break;
  case PLL_120:
    prdiv = 4u;
    vdiv = 8u;
    break;
  case PLL_150:
    prdiv = 4u;
    vdiv = 14u;
    break;
  case PLL_180:
    prdiv = 4u;
    vdiv = 20u;
    break;
  case PLL_200:
    prdiv = 3u;
    vdiv = 0u;
    break;
  default:
    return LPLD_PLL_Setup(PLL_120);
  } 
#endif
  
  pll_freq = core_clk_mhz * 1;
  core_div = 0;
  if((bus_div = (uint8)(core_clk_mhz/BUS_CLK_MHZ - 1u)) == (uint8)-1)
  {
    bus_div = 0;
  }
  else if(core_clk_mhz/(bus_div+1) > BUS_CLK_MHZ)
  {
    bus_div += 1;
  }
  if((flexbus_div = (core_clk_mhz/FLEXBUS_CLK_MHZ - 1u)) == (uint8)-1)
  {
    flexbus_div = 0;
  }
  else if(core_clk_mhz/(flexbus_div+1) > FLEXBUS_CLK_MHZ)
  {
    flexbus_div += 1;
  }
  if((flash_div = (core_clk_mhz/FLASH_CLK_MHZ - 1u)) == (uint8)-1)
  {
    flash_div = 0;
  }
  else if(core_clk_mhz/(flash_div+1) > FLASH_CLK_MHZ)
  {
    flash_div += 1;
  }
 
#if (defined(CPU_MK60DZ10)) 
  // ������踴λ�� MCG ģ��Ĭ��Ϊ FEI ģʽ
  // �����ƶ��� FBE ģʽ
  MCG->C2 = 0;
  // ������ʼ����ɺ�,�ͷ�����״̬�µ� oscillator �� GPIO 
  SIM->SCGC4 |= SIM_SCGC4_LLWU_MASK;
  LLWU->CS |= LLWU_CS_ACKISO_MASK;
  // ѡ���ⲿ oscilator ���ο���Ƶ�� and ���� IREFS �����ⲿosc
  // CLKS=2, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
  MCG->C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);  
  while (MCG->S & MCG_S_IREFST_MASK){}; // �ȴ��ο�ʱ������
  while (((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2){}; // �ȴ�ʱ��״̬��ʾΪ�ⲿ�ο�ʱ��(ext ref clk)
  // ����FBEģʽ
  // ���� PLL �ο���Ƶ��, PLLCLKEN=0, PLLSTEN=0, PRDIV=5
  // �þ���Ƶ����ѡ�� PRDIV ֵ. ������Ƶ�ʾ����ʱ��֧��
  // ���� 2MHz �Ĳο�ʱ�Ӹ� PLL.
  MCG->C5 = MCG_C5_PRDIV(prdiv); // ���� PLL ƥ�侧��Ĳο���Ƶ�� 
  // ȷ��MCG_C6���ڸ�λ״̬,��ֹLOLIE��PLL����ʱ�ӿ�����,��PLL VCO��Ƶ��
  MCG->C6 = 0x0;
  //����ϵͳʱ�ӷ�Ƶϵ��
  LPLD_Set_SYS_DIV(core_div, bus_div, flexbus_div, flash_div);  
  //���ñ�Ƶϵ��
  MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(vdiv); 
  while (!(MCG->S & MCG_S_PLLST_MASK)){}; // wait for PLL status bit to set
  while (!(MCG->S & MCG_S_LOCK_MASK)){}; // Wait for LOCK bit to set
  // �Ѿ�����PBEģʽ
  // ����CLKS ����PEEģʽ
  MCG->C1 &= ~MCG_C1_CLKS_MASK;
  // Wait for clock status bits to update
  while (((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3){};
  // �Ѿ�����PEEģʽ
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  if (PMC->REGSC &  PMC_REGSC_ACKISO_MASK)
        PMC->REGSC |= PMC_REGSC_ACKISO_MASK;
  /*ע�⣺PLL��ʼ����������ϵͳʱ�ӷ�Ƶ��
    ����ϵͳʱ�ӷ�Ƶ������PLL֮ǰ����*/ 
  SIM->CLKDIV1 = ( 0
                  | SIM_CLKDIV1_OUTDIV1(core_div)   //�����ں˷�Ƶ
                  | SIM_CLKDIV1_OUTDIV2(bus_div)   //���������Ƶ
                  | SIM_CLKDIV1_OUTDIV3(flexbus_div)   //����FlexBus��Ƶ
                  | SIM_CLKDIV1_OUTDIV4(flash_div) );//����FLASH��Ƶ
  //��ʼ��������ʱ�ӣ�ϵͳ�ں���Ƶ������ʱ�ӡ�FlexBusʱ�ӡ�Flashʱ��
  // ������踴λ�� MCG ģ��Ĭ��Ϊ FEI ģʽ
  // �����ƶ��� FBE ģʽ
  MCG->C2 = MCG_C2_RANGE0(1);
  // ѡ���ⲿ oscilator ���ο���Ƶ�� and ���� IREFS �����ⲿosc
  // CLKS=2, FRDIV=5, IREFS=0, IRCLKEN=0, IREFSTEN=0
  MCG->C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(5);
  while (MCG->S & MCG_S_IREFST_MASK){}; // �ȴ��ο�ʱ������
  while (((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2){}; // �ȴ�ʱ��״̬��ʾΪ�ⲿ�ο�ʱ��(ext ref clk)
  // ����FBEģʽ
  // ���� PLL �ο���Ƶ��, PLLCLKEN=0, PLLSTEN=0, PRDIV
  // �þ���Ƶ����ѡ�� PRDIV ֵ. ������Ƶ�ʾ����ʱ��֧��
  // ���� 10MHz �Ĳο�ʱ�Ӹ� PLL.
  MCG->C6 |= MCG_C6_CME0_MASK;
  MCG->C5 = MCG_C5_PRDIV0(prdiv); // ���� PLL ƥ�侧��Ĳο���Ƶ��
  MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(vdiv); 
  while (!(MCG->S & MCG_S_PLLST_MASK)){}; // wait for PLL status bit to set
  while (!(MCG->S & MCG_S_LOCK0_MASK)){}; // Wait for LOCK bit to set
  // �Ѿ�����PBEģʽ
  // ����CLKS ����PEEģʽ
  MCG->C1 &= ~MCG_C1_CLKS_MASK;
  // Wait for clock status bits to update
  while (((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3){};
  // �Ѿ�����PEEģʽ
#endif  
  return pll_freq;
} 

/*
 * LPLD_Set_SYS_DIV
 * ����ϵͳʼ�շ�Ƶ
 *
 * ˵��:
 * ��δ�����������RAM�У�Ŀ���Ƿ�ֹ�����ܷɣ�����ٷ��ĵ�errata e2448.
 * ��Flashʱ�ӷ�Ƶ�ı��ʱ��FlashԤ��ȡ�������.
 * ��ֹ��Flash���������´���.
 * ��Ԥ��ȡ������ʹ��֮ǰ������ʱ�ӷ�Ƶ�ı����һ��С����ʱ.
 *
 * ����:
 *    outdiv1~outdiv4--�ֱ�Ϊcore, bus, FlexBus, Flashʱ�ӷ�Ƶϵ��
 */
RAMFUNC void LPLD_Set_SYS_DIV(uint32 outdiv1, uint32 outdiv2, uint32 outdiv3, uint32 outdiv4)
{
  uint32 temp_reg;
  uint8 i;
  
  temp_reg = FMC->PFAPR; // ���� FMC_PFAPR �Ĵ���
  
  // ���� M0PFD �� M7PFD Ϊ 1 ����Ԥ�ȶ�ȡ
  FMC->PFAPR |= FMC_PFAPR_M7PFD_MASK | FMC_PFAPR_M6PFD_MASK | FMC_PFAPR_M5PFD_MASK
             | FMC_PFAPR_M4PFD_MASK | FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK
             | FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;
  
  // ����ʱ�ӷ�ƵΪ����ֵ  
  SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(outdiv1) | SIM_CLKDIV1_OUTDIV2(outdiv2) 
              | SIM_CLKDIV1_OUTDIV3(outdiv3) | SIM_CLKDIV1_OUTDIV4(outdiv4);

  // ��ʱһС��ʱ��ȴ��ı�
  for (i = 0 ; i < outdiv4 ; i++)
  {}
  
  FMC->PFAPR = temp_reg; // �ظ�ԭ�ȵ� FMC_PFAPR �Ĵ���ֵ
  
  return;
} // set_sys_dividers

/*******************************************
*         MK60F12 & 15
*  MCGOUT = PLL output frequency/2
*  PLL = (Crystal / PRDIV0 ) * VDIV0
********************************************
PRDIV0 Divide Factor
********************************************
PRDIV0  Va
********************************************
000     1
001     2
010     3
011     4
100     5
101     6
110     7
111     8
********************************************
VDIV0 MultiplyFactor
********************************************
VDIV0 Va VDIV0 Va VDIV0 Va VDIV0 Va
********************************************
00000 16 01000 24 10000 32 11000 40
00001 17 01001 25 10001 33 11001 41
00010 18 01010 26 10010 34 11010 42
00011 19 01011 27 10011 35 11011 43
00100 20 01100 28 10100 36 11100 44
00101 21 01101 29 10101 37 11101 45
00110 22 01110 30 10110 38 11110 46
00111 23 01111 31 10111 39 11111 47
********************************************/

/********************************************
*             MK60DZ10
*  MCGOUT = PLL output frequency
*  PLL = (Crystal / PRDIV0 ) * VDIV0
*********************************************
PRDIV DivideFactor
*********************************************
PRDIV0 Va PRDIV0 Va PRDIV0 Va PRDIV0 Va
*********************************************
00000  1  01000   9 10000  17 11000  25
00001  2  01001  10 10001  18 11001  Reserved
00010  3  01010  11 10010  19 11010  Reserved
00011  4  01011  12 10011  20 11011  Reserved
00100  5  01100  13 10100  21 11100  Reserved
00101  6  01101  14 10101  22 11101  Reserved
00110  7  01110  15 10110  23 11110  Reserved
00111  8  01111  16 10111  24 11111  Reserved
*********************************************
VDIV MultiplyFactor
*********************************************
VDIV0 Va VDIV0 Va VDIV0 Va VDIV0 Va
*********************************************
00000 24 01000 32 10000 40 11000 48
00001 25 01001 33 10001 41 11001 49
00010 26 01010 34 10010 42 11010 50
00011 27 01011 35 10011 43 11011 51
00100 28 01100 36 10100 44 11100 52
00101 29 01101 37 10101 45 11101 53
00110 30 01110 38 10110 46 11110 54
00111 31 01111 39 10111 47 11111 55
*********************************************/
