/////******************************************Disclaimer****************************************************//**
/////*The material offered by Holtek Semiconductor Inc. (including its subsidiaries, hereinafter 
/////*collectively referred to as "HOLTEK"), including but not limited to technical documentation and 
/////*code, is provided "as is", only for your reference, and may be superseded by updates. HOLTEK 
/////*reserves the right to revise the offered material at any time without prior notice. You shall use the 
/////*offered material at your own risk. HOLTEK disclaims any expressed, implied, or statutory warranties, 
/////*including but not limited to accuracy, suitability for commercialization, satisfactory quality, 
/////*specifications, characteristics, functions, fitness for a particular purpose, and non-infringement of 
/////*any third-party's rights. HOLTEK disclaims all liability arising from the offered material and its 
/////*application. In addition, HOLTEK does not recommend the use of HOLTEK's products where there is 
/////*a risk of personal hazard due to malfunction or other reasons. HOLTEK hereby declares that it does 
/////*not authorize the use of these products in life-saving, life-sustaining, or safety-critical components. 
/////*Any use of HOLTEK's products in life-saving, sustaining, or safety applications is entirely at your risk, 
/////*and you agree to defend, indemnify, and hold HOLTEK harmless from any damages, claims, suits, or 
/////*expenses resulting from such use.
/////************************************************************************************************************/

//////***********************************Intellectual Property*************************************************//**
/////*The offered material, including but not limited to the content, data, examples, materials, graphs, 
/////*and trademarks, is the intellectual property of HOLTEK (and its licensors, where applicable) and is 
/////*protected by copyright law and other intellectual property laws.
/////************************************************************************************************************/

#include <BS84C12CA.H>
#include "USER_PROGRAM_C.INC"
#include "Display.h"
#include "KEY.h"
#include "IIC.h"

// Capacitive Touch Key 
#define CAP_KEY1 0b0000000000000001  // Increment Key (PB0)
#define CAP_KEY2 0b0000000000000010  // Decrement Key (PB1)
#define CAP_KEY3 0b0000000000000100  // Power Key (PB2)

// LED Pin  
#define LED_PWR     _pa7 		//shared with segment A
#define LED_PWR_C   _pac7

#define LED_IND     _pb3    	// shared with segment E
#define LED_IND_C   _pbc3

#define LED_GND     _pa3
#define LED_GND_C   _pac3

//for arduino uart
#define CMD_POLL_DISPLAY  0xAA   // dummy byte to trigger a read

// Display buffer
unsigned char display_digits[4] = {0xFF, 0xFF, 0xFF, 0xFF}; 

// System state variables
volatile unsigned int current_value = 500;
volatile unsigned int last_key_buf = 0;
volatile bit system_power_on = 0;
volatile bit system_power_off = 0;
volatile bit show_on_message = 0;
volatile bit show_off_message = 0;
volatile bit show_blank_dashes = 0; 
volatile unsigned int on_message_counter = 0;
volatile unsigned int off_message_counter =0;
volatile unsigned int blank_counter =0;

// I2C error detection
static unsigned char i2c_fail_count = 0;
volatile bit i2c_error = 0;

// Value limits
#define MIN_VALUE 500
#define MAX_VALUE 3500
#define STEP_VALUE 500

#define ON_DISPLAY_TIME 2000  	
#define OFF_DISPLAY_TIME 2000
#define BLANK_DISPLAY_TIME 2000 

#define CMD_BLINK_LED  0x20   // Command to tell Arduino to blink its LED
#define CMD_LED_ON     0x02
#define CMD_LED_OFF    0x03

// I2C fail threshold -> 2 consecutive fails => E0 error
#define I2C_FAIL_THRESHOLD  2

//Delay function
void delay_custom(unsigned int count)
{
    unsigned int i, j;
    for (i = 0; i < count; i++)
        for (j = 0; j < 10; j++)
            asm("nop");
}

////==============================================
////**********************************************
////==============================================
//void __attribute((interrupt(0x04))) Interrupt_Extemal(void)
//{
//	//Insert your code here
//}

//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_C_INITIAL()
{
    unsigned int i;
    
    //Display init
    Display_Init();
    

    //LED pins
//    LED_GND_C = 0;  // Output
//    LED_GND = 0;     
    
    LED_IND_C = 0;   // Output 
    LED_IND = 0;     
   
//    LED_PWR_C = 0;   // Output
//    LED_PWR = 0;     
    
    // System starts in OFF state
    system_power_on = 0;
    show_on_message = 0;
    on_message_counter = 0;
    current_value = 500;
    brightness = 2;   		// stable brightness
    
    // Display is off initially
    display_enabled = 0;
    
    // Clear display buffer
    display_digits[0] = 0xFF;
    display_digits[1] = 0xFF;
    display_digits[2] = 0xFF;
    display_digits[3] = 0xFF;

    // I2C check -> 2 times -> 2 times fail -> E0
    i2c_fail_count = 0;
    i2c_error      = 0;

    for (i = 0; i < 2; i++)
    {
        if (!IIC_WriteData(CMD_BLINK_LED))
        {
            i2c_fail_count++;
        }
        else
        {
            i2c_fail_count = 0;
            break;    // success -> no failure
        }
    }

    if (i2c_fail_count >= I2C_FAIL_THRESHOLD)
    {
        i2c_error = 1;   // show E0 
    }

    // small delay
    for (i = 0; i < 100; i++)
    {
        GCC_CLRWDT();
        delay_custom(100);
    }
}

//Display ON 
void Display_ON_Message(void)
{
    display_digits[3] = 0xFF;  	// Blank
    display_digits[2] = 0;  	// Display 'O'
    display_digits[1] = 11;     // Display 'n'
    display_digits[0] = 0xFF;   // Blank  
}

//Display Blank dashes
void Display_Blank_Dashes(void)
{
    // Display dashes 
    display_digits[3] = 10;  // Dash pattern
    display_digits[2] = 10;  // Dash pattern
    display_digits[1] = 10;  // Dash pattern
    display_digits[0] = 10;  // Dash pattern
}

//Display OFF
void Display_OFF_Message(void)
{
    // display off
    display_digits[3] = 0xFF;  	// Blank
    display_digits[2] = 0;     	// Display 'O'
    display_digits[1] = 12;  	// Display 'F'
    display_digits[0] = 12;  	// Display 'F'
}

void Blink_LED_IND(void)
{
    LED_IND = 1;
    delay_custom(50);   // short visible blink
    LED_IND = 0;
}

	
//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_C()
{
	//I2C 
	static unsigned int i2c_test_counter = 0;
	static unsigned char i2c_ok = 0;

    static vu16 u16_Key_Buf;
    static bit key3_pressed_last = 0;
    static bit key1_pressed_last = 0;
    static bit key2_pressed_last = 0;
    static unsigned int debounce_counter = 0;

    //for arduino uart
    static unsigned int poll_counter = 0;

    GCC_CLRWDT();

    // Scan capacitive touch keys
    BS84C12CA_CTOUCH();
    GCC_CLRWDT();
    
    //brightness = 1; 

    // Get key status after scan complete
    if (SCAN_CYCLEF)
    {
        SCAN_CYCLEF = 0;
        GET_KEY_BITMAP();
        u16_Key_Buf = DATA_BUF[0];
    }

    //KEY3 power on/off 
	if (u16_Key_Buf & CAP_KEY3)
	{
    	if (!key3_pressed_last)
    	{
        	debounce_counter++;
        	if (debounce_counter > 5)
        	{
            	system_power_on = !system_power_on;

            	if (system_power_on)
            	{
                	// POWER ON
                	system_power_off = 0;
                	show_on_message = 1;
                	show_off_message = 0;
                	on_message_counter = 0;
                	display_enabled = 1;
                	Display_ON_Message();
            	}
           		else
            	{
                	// POWER OFF
                	system_power_off = 1;
                	show_off_message = 1;
                	show_on_message = 0;
                	off_message_counter = 0;
                	display_enabled = 1;      // keep display ON for OFF message
                	Display_OFF_Message();
            	}	

            	key3_pressed_last = 1;
            	debounce_counter = 0;
        	}
   	 	}
	}
    else
    {
        key3_pressed_last = 0;
        debounce_counter = 0;
    }
    
    //I2C failure detect very 500 cycles
    if (system_power_on && !show_on_message)
	{
	    i2c_test_counter++;
	    if (i2c_test_counter >= 500)   
	    {
	        i2c_test_counter = 0;

	        if (!IIC_WriteData(CMD_BLINK_LED))  // LED_IND blinks on ACK via IIC_respons()
	        {
	            i2c_fail_count++;
	            if (i2c_fail_count >= I2C_FAIL_THRESHOLD)
	                i2c_error = 1;
	        }
	        else
	        {
	            i2c_fail_count = 0;
	            i2c_error      = 0;   // clear E0 when reconnected
	        }
	    }
	}


    //"ON" Handler
    if (show_on_message && system_power_on)
    {
        on_message_counter++;
        
        if (on_message_counter >= ON_DISPLAY_TIME)
		{
    		show_on_message = 0;
    		on_message_counter = 0;
	
    		show_blank_dashes = 1;
    		blank_counter = 0;
    		Display_Blank_Dashes();
		}
        else
        {
            // Continue showing "ON"
            Display_ON_Message();
        }
    }
    if (show_blank_dashes)
	{
    	blank_counter++;
    	if (blank_counter >= BLANK_DISPLAY_TIME)
    	{
       		show_blank_dashes = 0;
        	blank_counter = 0;
        	Display_Numbers(current_value);  // 500 as initial value
    	}
	}
    
    //"OFF" Handler
    if (show_off_message && system_power_off)
    {
        off_message_counter++;
        
        if (off_message_counter >= OFF_DISPLAY_TIME)
        {
            show_off_message = 0;
            off_message_counter = 0;
            //Display_Blank_Dashes();
            display_enabled = 0;
        }
        else
        {
            // Continue showing "Off"
            Display_OFF_Message();
        }
    }

    //KEY1 -> Increment handler
    
    if (system_power_on && !show_on_message)
    {
    	//Display_Numbers(current_value);
        if ((u16_Key_Buf & CAP_KEY1) && !key1_pressed_last)
        {
        	//Display_Numbers(current_value);
        	
            // Increment value
            if (current_value < MAX_VALUE)
            {
                current_value += STEP_VALUE;
                Display_Numbers(current_value);
                //LED_IND = 1;  // Turn on induction LED
            }
            key1_pressed_last = 1;

            if (current_value >= MAX_VALUE)
            {
                // Send buzzer command to Arduino
                if (!IIC_WriteData(0x10))   // CMD_BUZZER_ON on Arduino
                {
                    i2c_fail_count++;
                    if (i2c_fail_count >= I2C_FAIL_THRESHOLD)
                        i2c_error = 1;
                }
                else
                {
                    i2c_fail_count = 0;
                    i2c_error      = 0;
                }
            }
            
        }
        else if (!(u16_Key_Buf & CAP_KEY1))
        {
            key1_pressed_last = 0;
            //if (!(u16_Key_Buf & CAP_KEY2))
                //LED_IND = 0;  // Turn off LED only if no keys pressed
        }

        //KEY2 -> Decrement handler
        if ((u16_Key_Buf & CAP_KEY2) && !key2_pressed_last)
        {
            // Decrement value
            if (current_value > MIN_VALUE)
            {
                current_value -= STEP_VALUE;
                Display_Numbers(current_value);
                //LED_IND = 1;  // Turn on induction LED
            }
            key2_pressed_last = 1;
        }
        else if (!(u16_Key_Buf & CAP_KEY2))
        {
            key2_pressed_last = 0;
            //if (!(u16_Key_Buf & CAP_KEY1))
                //LED_IND = 0;  // Turn off LED only if no keys pressed
        }
    }

    //for arduino uart 
    if (system_power_on)
    {
        poll_counter++;
        if (poll_counter >= 3000)
        {
            poll_counter = 0;

            unsigned int received_value = IIC_ReadData_2byte();

            if (received_value >= 500 && received_value <= 3500)
            {
                current_value = received_value;
                Display_Numbers(current_value);
            }
        }
    }

    //Refresh display for multiplexing
    if (i2c_error)
    {
        // I2C disconnected -> show E0
        Display_E0_Error();
        display_enabled = 1;
        Display_Update();
    	Display_Update();
    	Display_Update();
    	Display_Update(); 
    }
    else if (display_enabled)
    {
    	//GCC_CLRWDT();
        Display_Update();
    	Display_Update();
    	Display_Update();
    	Display_Update();
    	GCC_CLRWDT();
    }
    else
    {
        // Turn off all display segments when powered off
        ALL_SEGMENT_OFF();
        ALL_COM_OFF();
        /*show_off_message = 1;
        display_enabled = 1;
        Display_OFF_Message();
        display_enabled=0;*/
    }

    // Store last key buffer 
    last_key_buf = u16_Key_Buf;
	
}

//function to execute before going into standby
void USER_PROGRAM_C_HALT_PREPARE()
{
    // Turn off all LEDs and display before standby
    display_enabled = 0;
    //LED_PWR = 0;
    //LED_IND = 0;
    ALL_SEGMENT_OFF();
    ALL_COM_OFF();
}

//Functions that are executed after standby mode is interrupted and IO is woken up
void USER_PROGRAM_C_HALT_WAKEUP()
{
    // Restore previous power state
    if (system_power_on)
    {
        display_enabled = 1;
        //brightness = 1;
        //LED_PWR = 1;
    }
}

//function to execute when standby mode is switched back to work mode
void USER_PROGRAM_C_RETURN_MAIN()
{
    // Re-initialize display if needed
    if (system_power_on)
    {
        Display_Init();
    }
}