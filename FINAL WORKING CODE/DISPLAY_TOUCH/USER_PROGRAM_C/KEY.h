/******************************************************************************
 * KEY.h - Header file for Capacitive Touch Key Handler
 * 
 * Description: Function prototypes for key scanning and processing
 ******************************************************************************/

#ifndef _KEY_H_
#define _KEY_H_

// Type definitions for compatibility
typedef unsigned char  u8;
typedef unsigned int   u16;
typedef volatile u8    vu8;
typedef volatile u16   vu16;

/******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * Initialize key handling subsystem
 */
void Key_Init(void);

/**
 * Scan and debounce capacitive touch keys
 * @param u16_Key_Buf_Temp - Current key buffer value from touch scan
 */
void Key_Scan(u16 u16_Key_Buf_Temp);

/**
 * Process key events and execute corresponding actions
 */
void Key_Drive(void);

#endif /* _KEY_H_ */