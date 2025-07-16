/*************************************************
// 文件说明:      0.96寸4针OLED驱动代码
// 创 建 人：     mnWu522
// 日期：         2019-12-30
// 修 改 人：                     
// 修改日期：     20xx-xx-xx
*************************************************/
#include "oled.h"
#include "oledfont.h"
#include "tim.h"

//OLED两个引脚初始化
void OLED_GPIO_Init(void)
{ 
 GPIO_InitTypeDef  GPIO_InitStruct;
  
 OLED_GPIO_CLK_ENABLE();
 GPIO_InitStruct.Pin  = OLED_SCK_PIN | OLED_SDA_PIN;
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
 HAL_GPIO_Init(GPIOx_OLED_PORT, &GPIO_InitStruct);
 
 OLED_SDA_OFF();
 OLED_SCK_ON();
}

/**
 * @brief 延时1us
 * 
 * @param us 延时的us数
 */
void Delay_us(uint32_t us) {
    while (us--) {
        volatile uint32_t count = 7;  // 72MHz 下约 1us（需根据实际调整）
        while (count--);
    }
}

//OLED初始化
void OLED_Init(void)
{
 uint8_t i;
 for(i=0;i<25;i++)
 {
  OLED_Send_Cmd(OLED_Init_cmd[i]);
 }
}

//
void OLED_IIC_Start(void)
{
 OLED_SDA_ON();
 Delay_us(1);
 OLED_SCK_ON();
 Delay_us(1);
 OLED_SDA_OFF();
 Delay_us(3);
 OLED_SCK_OFF();
 OLED_IIC_Write(0x78);
}

//
void OLED_IIC_Stop(void)
{
 OLED_SDA_OFF();
 Delay_us(1);
 OLED_SCK_ON();
 Delay_us(3);
 OLED_SDA_ON();
}

//OLED发送指令函数
void OLED_Send_Cmd(uint8_t command)
{
 OLED_IIC_Start();
 OLED_IIC_Write(0x00); 
 OLED_IIC_Write(command);
 OLED_IIC_Stop();
}

//OLED发送显示8点数据函数
void OLED_Send_Data(uint8_t data)
{
 OLED_IIC_Start();
 OLED_IIC_Write(0x40);
 OLED_IIC_Write(data);
 OLED_IIC_Stop();
}

//OLED设置列数 128列 0~127
void OLED_Set_Column(uint8_t column)
{
 OLED_Send_Cmd(0x10|(column>>4));//设置列地址高位
 OLED_Send_Cmd(0x00|(column&0x0f));//设置列地址低位
}

//OLED设置大行数 8大行 0~7 每大行由8小行组成
void OLED_Set_Page(uint8_t line)
{
 OLED_Send_Cmd(0xb0+line);
}

//OLED清屏函数 黑屏
void OLED_ALL_Clear(void)
{
 uint8_t line,column;
 for(line=0;line<8;line++)//page loop
 { 
  OLED_Set_Page(line);
  OLED_Set_Column(0);
  for(column=0;column<128;column++)
  {
   OLED_Send_Data(0x00);
  }
 }
}

//OLED清屏函数 第一大行黄色 其他7大行蓝色
void OLED_ALL_Full(void)
{
 uint8_t line,column;
 for(line=0;line<8;line++)
 { 
  OLED_Set_Page(line);
  OLED_Set_Column(0);
  for(column=0;column<128;column++)
  {
   OLED_Send_Data(0xff);
  }
 }
}

//OLED写入1Byte数据
void OLED_IIC_Write(uint8_t date)
{
 uint8_t i, temp;
 temp = date;
 for(i=0; i<8; i++)
 {
  OLED_SCK_OFF();
  if((temp&0x80) == 0)
  {
   OLED_SDA_OFF();
  }
  else
  {
   OLED_SDA_ON();
  }
  temp = temp << 1;
  Delay_us(1);
  OLED_SCK_ON();
  Delay_us(1);
 }
 OLED_SCK_OFF();
 Delay_us(1);
 OLED_SDA_ON();
 Delay_us(1);
 OLED_SCK_ON();
 Delay_us(1);
 OLED_SCK_OFF();
 Delay_us(1);
}

void OLED_Set_Pos(uint8_t x, uint8_t y)
{
	OLED_Send_Cmd(0xb0+y);	//设置页地址（0~7）
	OLED_Send_Cmd(((x&0xf0)>>4)|0x10); //设置显示位置—列高地址
	OLED_Send_Cmd(x&0x0f);	//设置显示位置—列低地址
}

/**
 * @brief oled显示字符
 * 
 * @param x 行
 * @param y 列
 * @param chr 要显示的字符 
 * @param Char_Size 字符大小
 * @param Color_Turn 颜色 0-代表正常颜色
 */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t Color_Turn)
{
	unsigned char c=0,i=0;
		c=chr-' ';//得到偏移后的值
		if(x>128-1){x=0;y=y+2;}
		if(Char_Size ==16)
		{
			OLED_Set_Pos(x,y);
			for(i=0;i<8;i++)
				{
				  if(Color_Turn)
					  OLED_Send_Data(~(F8X16[c*16+i]));
				  else
					  OLED_Send_Data(F8X16[c*16+i]);
				}
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			    {
				  if(Color_Turn)
					  OLED_Send_Data(~F8X16[c*16+i+8]);
				  else
					  OLED_Send_Data(F8X16[c*16+i+8]);
			    }

			}
	     else
	     {
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
			    {
				  if(Color_Turn)
					  OLED_Send_Data(~F6x8[c][i]);
				  else
					  OLED_Send_Data(F6x8[c][i]);
			    }
		  }
}

unsigned int oled_pow(uint8_t m,uint8_t n)
{
	unsigned int result=1;
	while(n--)result*=m;
	return result;
}

/**
 * @brief oled显示数字
 * 
 * @param x 行
 * @param y 列 最小是2
 * @param num 显示的数字 
 * @param len 长度
 * @param size2  大小 16 代表16*8
 * @param Color_Turn 数字的颜色`
 */
void OLED_ShowNum(uint8_t x,uint8_t y,int32_t num,uint8_t len,uint8_t size2, uint8_t Color_Turn)
{
	uint8_t t,temp;
	uint8_t enshow=0;
	for(t=0;t<len;t++)
	{
    if(num>=0){
		  temp=(num/oled_pow(10,len-t-1))%10;
    }else if(num <0 ){
      temp = ((-num)/oled_pow(10,len-t-1))%10;
      OLED_ShowChar(x,y,'-',size2,Color_Turn);
    }
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2, Color_Turn);
				continue;
			}else enshow=1;

		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2, Color_Turn);
    
	}
}

//OLED显示一个8x6的ASCII码符号
void OLED_Draw_8_6_ASCII(uint8_t line,uint8_t column,int ASCII_num)
{
  int i;
  OLED_Set_Page(line);
  OLED_Set_Column(column);
  for(i=0;i<6;i++)
  {
   OLED_Send_Data(ASCII8x6[ASCII_num][i]);
  }
}

//OLED显示一个16x8的ASCII码符号
void OLED_Draw_16_8_ASCII(uint8_t line,uint8_t column,int ASCII_num)
{
  int i;
  OLED_Set_Page(line);
  OLED_Set_Column(column);
  for(i=0;i<8;i++)
  {
   OLED_Send_Data(ASCII16x8[ASCII_num][i]);
  }
  OLED_Set_Page(line+1);
  OLED_Set_Column(column);
  for(i=8;i<16;i++)
  {
   OLED_Send_Data(ASCII16x8[ASCII_num][i]);
  }
}

//OLED显示一个16x16的汉字符号
void OLED_Draw_16_16_Hz(uint8_t line,uint8_t column,int Hz_num)
{
  int i;
  OLED_Set_Page(line);
  OLED_Set_Column(column);
  for(i=0;i<16;i++)
  {
   OLED_Send_Data(Hz16x16[Hz_num][i]);
  }
  OLED_Set_Page(line+1);
  OLED_Set_Column(column);
  for(i=16;i<32;i++)
  {
   OLED_Send_Data(Hz16x16[Hz_num][i]);
  }
}

void OLED_Draw_char(){

}
