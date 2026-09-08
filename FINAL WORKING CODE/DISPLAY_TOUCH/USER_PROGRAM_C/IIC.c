#include "IIC.h"
#include "Display.h"

extern void Blink_LED_IND(void);
/*************************************************************************************/
//**	Copyright	:	2015 BY HOLTEK SEMICONDUCTOR INC                            **
//** 	File Name   :	IIC.c                                                       **
//**	Description	: 	IO ?? IIC ??											**
//**	TargerBoard	: 	None														**
//**	MCU      	: 	HT67F5650													**
//**	Author   	: 	LJQ															**
//**	Date     	: 	2015/11/20													**
//**	Version  	: 	V00															**
//**	History  	:																**
/*************************************************************************************/

/*************************************************************************************/
//**	Note:
//**	1. ??eeprom?,??????buff???????????,?????????
//** 	  ???????,????DataSheet???,??????ms?
//**	2. ??HB45B1224?,?????start???stop
//**	
//**	
/*************************************************************************************/
volatile unsigned char gu8v_adc_data_1[3];

/***********************************************************
**   Function : delay5us
**   INPUT    : none
**   OUTPUT   : none
**   NOTE     : 
				CLK cycle = 10us ; Sps = 100KHz  bit/s 
***********************************************************/
void delay5us()    	   
{
//---------------------------------
// MVU Sys : 9.8 Mhz   
// nop     : 0.4us	
//---------------------------------	
	_nop(); _nop(); _nop(); _nop(); _nop();
    _nop(); _nop(); _nop(); _nop(); _nop();

}

/***********************************************************
**   Function : IIC_start
**   INPUT    : none
**   OUTPUT   : none
**   NOTE     : 
**
**   SCL:  ___|^^^^^^^^^^^^^^^^^^^^^^^|___
**   SDA:  ___|^^^^^^^^^^?_______________
**            |? >4.7us?|? >4.7us?|
**   ???? : SCL?????,SDA??????????				
***********************************************************/
void IIC_start()  					
{
	IIC_SDAC = OUTPUT;						
	IIC_SCLC = OUTPUT;		
	IIC_SDA  = 1;		
	delay5us();	
	IIC_SCL  = 1;	
	delay5us();							
	IIC_SDA  = 0;								
	delay5us();		
	//
	IIC_SCL = 0;    // Pull clock low ready for first bit
    delay5us();									
}

/***********************************************************
**   Function : IIC_stop
**   INPUT    : none
**   OUTPUT   : none
**   NOTE     : 
**
**   SCL:  ___|^^^^^^^^^^^^^^^^^^^^^^^|___
**   SDAy:  _______________?^^^^^^^^^^|___
**            |? >4.7us?|? >4.7us?|
**   ???? : SCL?????,SDA??????????				
***********************************************************/
void IIC_stop()  					
{
	IIC_SDAC = OUTPUT;						
	IIC_SCLC = OUTPUT;	
							
	IIC_SDA  = 0;
	delay5us();
	IIC_SCL  = 1;
	delay5us();
	IIC_SDA  = 1;
	delay5us();	
}

/***********************************************************
**   Function : IIC_respons
**   INPUT    : 0 -> ??,1 -> ???
**   OUTPUT   : none
**   NOTE     : 
**
**   SCL:  ^^^^^^^^^^^^^^^^|___
**   SDA:  ^^^^|____|^^^^^^^^^^  : ACK
**   SDA:  ^^^^^^^^^^^^^^^^^^^^  : NO_ACK    
**   ???? : SCL?????,SDA??????????				
***********************************************************/
unsigned char IIC_respons()  					
{
	volatile unsigned char i = 100;		// Timeout counter
	//
	unsigned char ack_received = 0;
	
	IIC_SDA_PU = EN_high;     // enable pull-up resistor on SDA
	IIC_SDAC   = INPUT;       // configure SDA as input (release line)
	
	_nop();	_nop();	_nop();	_nop();
							
	IIC_SCL = 1;			//9th clock pulse			
	delay5us();	
	
	while(i--)
	{	
		delay5us(); 				
		if(IIC_SDA == 0)	//ack received				
		{	
//			IIC_SCL  = 0;		//lower clock					
//			IIC_SDA_PU = DIS_high;
//			
//			Blink_LED_IND(); //blink LED_IND if ACK recived
//			
//			return 1;	      //ack received successfully
			//
			ack_received = 1;
            break;				
		}
	}
	IIC_SCL  = 0;
	IIC_SDA_PU = DIS_high;
	//	
	delay5us();	
	//
	if (ack_received)
    {
        Blink_LED_IND();                // Visual confirmation: ACK received
        return 1;
    }
    		
	return 0;							
}
/***********************************************************
**   Function : MaterAck
**   INPUT    : 
**   OUTPUT   : 
**   NOTE     : 
**
**   SCL:  ^^^^^^^^^^^^^^^^|___
**   SDA:  ^^^^|____|^^^^^^^^^^  : ACK
**   SDA:  ^^^^^^^^^^^^^^^^^^^^  : NO_ACK    
**   ???? : SCL?????,SDA??????????				
***********************************************************/
void MaterAck(unsigned char lu8v_AckFlag)
{
	IIC_SDAC = OUTPUT;
	IIC_SCLC  = OUTPUT;
	
	delay5us();
	IIC_SDA = lu8v_AckFlag;
	delay5us();
	IIC_SCL = 1;
	delay5us();	
	IIC_SCL = 0;
	delay5us();
}

/***********************************************************
**   Function : IIC_write_byte
**   INPUT    : lu8v_IIC_byte
**   OUTPUT   : none
**   NOTE     : 
**             SCL ?????,??? SDA???			
***********************************************************/
void IIC_write_byte(unsigned char lu8v_IIC_byte)		
{
	volatile unsigned char i;
	
	IIC_SDAC = OUTPUT;							
	IIC_SCLC  = OUTPUT;
	
	IIC_SCL  = 0;		// Ensure clock is low before starting		
	delay5us();	
	
	for(i=0;i<8;i++)	//loop through all 8 bits
	{
		if(lu8v_IIC_byte & 0x80)     //check MSB
		{                            //if MSB = 1 the result is nonzero
			IIC_SDA = 1;             //if MSB = 0 the result is zero
		}
		else
		{
		 	IIC_SDA = 0;	
		}	
					
		lu8v_IIC_byte <<= 1;   //after shifting next bit becomes MSB
/*		
	//	delay5us();
		IIC_SCL  = 1;					
		delay5us();delay5us();
		IIC_SCL  = 0;				
	//	delay5us();
	*/
	
		delay5us();     
		IIC_SCL  = 1;			 //raise clock, slave samples SDA		
		delay5us();delay5us();   //keep clock high enough
		IIC_SCL  = 0;            //lower clock, prepare next bit			
		delay5us();
	}
}

/***********************************************************
**   Function : IIC_read_byte
**   INPUT    : none
**   OUTPUT   : lu8v_IIC_byte
**   NOTE     : 
**             SCL ?????,??? SDA???			
***********************************************************/
unsigned char IIC_read_byte()     				
{
	
	volatile unsigned char i;
	unsigned char lu8v_IIC_byte = 0;
	
	IIC_SDA_PU = EN_high; // Enable pull-up
	IIC_SDAC   = INPUT;   // Release SDA for slave to drive
	
	IIC_SCL  = 0;      //start with clock low		
	delay5us();	
				
	for(i = 0; i < 8; i ++)			
	{	
				
//		lu8v_IIC_byte = (lu8v_IIC_byte << 1) | IIC_SDA;	 //left shift and add the new bit	
//		
//		IIC_SCL  = 1;	//slave puts the bit on SDA, master samples it		
//		delay5us(); delay5us(); 
//		IIC_SCL  = 0 ;		//prepare for the next bit			
//		//delay5us(); 
		//
		IIC_SCL = 1;                    // Raise clock - slave puts bit on SDA
        delay5us();
        delay5us();

        lu8v_IIC_byte = (lu8v_IIC_byte << 1) | IIC_SDA;  // Sample SDA

        IIC_SCL = 0;                    // Lower clock - prepare next bit
        delay5us();	
				
	}
	
	IIC_SDA_PU = DIS_high;	
									
	return lu8v_IIC_byte;
}

/***********************************************************
**   Function : IIC_WriteData
**   INPUT    : lu8v_IIC_add,lu8v_IIC_data
**   OUTPUT   : none
**   NOTE     : 
**            	
***********************************************************/

// Change return type from void to unsigned char
unsigned char IIC_WriteData(unsigned char lu8v_IIC_data)
{
    volatile unsigned char lu8v_IIC_ACK = 0;

    IIC_start();
    IIC_write_byte(IIC_Device_ADD << 1);
    lu8v_IIC_ACK = IIC_respons();
    if(lu8v_IIC_ACK)
    {
        IIC_write_byte(lu8v_IIC_data);
        IIC_respons();
        IIC_stop();
        return 1;   // SUCCESS
    }
    IIC_stop();
    return 0;       // FAIL
}

/***********************************************************
**   Function : IIC_ReadData
**   INPUT    : lu8v_IIC_add
**   OUTPUT   : lu8v_IIC_ReadData
**   NOTE     : 
**            	
***********************************************************/
unsigned char IIC_ReadData(unsigned char lu8v_IIC_add)
{
    volatile unsigned char lu8v_IIC_ACK = 0;    //store ACK result
    volatile unsigned char lu8v_IIC_ReadData;   //store received byte
    
//	IIC_start();
//	IIC_write_byte(IIC_Device_ADD);
//	lu8v_IIC_ACK = IIC_respons();
//	if(lu8v_IIC_ACK)
//	{
//		IIC_write_byte(lu8v_IIC_add);		
//	}
//	lu8v_IIC_ACK = IIC_respons();
	
//	IIC_stop();
	
	IIC_start();                         //start condition
//	IIC_write_byte(IIC_Device_ADD|0x1);  //send slave address + read bit
	IIC_write_byte((IIC_Device_ADD << 1) | 0x1);
	lu8v_IIC_ACK = IIC_respons();        //check if slave responded with ACK
	if(lu8v_IIC_ACK)
	{
		lu8v_IIC_ReadData = IIC_read_byte();  //reads 8 bits from SDA	
	}
	MaterAck(M_NOACK);	 	//stop sending
	
	IIC_stop();          //stop condition

	return lu8v_IIC_ReadData;
}

//for arduino uart
unsigned int IIC_ReadData_2byte(void)
{
    volatile unsigned char lu8v_IIC_ACK = 0;
    unsigned char high_byte = 0;
    unsigned char low_byte  = 0;

    IIC_start();
    IIC_write_byte((IIC_Device_ADD << 1) | 0x1);  // address + read bit
    lu8v_IIC_ACK = IIC_respons();

    if (lu8v_IIC_ACK)
    {
        high_byte = IIC_read_byte();   // read first byte
        MaterAck(M_ACK);               // ACK → tell slave to send another
        low_byte  = IIC_read_byte();   // read second byte
        MaterAck(M_NOACK);             // NACK → tell slave we're done
    }

    IIC_stop();

    return (unsigned int)((high_byte << 8) | low_byte);
}