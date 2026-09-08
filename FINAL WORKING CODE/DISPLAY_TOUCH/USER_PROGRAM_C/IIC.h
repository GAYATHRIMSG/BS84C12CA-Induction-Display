//*************************************************************************************/
//**    Copyright    :    2015 BY HOLTEK SEMICONDUCTOR INC                            **
//**     File Name   :    IIC.h                                                       **
//**    Description    :     IO ?? IIC ??                                                **
//**    TargerBoard    :     None                                                        **
//**    MCU          :     HT67F5650                                                    **
//**    Author       :     LJQ                                                            **
//**    Date         :     2015/11/20                                                    **
//**    Version      :     V00                                                            **
//**    History      :                                                                **
/*************************************************************************************/
#ifndef __IIC_h_
#define __IIC_h_
#include "BS84C12CA.h"
/*========================I2C definition===============================*/
#define IIC_Device_ADD   85
        
#define IIC_SCL          _pa2                //I2C CLOCK(I/O PIN)
#define IIC_SCLC         _pac2                //I2C CLOCK(I/O PIN DIRECTION SEETING)
#define IIC_SDA             _pa0                //I2C DATA(I/O PIN)
#define IIC_SDAC         _pac0                //I2C DATA(I/O PIN DIRECTION SETTING)
// IIC_SDA_PU may already be defined by GLOBE_VARIES.INC undefine first to avoid warning
#ifdef IIC_SDA_PU
  #undef IIC_SDA_PU
#endif
#define IIC_SDA_PU       _papu0             //I2C DATA(I/O PIN INPUT PULL)
/*========================params==================================*/
#define INPUT      1
#define OUTPUT     0 
#define EN_high    1
#define DIS_high   0  
#define M_ACK      0
#define M_NOACK    1
/*========================functions====================================*/
extern volatile unsigned char gu8v_adc_data_1[3];
void IIC_start();                                //IIC????
void IIC_stop();                                //IIC????
unsigned char IIC_respons();                                //IIC????
void MaterAck(unsigned char lu8v_AckFlag);
void IIC_write_byte(unsigned char lu8v_IIC_byte);            //IIC???8???
unsigned char IIC_read_byte();                                //IIC???8???
unsigned char IIC_ReadData(unsigned char add_reg);
unsigned char IIC_WriteData(unsigned char data_reg);
void Write_HT24_nByte(unsigned char lu8v_HT24_add,unsigned char lu8v_IIC_length,unsigned char* Buffer);
void Read_HT24_nByte(unsigned char lu8v_HT24_add,unsigned char lu8v_IIC_length,unsigned char* Buffer);
unsigned char IIC_ReadData_3(unsigned char lu8v_IIC_reg_add);

//for arduino uart
unsigned int IIC_ReadData_2byte(void);
/*----------------------------------------------------------------------*/
    #define PWRC   0x00
    #define PGAC0  0x01
    #define PGAC1  0x02
    #define PGACS  0x03
    #define ADRL   0x04
    #define ADRM   0x05
    #define ADRH   0x06
    #define ADCR0  0x07
    #define ADCR1  0x08
    #define ADCS   0x09
    #define ADCTE  0x0a
    #define DAH    0x0b
    #define DAL    0x0c
    #define DACC   0x0d
    #define SIMC0  0x0e
    #define SIMC2  0x0f
    #define SIMTOC 0x10
    #define HIRCC  0x11
    #define HXTC   0x12
    #define OSCRH  0x1a
    #define OSCRL  0x1b
    #define BGVREF 0x1e
/*==========================================================================*/
#endif