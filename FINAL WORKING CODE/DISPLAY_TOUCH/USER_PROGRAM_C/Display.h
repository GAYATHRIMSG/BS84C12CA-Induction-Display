/******************************************************************************
 * Display.h - Header file for 7-Segment Display Driver
 * 
 * Description: Function prototypes and macros for display control
 ******************************************************************************/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <BS84C12CA.H>

/******************************************************************************
 * Pin Definitions - Segments (needed for macros)
 ******************************************************************************/
#define Aseg        _pa7 
#define Bseg        _pd4 
#define Cseg        _pb6 
#define Dseg        _pb4 
#define Eseg        _pb3 
#define Fseg        _pd5 
#define Gseg        _pa1 
#define DPseg       _pb5

/******************************************************************************
 * Pin Definitions - Digit Control (needed for macros)
 ******************************************************************************/
#define DIGIT1      _pb7 
#define DIGIT2      _pd1 
#define DIGIT3      _pd0 
#define DIGIT4      _pa4

/******************************************************************************
 * Macros for controlling all segments and digits at once
 ******************************************************************************/
#define ALL_SEGMENT_OFF()   Aseg = 0, Bseg = 0, Cseg = 0, Dseg = 0, \
                            Eseg = 0, Fseg = 0, Gseg = 0, DPseg = 0

#define ALL_SEGMENT_ON()    Aseg = 1, Bseg = 1, Cseg = 1, Dseg = 1, \
                            Eseg = 1, Fseg = 1, Gseg = 1, DPseg = 1

#define ALL_COM_ON()        DIGIT1 = 0, DIGIT2 = 0, DIGIT3 = 0, DIGIT4 = 0

#define ALL_COM_OFF()       DIGIT1 = 1, DIGIT2 = 1, DIGIT3 = 1, DIGIT4 = 1

/******************************************************************************
 * External Variables
 ******************************************************************************/
extern unsigned char brightness;
extern unsigned char display_enabled;

/******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * Initialize display pins and turn off all segments
 */
void Display_Init(void);

/**
 * Set segment pattern for a single digit
 * @param pattern - 8-bit pattern where each bit controls a segment
 */
void Set_Segments(unsigned char pattern);

/**
 * Convert a number to display format with leading zero suppression
 * @param count - Number to display (0-9999)
 */
void Display_Numbers(unsigned int count);

/**
 * Multiplexing update routine - MUST be called continuously in main loop
 * Updates one digit at a time for smooth, flicker-free display
 */
void Display_Update(void);

/**
 * Display all segments ON for 1 second (power-on test)
 */
void PowerON_Display(void);


void Display_E0_Error(void);
/**
 * Turn off all segments and digits
 */
void PowerOFF_Display(void);

/**
 * Delay function - milliseconds (approximate)
 * @param ms - Number of milliseconds to delay
 */
void delay_ms(unsigned int ms);

/**
 * Delay function - microseconds (approximate)
 * @param us - Number of microseconds to delay
 */
void delay_us(unsigned int us);

#endif /* _DISPLAY_H_ */