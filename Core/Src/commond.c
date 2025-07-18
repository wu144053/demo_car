#include "commond.h"

//循环缓冲区的大小
//#define BUFFER_SIZE 200

#define PACK_LEAST 30

//循环缓冲区
uint8_t buffer[BUFFER_SIZE];
//写指针
uint8_t write_index;
//读指针
uint8_t read_index;

//读取的指令数组
uint8_t commond_buffer[50];

uint8_t pack_head;
/**
 * @brief 增加读索引
 * 
 * @param length 缓冲区要增加的长度
 */
void Commond_AddReadIndex(uint8_t length){
    read_index += length;
    read_index %= BUFFER_SIZE;
}

uint8_t Commond_Read(uint8_t i){
    uint8_t index = i % BUFFER_SIZE;
    return buffer[index];
}

/**
 * @brief 计算缓冲区以写区间
 * 
 * @return uint16_t 
 */
uint16_t Commond_GetLength(){
    return (write_index + BUFFER_SIZE - read_index)%BUFFER_SIZE;
}

/**
 * @brief 计算剩余存储空间
 * 
 * @return uint16_t 
 */
uint16_t Commond_Get_Remain(){
    return BUFFER_SIZE - Commond_GetLength();
}

/**
 * @brief 循环缓冲区写入
 * 
 * @param data 将要写入的数据  
 * @param length 写入数据的长度
 * @return uint8_t 返回写入数据的长度
 */
uint8_t Commond_Write(char* Data ,uint8_t length){
    if( length > Commond_Get_Remain())
        return 0;
    if(write_index + length < BUFFER_SIZE){
        memcpy(buffer+write_index,Data,length);
        write_index += length;
    }else {
        uint8_t firstlength = BUFFER_SIZE - write_index ;
        memcpy (buffer+write_index , Data , firstlength);
        memcpy(buffer ,Data + firstlength , length - firstlength);
        write_index = length-firstlength;
    }
    return length;
}

/**
 * @brief 尝试获取一条指令
 * 
 * @param commond 接收数据的数组
 * @return uint8_t 
 */
uint8_t Commond_GetCommond(uint8_t* commond){   
    while(1){
    if(Commond_GetLength( ) < PACK_LEAST){
        return 0;
    }
    if(Commond_Read(read_index)!= pack_head){
        //将读指针向后移一格
        Commond_AddReadIndex(1);
        continue;
    }
    uint8_t length = Commond_Read(read_index+1);
    if(Commond_GetLength() < length){
        return 0 ;
    }
    uint8_t sum = 0;
    for(uint8_t i = 0 ; i < length-1 ; i ++){
        sum += Commond_Read(read_index + i);
    }
    if(sum != Commond_Read(read_index + length - 1)){
        Commond_AddReadIndex(1);
        continue;
    }
    for(uint8_t i = 0 ; i < length ; i ++){
        commond_buffer[i] = Commond_Read(read_index + i);
    }
    Commond_AddReadIndex(length);
    return length ;
    }
}

/**
 * @brief 
 * 
 * @param commond 
 * @return uint8_t 
 */
uint8_t Commond_GetCommond_led(){   
    while(1){
    if(Commond_GetLength() < 10){
        return 0;
    }
    if(Commond_Read(read_index)!= 'D'){
        //将读指针向后移一格
        Commond_AddReadIndex(1);
        continue;
    }
    uint8_t length = 0;
    for(uint8_t i = 0 ; i < 40 ; i ++){
        length ++;
        if(Commond_Read(read_index + i) == '$'){
            break;
        }
        if(i > 40){
            Commond_AddReadIndex(1);
            continue;
        }
    }
    if(Commond_GetLength() < length){
        return 0 ;
    }
    for(uint8_t i = 0 ; i < length ; i ++){
        commond_buffer[i] = Commond_Read(read_index + i);
    }
    Commond_AddReadIndex(length);
    return length ;
    }
}
