#ifndef _COMMOND_H_
#define _COMMOND_H_

#define BUFFER_SIZE 1000

#include "stm32f1xx_hal.h"
#include "string.h"

extern uint8_t commond_buffer[50];
extern uint8_t buffer[BUFFER_SIZE];

//uint8_t Commond_Write(char* Data ,uint8_t length);
uint8_t Commond_GetCommond(uint8_t* commond); 
uint16_t Commond_Get_Remain();
uint16_t Commond_GetLength();
uint8_t Commond_Write(char* Data ,uint8_t length);
uint8_t Commond_Read(uint8_t i);
void Commond_AddReadIndex(uint8_t length);
uint8_t Commond_GetCommond_led();  
#endif // !_COMMOND_H_