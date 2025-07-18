#ifndef __OLED_H__
#define __OLED_H__

#include "stm32f1xx_hal.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#define    OLED_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()

#define    GPIOx_OLED_PORT                GPIOB
#define    OLED_SCK_PIN                   GPIO_PIN_8
#define    OLED_SCK_ON()                  HAL_GPIO_WritePin(GPIOx_OLED_PORT, OLED_SCK_PIN, GPIO_PIN_SET)
#define    OLED_SCK_OFF()                 HAL_GPIO_WritePin(GPIOx_OLED_PORT, OLED_SCK_PIN, GPIO_PIN_RESET)
#define    OLED_SCK_TOGGLE()              HAL_GPIO_TogglePin(GPIOx_OLED_PORT, OLED_SCK_PIN)
#define    OLED_SDA_PIN                   GPIO_PIN_9
#define    OLED_SDA_ON()                  HAL_GPIO_WritePin(GPIOx_OLED_PORT, OLED_SDA_PIN, GPIO_PIN_SET)
#define    OLED_SDA_OFF()                 HAL_GPIO_WritePin(GPIOx_OLED_PORT, OLED_SDA_PIN, GPIO_PIN_RESET)
#define    OLED_SDA_TOGGLE()              HAL_GPIO_TogglePin(GPIOx_OLED_PORT, OLED_SDA_PIN)
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void OLED_GPIO_Init(void);
void OLED_Init(void);
void OLED_IIC_Start(void);
void OLED_IIC_Stop(void);
void OLED_Send_Cmd(uint8_t);
void OLED_Send_Data(uint8_t);
void OLED_Set_Column(uint8_t);
void OLED_Set_Page(uint8_t);
void OLED_ALL_Clear(void);
void OLED_ALL_Full(void);
void OLED_IIC_Write(uint8_t);
void OLED_Draw_8_6_ASCII(uint8_t,uint8_t,int);
void OLED_Draw_16_8_ASCII(uint8_t,uint8_t,int);
void OLED_Draw_16_16_Hz(uint8_t,uint8_t,int);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t Color_Turn);
void OLED_ShowNum(uint8_t x,uint8_t y , int32_t num,uint8_t len,uint8_t size2, uint8_t Color_Turn);
void OLED_ShowString(uint8_t x , uint8_t y , uint8_t* string , uint8_t Char_Size ,uint8_t Color_turn);

#endif
