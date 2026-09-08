 


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




;;;;;/*********************************************************************************************************//**
;;;;;// * @file    TK_IIC_HXT_SLAVE.INC
;;;;;// * @version V1.00
;;;;;// * @date    11/13/2020
;;;;;// * @brief   The header file of the TK_IIC_HXT_SLAVE library.
;;;;;// *************************************************************************************************************
;;;;;// * @attention
;;;;;// * <h2><center>Copyright (C) Best Solution Inc. All rights reserved</center></h2>
;;;;;// ************************************************************************************************************/

;;;;;///* Includes ------------------------------------------------------------------------------------------------*/
#define TK_IIC_HXT_SLAVE_DEF
#include "..\GLOBE\GLOBE_VARIES.INC"
#include "..\GLOBE\GLOBE_INCLUDE.INC"
#include "IIC_SLAVE_HXT_CTOUCH_V512.DEF"


ifndef ___TK_IIC_HXT_SLAVE

;/*--------- <<<config>>> -----------------*/
;//<include file>
;//<simple description>Simple prompt message
;//<support MCU>BS82C16CA\BS82D20CA\BS83B04C\BS83B08C\BS83B12C\BS83B16C\BS84B08C\BS84C12C\BS84C12CA\BS84D20CA\BS86C08C\BS86D12C\BS86C12CA\BS86E16C\BS86D20C\BS86D20CA\BS86E20CA\BS66F340C\BS66F350C\BS66F360C\BS67F350C
;//<use HardWare> IIC_SDA
;//<use Language>asm
;//<config Diagram Png>IIC.png
;//<config Diagram Pin>0x00FF00,RightCenter,0x00FE00,RightCenter
;//<communication Packages>True
;//<QuickConfig>Disable Tool,IIC(HXT Editor),1,115200
;//<PackageType>COMM_TYPE
;//<EnablePackage> DoAction("TK_IIC_HXT_SLAVE", "EnablePackage", "TOUCH_TYPE")  && !DoAction("TK_IIC_HXT_SLAVE", "EnablePackage","COMM_TYPE") 

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
;/*-------- <<<\config>>> ----------------*/

;/*-------- <<<globe>>> ------------------*/
#define ___TK_IIC_HXT_SLAVE
;/*-------- <<<\globe>>> ------------------*/


;/*-------- <<<communication_option>>> ------------------*/
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

;/*-------- <<<\communication_option>>> ------------------*/

;/*-------- <<<communication_data>>> ------------------*/
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



;/*-------- <<<\communication_data>>> ------------------*/


;/*-------- <<<option>>> ------------------*/

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
            
;/*-------- <<<\option>>> ------------------*/



endif