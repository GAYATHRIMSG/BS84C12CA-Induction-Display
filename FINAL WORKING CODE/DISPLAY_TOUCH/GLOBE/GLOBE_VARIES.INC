;;;;;/******************************************Disclaimer****************************************************//**
;;;;;*The material offered by Holtek Semiconductor Inc. (including its subsidiaries, hereinafter 
;;;;;*collectively referred to as “HOLTEK”), including but not limited to technical documentation and 
;;;;;*code, is provided “as is”, only for your reference, and may be superseded by updates. HOLTEK 
;;;;;*reserves the right to revise the offered material at any time without prior notice. You shall use the 
;;;;;*offered material at your own risk. HOLTEK disclaims any expressed, implied, or statutory warranties, 
;;;;;*including but not limited to accuracy, suitability for commercialization, satisfactory quality, 
;;;;;*specifications, characteristics, functions, fitness for a particular purpose, and non-infringement of 
;;;;;*any third-party’s rights. HOLTEK disclaims all liability arising from the offered material and its 
;;;;;*application. In addition, HOLTEK does not recommend the use of HOLTEK’s products where there is 
;;;;;*a risk of personal hazard due to malfunction or other reasons. HOLTEK hereby declares that it does 
;;;;;*not authorize the use of these products in life-saving, life-sustaining, or safety-critical components. 
;;;;;*Any use of HOLTEK’s products in life-saving, sustaining, or safety applications is entirely at your risk, 
;;;;;*and you agree to defend, indemnify, and hold HOLTEK harmless from any damages, claims, suits, or 
;;;;;*expenses resulting from such use.
;;;;;************************************************************************************************************/

;;;;;/***********************************Intellectual Property*************************************************//**
;;;;;*The offered material, including but not limited to the content, data, examples, materials, graphs, 
;;;;;*and trademarks, is the intellectual property of HOLTEK (and its licensors, where applicable) and is 
;;;;;*protected by copyright law and other intellectual property laws.
;;;;;************************************************************************************************************/ 


;;;;;//*************************************************************************
;;;;;//* @file    CALCULATE_POSITION.INC                                       *
;;;;;//* @version V1.00                                                        *
;;;;;//* @date    11/13/2020                                                   *
;;;;;//* @brief   The header file of the CALCULATE_POSITION library.           *
;;;;;//*************************************************************************

;;;;;// ---------------------------------------------------------------------- //
;;;;;// MCU Base Config                                                        //
;;;;;// ---------------------------------------------------------------------- //

;;;;;// *MCU**MCU**MCU**MCU**MCU**MCU**MCU**MCU**MCU**MCU**MCU**MCU**MCU**MCU***
;////start mcu option
        #define _CCV3_

        ;// <h> System_Config
              ;// <o> Vdd
              ;// <i> Vdd (for selections of Internal RC)
              ;// <1 =>    5V
              ;// <2 =>    3.0V
              #define  vdd	0

              ;// <o> SystemClock
              ;// <i> auto calibration period select 80ms ~ 1280ms
              ;// <0 =>     8MHZ    
              ;// <1 =>    12MHZ
              ;// <2 =>    16MHZ
              #define  SystemClock  0
              
        ;// </h>
        
       
	;//<o>LOOP_TIMES
	     #define LOOP_TIMES		12
		 
		;//<s>LOOP_VAR_NAME
	    #define LOOP_VAR_NAME     "cn"
        #define cn 0	
        #include "..\DEVICE\BS84C12CA.DEV"
;////end mcu option
;;;;;//
;;;;;// ---------------------------------------------------------------------- //
;;;;;// C & ASM Includes,define                                                //
;;;;;// *g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**g**
#define ___TK_IIC_HXT_SLAVE
      #define TouchLibraryVersion     512H

;;;;;//
;;;;;// ---------------------------------------------------------------------- //



;;;;;// ---------------------------------------------------------------------- //
;;;;;// assembly exported function,register                                    //
;;;;;// *asm**asm**asm**asm**asm**asm**asm**asm**asm**asm**asm**asm**asm**asm* //
;//<IIC_SCL>SCL_EN
;//<ALIAS>IIC_SCL
#define ___SCL        PA2
#define ___SCL_C      PAC2
#define ___SCL_PU     PAPU2
#define IIC_SCL_ON    IIC_SCL_ON_PA2

;//<IIC_SDA>SDA_EN
;//<ALIAS>IIC_SDA
#define ___SDA        PA0
#define ___SDA_C      PAC0
#define ___SDA_PU     PAPU0
#define IIC_SDA_ON    IIC_SDA_ON_PA0


;//<TOUCH>__KEY1_EN
;//<ALIAS>KEY1
#define ___KEY1 	PB0
#define ___KEY1_C 	PBC0
#define ___KEY1_PU 	PBPU0

;//<TOUCH>__KEY2_EN
;//<ALIAS>KEY2
#define ___KEY2 	PB1
#define ___KEY2_C 	PBC1
#define ___KEY2_PU 	PBPU1  

;//<TOUCH>__KEY3_EN
;//<ALIAS>KEY3
#define ___KEY3 	PB2
#define ___KEY3_C 	PBC2
#define ___KEY3_PU 	PBPU2  

;//<TOUCH>__KEY4_EN
;//<ALIAS>KEY4
#define ___KEY4 	0
#define ___KEY4_C 	0
#define ___KEY4_PU 	0

;//<TOUCH>__KEY5_EN
;//<ALIAS>KEY5
#define ___KEY5 	0
#define ___KEY5_C 	0
#define ___KEY5_PU 	0  

;//<TOUCH>__KEY6_EN
;//<ALIAS>KEY6
#define ___KEY6 	0
#define ___KEY6_C 	0
#define ___KEY6_PU 	0

;//<TOUCH>__KEY7_EN
;//<ALIAS>KEY7
#define ___KEY7 	0
#define ___KEY7_C 	0
#define ___KEY7_PU 	0  

;//<TOUCH>__KEY8_EN
;//<ALIAS>KEY8
#define ___KEY8 	0
#define ___KEY8_C 	0
#define ___KEY8_PU 	0  

;//<TOUCH>__KEY9_EN
;//<ALIAS>KEY9
#define ___KEY9 	0
#define ___KEY9_C 	0
#define ___KEY9_PU 	0 


;//<TOUCH>__KEY10_EN
;//<ALIAS>KEY10
#define ___KEY10 	0
#define ___KEY10_C 	0
#define ___KEY10_PU 0

;//<TOUCH>__KEY11_EN
;//<ALIAS>KEY11
#define ___KEY11 	0
#define ___KEY11_C 	0
#define ___KEY11_PU 0

;//<TOUCH>__KEY12_EN
;//<ALIAS>KEY12
#define ___KEY12 	0
#define ___KEY12_C 	0
#define ___KEY12_PU 0



;////start option_ASM

      ;// <o> IIC_ADDRESS
      ;// <i> IIC ADDRESS MATCH
      ;//<i>  IIC_ADDRESS_default   0x55
      ;// <0-127>
      #define  IIC_ADDRESS  85         

      ;//<q>SDA_EN
      ;// <i> 0=SDA_EN disable 1=SDA_EN enalbe 
        #define SDA_EN                1


    ;//<q>SCL_EN
      ;// <i> 0=SCL_EN disable 1=SCL_EN enalbe 
        #define SCL_EN                1   

      #define IIC_SDA_PU    SET ___SDA_C
      #define IIC_SCL_PU    SET ___SCL_PU
      #define IIC_SDA_PIN   IIC_SDA_ON
      #define IIC_SCL_PIN   IIC_SCL_ON
            

;// <h> TKL_Config
    
      ;// <o> DebounceTimes
      ;// <i> Debounce in output key status 
      ;// <0-15>
      #define DebounceTimes           0

      ;// <o> AutoCalibrationPeriod
      ;// <i> auto calibration period select 80ms to 1280ms.The faster speed the better the anti-interference and the worse the sensitivity.The slower speed the worse the anti-interference and the better the sensitivity
      ;// <0 =>     80mS    
      ;// <1 =>    160mS
      ;// <2 =>    240mS
      ;// <3 =>    320mS
      ;// <4 =>    400mS
      ;// <5 =>    480mS
      ;// <6 =>    560mS
      ;// <7 =>    640mS
      ;// <8 =>    720mS
      ;// <9 =>    800mS
      ;// <10=>    880mS
      ;// <11=>    960mS
      ;// <12=>   1040mS
      ;// <13=>   1120mS
      ;// <14=>   1200mS
      ;// <15=>   1280mS
      #define  AutoCalibrationPeriod  7

      ;// <o> HighSensitive 
      ;// <i> Sensitive double up,0-Normal  1-High Sensitive
      ;// <0=>     Normal
      ;// <1=>     High
      #define HighSensitive           1

      ;// <o> MaximumKeyHoldTime 
      ;// <i> key holding time ,if time out will reset key status to non-press,Range is 4S~60S or Disable the function
      ;// <0 =>  Disable    
      ;// <1 =>       4S
      ;// <2 =>       8S
      ;// <3 =>      12S
      ;// <4 =>      16S
      ;// <5 =>      20S
      ;// <6 =>      24S
      ;// <7 =>      28S
      ;// <8 =>      32S
      ;// <9 =>      36S
      ;// <10=>      40S
      ;// <11=>      44S
      ;// <12=>      48S
      ;// <13=>      52S
      ;// <14=>      56S
      ;// <15=>      60S
      #define  MaximumKeyHoldTime     2

      ;// <q> AutoFrequencyHopping
      ;// <i> enalbe hardware hopping function     
      #define AutoFrequencyHopping    1
      
      
      ;// <q> OneKeyActive
      ;// <i> Only one or all key active at the same time
      ;// <0 =>  all key active    
      ;// <1 =>  one key active
      #define OneKeyActive            0

      ;// <q> PowerSave
      ;// <i> Low power mode 
      #define PowerSave               0
  
      ;// <q> TKL_MovingCalibration
      ;// <i> Touch key Moving Calibration keys easier to operate
      #define MovingCalibration       1
      
      ;// <o>MainFreqSelect
      ;// <i> Touch frequency selection
      ;// <0 =>  3M&7M
      ;// <1 =>  3M&11M
      ;// <2 =>  1M&3M
      #define MainFreqSelect          1


   ;// </h>
  
  ;// <h> TKL_ENABLE_KEY
      
    ;// <i> If the setting over the maximum key, it will be set disable
    
    ;// <e> __KEY1_EN
      ;// <i> 0=__KEY1 disable 1=__KEY1 enalbe 
        #define __KEY1_EN                 1
      ;// <o> Key1Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key1Threshold            16
      ;// <o> __KEY1_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY1_WAKE               0
    ;// </e>
    
    ;// <e> __KEY2_EN
      ;// <i> 0=__KEY2 disable 1=__KEY2 enalbe 
        #define __KEY2_EN                 1
      ;// <o> Key2Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key2Threshold            16
      ;// <o> __KEY2_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY2_WAKE               0
    ;// </e>
    
    ;// <e> __KEY3_EN
      ;// <i> 0=__KEY3 disable 1=__KEY3 enalbe 
        #define __KEY3_EN                 1
      ;// <o> Key3Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key3Threshold            16
      ;// <o> __KEY3_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY3_WAKE               0
    ;// </e>
    
    ;// <e> __KEY4_EN
      ;// <i> 0=__KEY4 disable 1=__KEY4 enalbe 
        #define __KEY4_EN                 0
      ;// <o> Key4Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key4Threshold            16
      ;// <o> __KEY4_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY4_WAKE               0
    ;// </e>
    
    ;// <e> __KEY5_EN
      ;// <i> 0=__KEY5 disable 1=__KEY5 enalbe 
        #define __KEY5_EN                 0
      ;// <o> Key5Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key5Threshold            16
      ;// <o> __KEY5_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY5_WAKE               0
    ;// </e>
    
    ;// <e> __KEY6_EN
      ;// <i> 0=__KEY6 disable 1=__KEY6 enalbe 
        #define __KEY6_EN                 0
      ;// <o> Key6Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key6Threshold            16
      ;// <o> __KEY6_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY6_WAKE               0
    ;// </e>
    
    ;// <e> __KEY7_EN
      ;// <i> 0=__KEY7 disable 1=__KEY7 enalbe 
        #define __KEY7_EN                 0
      ;// <o> Key7Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key7Threshold            16
      ;// <o> __KEY7_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY7_WAKE               0
    ;// </e>
    
    ;// <e> __KEY8_EN
      ;// <i> 0=__KEY8 disable 1=__KEY8 enalbe 
        #define __KEY8_EN                 0
      ;// <o> Key8Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key8Threshold            16
      ;// <o> __KEY8_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY8_WAKE               0
    ;// </e>
    
    ;// <e> __KEY9_EN
      ;// <i> 0=__KEY9 disable 1=__KEY9 enalbe 
        #define __KEY9_EN                 0
      ;// <o> Key9Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key9Threshold            16
      ;// <o> __KEY9_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY9_WAKE               0
    ;// </e>
    
    ;// <e> __KEY10_EN
      ;// <i> 0=__KEY10 disable 1=__KEY10 enalbe 
        #define __KEY10_EN                 0
      ;// <o> Key10Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key10Threshold            16
      ;// <o> __KEY10_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY10_WAKE               0
    ;// </e>
    
    ;// <e> __KEY11_EN
      ;// <i> 0=__KEY11 disable 1=__KEY11 enalbe 
        #define __KEY11_EN                 0
      ;// <o> Key11Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key11Threshold            16
      ;// <o> __KEY11_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY11_WAKE               0
    ;// </e>
    
    ;// <e> __KEY12_EN
      ;// <i> 0=__KEY12 disable 1=__KEY12 enalbe 
        #define __KEY12_EN                 0
      ;// <o> Key12Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key12Threshold            16
      ;// <o> __KEY12_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY12_WAKE               0
    ;// </e>
  ;// </h> 

    #define IO_TOUCH_ATTR_IP0   (__KEY1_EN<<0|__KEY2_EN<<1|__KEY3_EN<<2|__KEY4_EN<<3)
    #define IO_TOUCH_ATTR_IP1   (__KEY5_EN<<4|__KEY6_EN<<5|__KEY7_EN<<6|__KEY8_EN<<7)
    #define IO_TOUCH_ATTR_IP2   (__KEY9_EN<<8|__KEY10_EN<<9|__KEY11_EN<<10|__KEY12_EN<<11)
    #define IO_TOUCH_ATTR       (IO_TOUCH_ATTR_IP0|IO_TOUCH_ATTR_IP1|IO_TOUCH_ATTR_IP2)
      
    #define WAKEUP_KEY_IP0      ((__KEY1_WAKE^1)<<0|(__KEY2_WAKE^1)<<1|(__KEY3_WAKE^1)<<2|(__KEY4_WAKE^1)<<3)
    #define WAKEUP_KEY_IP1      ((__KEY5_WAKE^1)<<4|(__KEY6_WAKE^1)<<5|(__KEY7_WAKE^1)<<6|(__KEY8_WAKE^1)<<7)
    #define WAKEUP_KEY_IP2      ((__KEY9_WAKE^1)<<8|(__KEY10_WAKE^1)<<9|(__KEY11_WAKE^1)<<10|(__KEY12_WAKE^1)<<11)
    #define WAKEUP_KEY          (WAKEUP_KEY_IP0|WAKEUP_KEY_IP1|WAKEUP_KEY_IP2)
    


;////end option_ASM
;////start communication option configuration_ASM
  ;//<o>  DebounceTimes    
    ;//<i>Debounce in output key status
    ;//<0-15>
    ;//<c>
		;//<o>  ADDR
		;//<o1> MASK    
		;//<s>  OUTPUT
		;//<s1> OUTPUT_R
	       #define DebounceTimes_ADDR              0D3H
         #define DebounceTimes_MASK              0FH
         #define DebounceTimes_OUTPUT            "OUTPUT"
         #define DebounceTimes_OUTPUT_R          "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
	;//</c>
	
	;//<o>  AutoCalibrationPeriod   
    ;//<i>auto calibration period select 80ms to 1280ms. 
    ;//<0 =>     80mS    
    ;//<1 =>    160mS
    ;//<2 =>    240mS
    ;//<3 =>    320mS
    ;//<4 =>    400mS
    ;//<5 =>    480mS
    ;//<6 =>    560mS
    ;//<7 =>    640mS
    ;//<8 =>    720mS
    ;//<9 =>    800mS
    ;//<10=>    880mS
    ;//<11=>    960mS
    ;//<12=>   1040mS
    ;//<13=>   1120mS
    ;//<14=>   1200mS
    ;//<15=>   1280mS
	;//<c>
	  ;//<o>  ADDR
      ;//<o1> MASK
      ;//<s>  OUTPUT
      ;//<s1> OUTPUT_R
      #define AutoCalibrationPeriod_ADDR        0D3H
      #define AutoCalibrationPeriod_MASK        0F0H
      #define AutoCalibrationPeriod_OUTPUT      "OUTPUT"
      #define AutoCalibrationPeriod_OUTPUT_R    "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
	;//</c>

  
    ;//<o>  HighSensitive    
    ;//<i> Sensitive double up,0-Normal  1-High Sensitive
    ;//<0=>     Normal
    ;//<1=>     High
	;//<c>
	  ;//<o>   ADDR
      ;//<o1>  MASK
      ;//<s>   OUTPUT
      ;//<s1>  OUTPUT_R
      #define HighSensitive_ADDR                0D4H
      #define HighSensitive_MASK                01H
      #define HighSensitive_OUTPUT              "OUTPUT"
      #define HighSensitive_OUTPUT_R            "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
	;//</c>
  
    
  
  
    ;//<o>  MaximumKeyHoldTime    
    ;//<i> key holding time ,if time out will reset key status to non-press,Range is 4S~60S or Disable the function
    ;//<0 =>  Disable    
    ;//<1 =>       4S
    ;//<2 =>       8S
    ;//<3 =>      12S
    ;//<4 =>      16S
    ;//<5 =>      20S
    ;//<6 =>      24S
    ;//<7 =>      28S
    ;//<8 =>      32S
    ;//<9 =>      36S
    ;//<10=>      40S
    ;//<11=>      44S
    ;//<12=>      48S
    ;//<13=>      52S
    ;//<14=>      56S
    ;//<15=>      60S
	;//<c>
	  ;//<o>  ADDR
	  ;//<o1> MASK
	  ;//<s>  OUTPUT
	  ;//<s1> OUTPUT_R
    #define MaximumKeyHoldTime_ADDR           0D4H
	  #define MaximumKeyHoldTime_MASK           0F0H
    #define MaximumKeyHoldTime_OUTPUT         "OUTPUT"
	  #define MaximumKeyHoldTime_OUTPUT_R   "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
	;//</c>
  
  
    ;//<o>  AutoFrequencyHopping    
    ;//<i> enalbe hardware hopping function
    ;//<i> 0=Close 1=Open
	;//<c>
	  ;//<o>  ADDR
	  ;//<o1> MASK
      ;//<s> OUTPUT
	  ;//<s1> OUTPUT_R
    #define AutoFrequencyHopping_ADDR         0D5H
	  #define AutoFrequencyHopping_MASK         08H
	  #define AutoFrequencyHopping_OUTPUT       "OUTPUT"
    #define AutoFrequencyHopping_OUTPUT_R     "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
	;//</c>


    ;//<o>  OneKeyActive    
    ;//<i> Only one or all key active at the same time
    ;//<0 =>  all key active    
    ;//<1 =>  one key active
	;//<c>
	  ;//<o>  ADDR
	  ;//<o1> MASK
	  ;//<s>  OUTPUT
      ;//<s1> OUTPUT_R
      #define OneKeyActive_ADDR                 0D5H
	  #define OneKeyActive_MASK                 020H
      #define OneKeyActive_OUTPUT               "OUTPUT"
	  #define OneKeyActive_OUTPUT_R             "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
    ;//</c>

  
    ;//<o>  PowerSave    
    ;//<i> Low power mode 
	;//<c>
	  ;//<o>  ADDR
	  ;//<o1> MASK
	  ;//<s>  OUTPUT
      ;//<s1> OUTPUT_R
      #define PowerSave_ADDR                 0D5H
	  #define PowerSave_MASK                 040H
      #define PowerSave_OUTPUT               "OUTPUT"
	  #define PowerSave_OUTPUT_R             "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
    ;//</c>


    ;//<o>  TKL_MovingCalibration   
    ;//<i> Touch key Moving Calibration keys easier to operate
    ;//<0 => Close Open
    ;//<1 => Open
	;//<c>
	  ;//<o>  ADDR
	  ;//<o1> MASK
      ;//<s>  OUTPUT
	  ;//<s1> OUTPUT_R
      #define MovingCalibration_ADDR            0D5H
	  #define MovingCalibration_MASK            080H
      #define MovingCalibration_OUTPUT          "OUTPUT"
	  #define MovingCalibration_OUTPUT_R        "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
    ;//</c> 


    ;//<o>  MainFreqSelect    
    ;//<i> Touch frequency selection
    ;//<0 =>  Normal
    ;//<1 =>  High
    ;//<2 =>  Low
	;//<c>
	  ;//<o>  ADDR
	  ;//<o1> MASK
      ;//<s>  OUTPUT
	  ;//<s1> OUTPUT_R
      #define MainFreqSelect_ADDR               0D4H
	  #define MainFreqSelect_MASK               02H
      #define MainFreqSelect_OUTPUT             "OUTPUT"
      #define MainFreqSelect_OUTPUT_R           "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
	;//</c>


  ;//<r> LOOP_VAR_NAME,LOOP_TIMES
      ;//<o>  KeycnThreshold
      ;//<i> suggestion range 12 ~ 63	   
	  ;//<c> cn
	    ;//<o> ADDR 
        ;//<o1> MASK	 
	    ;//<o2>  ADDR_STEP			
        ;//<s>  OUTPUT
        ;//<s1> OUTPUT_R
        #define KEYcnTHRESHOLD_ADDR              0D8H
        #define KEYcnTHRESHOLD_MASK              07FH	 
	      #define KEYcnTHRESHOLD_ADDR_STEP           1	 
        #define KEYcnTHRESHOLD_OUTPUT            "OUTPUT"
        #define KEYcnTHRESHOLD_OUTPUT_R          "DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"	 	
	  ;//</c>

      
      ;//<o> __KEYcn_WAKE
      ;//<i> SLEEP MODE WORK TOUCH 
	  ;//<c> cn
	    ;//<o>  ADDR 
        ;//<o1> MASK
	    ;//<o2> ADDR_STEP	
        ;//<s>  OUTPUT
        ;//<s1> OUTPUT_R
        #define KEYcn_WAKE_ADDR              	0D8H
        #define KEYcn_WAKE_MASK              	80H	
	    #define KEYcn_WAKE_ADDR_STEP         	  1
        #define KEYcn_WAKE_OUTPUT            	"OUTPUT"
        #define KEYcn_WAKE_OUTPUT_R          	"DoAction('Reserved', 'ReadOptionAddress', 'ADDR', 'MASK')"
      ;//</c>
  ;//</r>	


;////end communication option configuration_ASM
;////start communication data configuration_ASM
;//<i>Preamble=StartAddress,Length
;//02=10H,0x20
;//04=50H,0x20

	;//<r> LOOP_VAR_NAME,LOOP_TIMES
		;//<h>  KEYcn
			 ;//<e>	ENV		
		    ;//<o>  KEYcn_ENV			
			;//<c> cn					
				;//<o>    ADDR			
				;//<o1>   MASK
				;//<o2>	  ADDR_STEP	
				;//<s>    OUTPUT
				;//<s1>   OUTPUT_R				
				#define KEYcn_ENV_ADDR           10H 			
				#define KEYcn_ENV_MASK           0FFFFH
				#define KEYcn_ENV_STEP			 2
				#define KEYcn_ENV_OUTPUT         ""
				#define KEYcn_ENV_OUTPUT_R       "DoAction('Reserved', 'ReadDataAddress', 'ADDR', 'MASK')"
			;//</c>
		  ;//</e>
    ;//</h>
		;//<h>  KEYcn
		  ;//<e>	REF		
		    ;//<o>  KEYcn_REF			
			;//<c> cn					
				;//<o>    ADDR			
				;//<o1>   MASK
				;//<o2>	  ADDR_STEP	
				;//<s>    OUTPUT
				;//<s1>   OUTPUT_R				
				#define KEYcn_REF_ADDR           50H 			
				#define KEYcn_REF_MASK           0FFFFH
				#define KEYcn_REF_STEP			 2
				#define KEYcn_REF_OUTPUT         ""
				#define KEYcn_REF_OUTPUT_R       "DoAction('Reserved', 'ReadDataAddress', 'ADDR', 'MASK')"
			;//</c>
		  ;//</e>		 
		;//</h>

    ;//<h>  KEYcn
		  ;//<e>	RCC		
		    ;//<o>  KEYcn_RCC			
			;//<c> cn					
				;//<o>    ADDR			
				;//<o1>   MASK
				;//<o2>	  ADDR_STEP	
				;//<s>    OUTPUT
				;//<s1>   OUTPUT_R				
				#define KEYcn_RCC_ADDR           0B0H 			
				#define KEYcn_RCC_MASK           0FFH
				#define KEYcn_RCC_STEP			      1
				#define KEYcn_RCC_OUTPUT         ""
				#define KEYcn_RCC_OUTPUT_R       "DoAction('Reserved', 'ReadDataAddress', 'ADDR', 'MASK')"
			;//</c>
		  ;//</e>		 
		;//</h>

        ;//<h>  KEYcn  
		  ;//<e> STATUS
		     ;//<o>  KEYcn_SUATUS			 	
		     ;//<c> cn					
				;//<o>  ADDR 			
				;//<o1> MASK 
				;//<o2> MASK_STEP	
        ;//<s>TRIGGER
				;//<s1> OUTPUT
				;//<s2> OUTPUT_R						
				#define KEYcn_SUATUS_ADDR       08H 			
				#define KEYcn_SUATUS_MASK       01H
				#define KEYcn_SUATUS_STEP		1
        #define KEYcn_SUATUS_TRIGGER           "DoAction('Reserved','ReadDataAddress','ADDR','MASK')>0"    
				#define KEYcn_SUATUS_OUTPUT     ""
				#define KEYcn_SUATUS_OUTPUT_R   "DoAction('Reserved', 'ReadDataAddress', 'ADDR', 'MASK')"
			;//</c>
		  ;//</e>
		 
		  
		;//</h>
    ;//</r>  	




;////end communication data configuration_ASM
;;;;;//




;;;;;// ---------------------------------------------------------------------- //
;;;;;// C exported function,register                                           //
;;;;;// ---------------------------------------------------------------------- //
;/*
ifdef _INCLUDE_C_
;*/
;;;;;// *c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c**c //


;////start option_C


;////end option_C
;;;;;//
;/*
endif
;*/

