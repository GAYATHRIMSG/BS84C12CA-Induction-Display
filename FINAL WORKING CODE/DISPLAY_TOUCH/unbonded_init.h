/*******************************************************************************
  * @file     unbonded_init.h
  * @brief    This file is used to initialize unbonded pins.
  * @author   Holtek Semiconductor Inc.
  * @version  1
  * @date     2026-2-20 (11-01-10)
 *******************************************************************************
  * @attention
  *
  * Firmware Disclaimer Information

  * 1. The customer hereby acknowledges and agrees that the program technical
  *    Holtek Semiconductor Inc., (hereinafter referred to as 'HOLTEK') 
  *    is the proprietary and confidential intellectual property of HOLTEK,
  *    and is protected by copyright law and other intellectual property laws.
  *
  * 2. The customer hereby acknowledges and agrees that the program technical
  *    documentation, including the code, is confidential information belonging
  *    to HOLTEK, and must not be disclosed to any third parties other than
  *    HOLTEK and the customer.
  *
  * 3. The program technical documentation, including the code,
  *    is provided 'as is' and for customer reference only.
  *    After delivery by HOLTEK, the customer shall use the program
  *    technical documentation,including the code, at their own risk.
  *    HOLTEK disclaims any expressed, implied or statutory warranties,
  *    including the warranties of merchantability,
  *    satisfactory quality and fitness for a particular purpose.
  *
  * @attention
  * Do not modify manually
  *
  * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ******************************************************************************/

void Init_Unbonded_Pins()
{
   //For lower pin-count packages, some pins may be unbonded.
   //These pins should be properly configured to avoid extra current
   //consumption caused by floating inputs.
   //Please refer to the "Standby Current Considerations" and
   //"Input/Output Ports" sections in the datasheet for details.
	_pcpu |= 0x0F;
	_pdpu |= 0xCC;
}
