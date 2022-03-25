/**
 * --------------����"��������K60�ײ��"�Ĺ��̣�Smart_Car��-----------------
 * @file TFT.c
 * @version 0.0
 * @date 2015-2-7
 * @brief ���ڸù��̵�����
 *
 * ��Ȩ����:�������칤ҵѧԺ ��ʮ���˼����  ����ͷ2�� 
 * Ӳ��ƽ̨:  MK60FX512
 * 
 */
#include "common.h"
#include "Delay.h"
#include "Font_ASC.h"
#include "tft.h"
#include "global.h"

/* TFT��SPI���Ŷ��� */
#define TFT_SPIX    (SPI0)

/* ѡ��TFT MOSI����Ӧ��IO */
#define TFT_MOSI    (PTA16)
/* ѡ��TFT MISO����Ӧ��IO */
#define TFT_MISO    (PTA17)        //δ��
/* ѡ��TFT SCK����Ӧ��IO */
#define TFT_SCK     (PTA15)
/* ѡ��TFT CS����Ӧ��IO */
#define TFT_PCS0    (PTA14)       //δ��

/* ѡ��TFT RESET����Ӧ��IO */
#define TFT_RESET_PTX     (PTE)
#define TFT_RESET_IOX     (GPIO_Pin27)
#define TFT_RESET_SET()    PTE27_O = 1 
#define TFT_RESET_CLR()    PTE27_O = 0

/* ѡ��TFT A0����Ӧ��IO */
#define TFT_A0_PTX        (PTE)
#define TFT_A0_IOX        (GPIO_Pin26)
#define TFT_A0_SET()       PTE26_O = 1 
#define TFT_A0_CLR()       PTE26_O = 0

/*
 * TFT_IO_Init
 * TFT����IO��ʼ��
 * 
 * ������ 
 *    ��
 *
 * ���:
 *    ��
 */
static void TFT_IO_Init(void)
{
  GPIO_InitTypeDef tft_init;
  SPI_InitTypeDef spi_init;
  //RESET 
  tft_init.GPIO_PTx = TFT_RESET_PTX;
  tft_init.GPIO_Pins = TFT_RESET_IOX;
  tft_init.GPIO_Dir = DIR_OUTPUT;
  tft_init.GPIO_Output = OUTPUT_H;
  tft_init.GPIO_PinControl = IRQC_DIS; 
  LPLD_GPIO_Init(tft_init); 
  //A0
  tft_init.GPIO_PTx = TFT_A0_PTX;
  tft_init.GPIO_Pins = TFT_A0_IOX;
  tft_init.GPIO_Dir = DIR_OUTPUT;
  tft_init.GPIO_Output = OUTPUT_L;
  tft_init.GPIO_PinControl = IRQC_DIS; 
  LPLD_GPIO_Init(tft_init); 
  //SPI
  spi_init.SPI_SPIx = TFT_SPIX;
  spi_init.SPI_SckDivider = SPI_SCK_DIV_4;          //4��Ƶ
  spi_init.SPI_Pcs0Pin = TFT_PCS0;
  spi_init.SPI_SckPin  = TFT_SCK;
  spi_init.SPI_MosiPin = TFT_MOSI;
  spi_init.SPI_MisoPin = TFT_MISO;
  spi_init.SPI_TxCompleteIntIsr = NULL;
  spi_init.SPI_QueueEndIntIsr = NULL;
  spi_init.SPI_TxFIFO_FillIntIsr = NULL;
  spi_init.SPI_TxFIFO_UnderflowIntIsr = NULL;
  spi_init.SPI_RxFIFO_DrainIntIsr = NULL;
  spi_init.SPI_RxFIFO_OverflowIntIsr = NULL;
  LPLD_SPI_Init(spi_init);
}
/*
 * TFT_WriteIndex
 * TFTдָ��
 * 
 * ������ 
 *    index--ָ���ַ
 *
 * ���:
 *    ��
 */
static void TFT_WriteIndex(uint8 index)
{
  TFT_A0_CLR();       //дָ��
  LPLD_SPI_Master_Write(TFT_SPIX, index, SPI_PCS0, SPI_PCS_ASSERTED); 
}
/*
 * TFT_WriteData
 * TFTд����
 * 
 * ������ 
 *    data--����
 *
 * ���:
 *    ��
 */
static void TFT_WriteData(uint8 data)
{
  TFT_A0_SET();      //д����
  LPLD_SPI_Master_Write(TFT_SPIX, data, SPI_PCS0, SPI_PCS_ASSERTED); 
}
/*
 * TFT_Init
 * TFT�����ó�ʼ��
 * 
 * ������ 
 *    ��
 *
 * ���:
 *    ��
 */
void TFT_Init()
{
  TFT_IO_Init();

  TFT_RESET_CLR();
  Delayms(20);
  TFT_RESET_SET();
  
  Delayms(10);
  TFT_WriteIndex(0x01);    //Sofeware setting
  Delayms(20);
  TFT_WriteIndex(0x11);   //SLEEP OUT
  
  TFT_WriteIndex(0x3A);   //16 bit  RGB color  format  select
  TFT_WriteData(0x05);    
  
  TFT_WriteIndex(0xB1);   // Frame rate setting   95HZ
  TFT_WriteData(0x00);
  TFT_WriteData(0x06);
  TFT_WriteData(0x03);
  
  TFT_WriteIndex(0x36);   //MV,MX,MY,RGB
  TFT_WriteData(0x60);    //RGB    a0
  
  TFT_WriteIndex(0xB6);   //Display control non-overlap
  TFT_WriteData(0x15);
  TFT_WriteData(0x02);
  
  TFT_WriteIndex(0xB4);   //line inverion
  TFT_WriteData(0x00);
  
  TFT_WriteIndex(0xC0);  //POWER CONTROL 1 GVDD&VCI1 VCI1=2.65V
  TFT_WriteData(0x02);
  TFT_WriteData(0x70);
  
  TFT_WriteIndex(0xC1);  //VGH,VGL
  TFT_WriteData(0x05);
  
  TFT_WriteIndex(0xC2);  //DC/DC SET
  TFT_WriteData(0x01); 
  TFT_WriteData(0x02);
  
  TFT_WriteIndex(0xC5);  //VCOMH=3.925V;VCOML=0.875V
  TFT_WriteData(0x3C);
  TFT_WriteData(0x38);
  
  TFT_WriteIndex(0xFC);
  TFT_WriteData(0x11);
  TFT_WriteData(0x15);
  /***********************GAMMA*************************/
  TFT_WriteIndex(0xE0);  //Positive
  TFT_WriteData(0x09);
  TFT_WriteData(0x16);
  TFT_WriteData(0x09);
  TFT_WriteData(0x20);
  TFT_WriteData(0x21);
  TFT_WriteData(0x1B);
  TFT_WriteData(0x13);
  TFT_WriteData(0x19);
  TFT_WriteData(0x17);
  TFT_WriteData(0x15);
  TFT_WriteData(0x1E);
  TFT_WriteData(0x2B);
  TFT_WriteData(0x04);
  TFT_WriteData(0x05);
  TFT_WriteData(0x02);
  TFT_WriteData(0x1E);
  
  TFT_WriteIndex(0xE1);  //Negative
  TFT_WriteData(0x0B);
  TFT_WriteData(0x14);
  TFT_WriteData(0x08);
  TFT_WriteData(0x1E);
  TFT_WriteData(0x22);
  TFT_WriteData(0x1D);
  TFT_WriteData(0x18);
  TFT_WriteData(0x1E);
  TFT_WriteData(0x1B);
  TFT_WriteData(0x1A);
  TFT_WriteData(0x24);
  TFT_WriteData(0x24);
  TFT_WriteData(0x2B);
  TFT_WriteData(0x06);
  TFT_WriteData(0x02);
  TFT_WriteData(0x1F);
  
  TFT_WriteIndex(0x2A);
  TFT_WriteData(0x00);
  TFT_WriteData(0x00);
  TFT_WriteData(0x00);
  TFT_WriteData(0x9F);
  
  TFT_WriteIndex(0x2B);
  TFT_WriteData(0x00);
  TFT_WriteData(0x00);
  TFT_WriteData(0x00);
  TFT_WriteData(0x7F);
  
  TFT_WriteIndex(0x13);
  
  TFT_WriteIndex(0x2C);
  
  TFT_WriteIndex(0x29);
}
/*
 * TFT_SetCursor
 * ָ�������
 * 
 * ������ 
 *    x--����� y--������
 *
 * ���:
 *    ��
 */
void TFT_SetCursor( uint8 x, uint8 y )
{
  TFT_WriteIndex(0x2A);    
  TFT_WriteData(0x00);
  TFT_WriteData(x);
  
  TFT_WriteIndex(0x2B);    
  TFT_WriteData(0x00);
  TFT_WriteData(y);
}
/*
 * TFT_SetWindows
 * ����һ�����ƴ���
 * 
 * ������ 
 *    x0--����ʼ�� y0--����ʼ�� x1--�н����� y1--�н�����
 *
 * ���:
 *    ��
 */
void TFT_SetWindows( uint8 x0, uint8 y0, uint8 x1, uint8 y1 )
{
  TFT_WriteIndex(0x2A);
  TFT_WriteData(0x00);
  TFT_WriteData(x0);
  TFT_WriteData(0x00);
  TFT_WriteData(x1);
  
  TFT_WriteIndex(0x2B);
  TFT_WriteData(0x00);
  TFT_WriteData(y0);
  TFT_WriteData(0x00);
  TFT_WriteData(y1);
}
/*
 * TFT_SetPoint
 * ����һ��
 * 
 * ������ 
 *    x0--����ʼ�� y0--����ʼ�� color--��ɫ
 *
 * ���:
 *    ��
 */
void TFT_SetPoint( uint8 x, uint8 y, uint16 color)
{ 
  TFT_SetCursor(x,y);
  TFT_WriteIndex(0x2C); 
  TFT_WriteData(color>>8);
  TFT_WriteData(color); 
}
/*
 * TFT_U8GrayToRGB
 * U8�Ҷ���ɫתΪRGB��ɫ
 * 
 * ����:
 *    color--8λ�Ҷ���ɫֵ
 *
 * ���:
 *    16λRGB��ɫֵ
 */
uint16 TFT_U8GrayToRGB(uint8 color)
{
  uint16  r, g, b, rgb;
  
  b = ( color>>3 )  & 0x1f;
  g = ( color>>2 )  & 0x3f;
  r = ( color>>3 )  & 0x1f;
  
  rgb =  (b<<11) + (g<<5) + (r<<0);
  
  return( rgb );
}
/*
 * TFT_FillBackground
 * ���һ��ָ������
 * 
 * ������ 
 *    x0--����ʼ�� y0--����ʼ�� x1--�н����� y1--�н����� color--�����ɫ
 *
 * ���:
 *    ��
 */
void TFT_FillBackground( uint8 x0, uint8 y0, uint8 x1, uint8 y1, uint16 color )
{
  uint8 i,j;
  TFT_SetWindows(x0, y0, x1, y1);
  
  TFT_WriteIndex(0x2C);                     //д��ɫ����
  for(i=0;i<=x1-x0;i++)
    for(j=0;j<=y1-y0;j++)
    {
      TFT_WriteData(color>>8);
      TFT_WriteData(color);
    }
}
/*
 * TFT_ClearScreen
 * ����
 * 
 * ������ 
 *    color--16λ�Ҷ�ͼ������
 *
 * ���:
 *    ��
 */
void TFT_ClearScreen(uint16 color)
{
  TFT_FillBackground(0,0,159,127,color);
}
/*
 * TFT_DrawU8Gray
 * ��ʾһ��ָ����С��U8�Ҷ�ͼ��
 * 
 * ������ 
 *    *color--8λ�Ҷ�ͼ������
 *    w--ͼ���
 *    h--ͼ���
 *
 * ���:
 *    ��
 */
void TFT_DrawU8Gray( uint8 x0, uint8 y0, uint8 x1, uint8 y1, uint8 color[][H])
{
  uint8 w,h;
  uint16 temp;
  TFT_SetWindows(x0,y0,x1,y1);                       //�趨���ڴ�С
  TFT_WriteIndex(0x2C);                             //д��ɫ����
  for(w=0;w<=y1;w++)
    for(h=23;h<=x1+23;h++)    //20
    {
      if(color[w][h] == 0x11)                //��Ǳ���
        temp = COLOR_Red;
      else if(color[w][h] == 0x12)
        temp = COLOR_Blue;
      else if(color[w][h] == 0x13)
        temp = COLOR_Yellow;
      else
        temp = TFT_U8GrayToRGB(color[w][h]);
      TFT_WriteData(temp>>8);                     
      TFT_WriteData(temp);  
    }
}
/*
 * TFT_DrawLine
 * ��һ��ֱ��
 * 
 * ������ 
 *    x0--����ʼ�� y0--����ʼ�� x1--�н����� y1--�н����� color--��ɫ
 *
 * ���:
 *    ��
 */
void TFT_DrawLine( uint8 x0, uint8 y0, uint8 x1, uint8 y1 , uint16 color )
{
  short dx,dy;      /* ����X Y�������ӵı���ֵ */
  short temp;       /* ��� �յ��С�Ƚ� ��������ʱ���м���� */
  
  if( x0 > x1 )     /* X�����������յ� �������� */
  {
    temp = x1;
    x1 = x0;
    x0 = temp;   
  }
  if( y0 > y1 )     /* Y�����������յ� �������� */
  {
    temp = y1;
    y1 = y0;
    y0 = temp;   
  }
  
  dx = x1-x0;       /* X�᷽���ϵ����� */
  dy = y1-y0;       /* Y�᷽���ϵ����� */
  
  if( dx == 0 )     /* X����û������ ����ֱ�� */ 
  {
    do
    { 
      TFT_SetPoint(x0, y0, color);   /* �����ʾ �费ֱ�� */
      y0++;
    }
    while( y1 >= y0 ); 
      return; 
  }
  if( dy == 0 )     /* Y����û������ ��ˮƽֱ�� */ 
  {
    do
    {
      TFT_SetPoint(x0, y0, color);   /* �����ʾ ��ˮƽ�� */
      x0++;
    }
    while( x1 >= x0 ); 
      return;
  }
  /* ����ɭ��ķ(Bresenham)�㷨���� */
  if( dx > dy )                         /* ����X�� */
  {
    temp = 2 * dy - dx;               /* �����¸����λ�� */         
    while( x0 != x1 )
    {
      TFT_SetPoint(x0,y0,color);    /* ����� */ 
      x0++;                         /* X���ϼ�1 */
      if( temp > 0 )                /* �ж����¸����λ�� */
      {
        y0++;                     /* Ϊ�������ڵ㣬����x0+1,y0+1�� */ 
        temp += 2 * dy - 2 * dx; 
      }
      else         
      {
        temp += 2 * dy;           /* �ж����¸����λ�� */  
      }       
    }
    TFT_SetPoint(x0,y0,color);
    }  
    else
    {
      temp = 2 * dx - dy;                      /* ����Y�� */       
      while( y0 != y1 )
      {
        TFT_SetPoint(x0,y0,color);     
        y0++;                 
        if( temp > 0 )           
        {
          x0++;               
          temp+=2*dy-2*dx; 
        }
        else
        {
          temp += 2 * dy;
        }
     } 
  TFT_SetPoint(x0,y0,color);
  }
}
/*
 * TFT_ShowChar
 * ��ָ��������ʾ�ַ�
 * 
 * ������ 
 *    x0--X������
 *    y0--Y������
 *    ascii--ASCI��
 *    charColor--�ַ�������ɫ
 *    bkColor--�ַ�������ɫ
 *
 * ���:
 *    ��
 */
void TFT_ShowChar( uint8 x0, uint8 y0, uint8 ascii, uint16 charColor, uint16 bkColor )
{
  uint16 i, j;
  uint8 tmp_char;
  for( i=0; i<10; i++ )
  {
    tmp_char = ascii_5x10[ascii-32][i];
    for( j=0; j<5; j++ )
    {
      if( (tmp_char >> j) & 0x01 == 0x01 )
      {
        TFT_SetPoint( x0 + j, y0 + i, charColor );  /* �ַ���ɫ */
      }
      else
      {
        TFT_SetPoint( x0 + j, y0 + i, bkColor );  /* ������ɫ */
      }
    }
  }
}
/*
 * TFT_ShowNum
 * ��ָ��������ʾ����(֧�ָ���)
 * 
 * ������ 
 *    x0--X������
 *    y0--Y������
 *    num--����
 *    charColor--�ַ�������ɫ
 *    bkColor--�ַ�������ɫ
 *
 * ���:
 *    ��
 */
void TFT_ShowNum( uint8 x0, uint8 y0, int32 num, uint16 charColor, uint16 bkColor )
{
  uint32 temp;
  uint8 flag=0,t=0;
  if(num == 0)
  {
    TFT_ShowChar(x0,y0,'0',charColor,bkColor);
    return;
  }
  else if(num < 0)
  {
    flag = 1;
    num = -num;
  }
  temp = num;
  while(temp)     //����λ��
  {
    temp /= 10;
    t++;
  }
  while(num)
  { 
    if(flag == 1)
    {
      TFT_ShowChar((x0 + 5*(t--)+5),y0,(num%10) + '0',charColor,bkColor);       //����ʾ��λ������������ʾ
    }
    else
    {
      TFT_ShowChar((x0 + 5*(t--)),y0,(num%10) + '0',charColor,bkColor);       //����ʾ��λ������������ʾ
    }
    num /= 10;
  } 
  if(flag == 1)
  {
    TFT_ShowChar(x0,y0,'-',charColor,bkColor);
  }
}
/*
 * TFT_ShowString
 * ��ָ��������ʾ�ַ���
 * 
 * ������ 
 *    x0--X������
 *    y0--Y������
 *    *str--�ַ���
 *    charColor--�ַ�������ɫ
 *    bkColor--�ַ�������ɫ
 *
 * ���:
 *    ��
 */
void TFT_ShowString( uint8 x0, uint8 y0, uint8 *str, uint16 charColor, uint16 bkColor )
{
  while(*str != '\0')
  {
    TFT_ShowChar(x0, y0, *str, charColor,bkColor);
    x0 += 5;
    str ++;
  }
}

