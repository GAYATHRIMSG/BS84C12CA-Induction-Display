//cl
#include "Display.h"

typedef unsigned char u8;

//Segment pins
#define Aseg_C      _pac7 
#define Bseg_C      _pdc4 
#define Cseg_C      _pbc6 
#define Dseg_C      _pbc4 
#define Eseg_C      _pbc3 
#define Fseg_C      _pdc5 
#define Gseg_C      _pac1 
#define DPseg_C     _pbc5

#define DIGIT1_C    _pbc7 
#define DIGIT2_C    _pdc1 
#define DIGIT3_C    _pdc0 
#define DIGIT4_C    _pac4

//segment pattern
#define SEG_A       0x01 
#define SEG_B       0x02 
#define SEG_C       0x04 
#define SEG_D       0x08 
#define SEG_E       0x10 
#define SEG_F       0x20 
#define SEG_G       0x40 
#define SEG_DP      0x80

//segment pattern for char
const unsigned char SEGMENT_PATTERNS[14] = { 
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,          // 0 
    SEG_B | SEG_C,                                           // 1 
    SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,                  // 2 
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,                  // 3 
    SEG_B | SEG_C | SEG_F | SEG_G,                          // 4 
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,                  // 5 
    SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,          // 6 
    SEG_A | SEG_B | SEG_C,                                  // 7 
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,  // 8 
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,          // 9
    SEG_G,                                                   // 10: Dash (-)
    SEG_C | SEG_E | SEG_G,                                  // 11: 'n'
    SEG_A | SEG_E | SEG_F | SEG_G,                          // 12: 'F' 
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,                  // 13: 'E'  
};

// ─── Double-buffer ─────────────────────────────────────────────────────────
// display_digits[] = back buffer  – written freely by application logic
// display_shadow[] = front buffer – copied from back only at frame boundary
//
// Display_Update() reads ONLY from display_shadow[], so it always drives a
// complete, coherent snapshot and never mixes digits from two different values
// within the same multiplex frame. That is what was causing the flicker.
// ───────────────────────────────────────────────────────────────────────────
extern unsigned char display_digits[4];
static unsigned char display_shadow[4] = {0xFF, 0xFF, 0xFF, 0xFF};

// Display control variables
unsigned char current_digit   = 0; 
unsigned char display_enabled = 1; 
unsigned char brightness      = 3;

// ─── Display_Init ──────────────────────────────────────────────────────────
void Display_Init(void) 
{ 
    Aseg_C = 0; Bseg_C = 0; Cseg_C = 0; Dseg_C = 0;
    Eseg_C = 0; Fseg_C = 0; Gseg_C = 0; DPseg_C = 0;
    DIGIT1_C = 0; DIGIT2_C = 0; DIGIT3_C = 0; DIGIT4_C = 0;

    Aseg = 0; Bseg = 0; Cseg = 0; Dseg = 0;
    Eseg = 0; Fseg = 0; Gseg = 0; DPseg = 0;

    DIGIT1 = 1; DIGIT2 = 1; DIGIT3 = 1; DIGIT4 = 1;

    current_digit = 0;

    // Sync shadow to back buffer on init
    display_shadow[0] = display_digits[0];
    display_shadow[1] = display_digits[1];
    display_shadow[2] = display_digits[2];
    display_shadow[3] = display_digits[3];
}

// ─── Set_Segments ──────────────────────────────────────────────────────────
void Set_Segments(unsigned char pattern) 
{ 
    Aseg  = (pattern & SEG_A)  ? 1 : 0; 
    Bseg  = (pattern & SEG_B)  ? 1 : 0; 
    Cseg  = (pattern & SEG_C)  ? 1 : 0; 
    Dseg  = (pattern & SEG_D)  ? 1 : 0; 
    Eseg  = (pattern & SEG_E)  ? 1 : 0; 
    Fseg  = (pattern & SEG_F)  ? 1 : 0; 
    Gseg  = (pattern & SEG_G)  ? 1 : 0; 
    DPseg = (pattern & SEG_DP) ? 1 : 0; 
}

// ─── Display_Numbers ───────────────────────────────────────────────────────
// Writes to the BACK BUFFER only. Shadow is updated at the next frame
// boundary inside Display_Update(), keeping the transition atomic.
void Display_Numbers(unsigned int count)
{
    unsigned char d0 = count % 10;
    unsigned char d1 = (count / 10)   % 10;
    unsigned char d2 = (count / 100)  % 10;
    unsigned char d3 = (count / 1000) % 10;

    display_digits[0] = d0;

    if (d3 != 0)
    {
        display_digits[3] = d3;
        display_digits[2] = d2;
        display_digits[1] = d1;
    }
    else if (d2 != 0)
    {
        display_digits[3] = 0xFF;
        display_digits[2] = d2;
        display_digits[1] = d1;
    }
    else if (d1 != 0)
    {
        display_digits[3] = 0xFF;
        display_digits[2] = 0xFF;
        display_digits[1] = d1;
    }
    else
    {
        display_digits[3] = 0xFF;
        display_digits[2] = 0xFF;
        display_digits[1] = 0xFF;
    }
    // display_shadow[] is NOT touched here.
}

// ─── Display_Update ────────────────────────────────────────────────────────
// Call 4x per main-loop pass for one complete refresh frame.
void Display_Update(void) 
{ 
    unsigned char pattern_to_display;

    // ── Frame boundary: latch back-buffer → shadow ─────────────────────────
    // Only at current_digit == 0 (start of new frame). This ensures all four
    // digits in one frame always come from the same value – no torn reads.
    if (current_digit == 0)
    {
        display_shadow[0] = display_digits[0];
        display_shadow[1] = display_digits[1];
        display_shadow[2] = display_digits[2];
        display_shadow[3] = display_digits[3];
    }

    if (!display_enabled) 
    { 
        DIGIT1 = 1; DIGIT2 = 1; DIGIT3 = 1; DIGIT4 = 1;
        return; 
    }
    
    // Blanking before segment change (prevents ghosting)
    DIGIT1 = 1; DIGIT2 = 1; DIGIT3 = 1; DIGIT4 = 1;
    
    // Read from SHADOW, not from display_digits[]
    if (display_shadow[current_digit] < 14)
        pattern_to_display = SEGMENT_PATTERNS[display_shadow[current_digit]];
    else
        pattern_to_display = 0;  // blank
    
    Set_Segments(pattern_to_display);
    
    delay_us(1);  // let segments settle before enabling COM
    
    switch (current_digit) 
    {
        case 0: DIGIT1 = 0; break;
        case 1: DIGIT2 = 0; break;
        case 2: DIGIT3 = 0; break;
        case 3: DIGIT4 = 0; break;
        default: break;
    }
    
    // Brightness on-time
    switch (brightness)
    {
        case 0: delay_us(1); break;
        case 1: delay_us(2); break;
        case 2: delay_us(4); break;
        case 3: delay_us(7); break;
        default: delay_us(4); break;
    }

    // Blanking at end of slot
    DIGIT1 = 1; DIGIT2 = 1; DIGIT3 = 1; DIGIT4 = 1;
    
    current_digit++;
    if (current_digit >= 4)
        current_digit = 0;
}

// ─── PowerON_Display ───────────────────────────────────────────────────────
void PowerON_Display(void)
{
    u8 i;
    _emi = 0;
    ALL_SEGMENT_ON();
    ALL_COM_ON();
    for (i = 0; i < 80; i++) { GCC_CLRWDT(); GCC_DELAY(50000); }
    _emi = 1;
}

// ─── Display_E0_Error ──────────────────────────────────────────────────────
void Display_E0_Error(void)
{
    display_digits[3] = 0xFF;  // blank
    display_digits[2] = 13;    // 'E'
    display_digits[1] = 0;     // '0'
    display_digits[0] = 0xFF;  // blank
}

// ─── PowerOFF_Display ──────────────────────────────────────────────────────
void PowerOFF_Display(void)
{
    u8 i;
    _emi = 0;
    ALL_SEGMENT_OFF();
    ALL_COM_OFF();
    for (i = 0; i < 20; i++) { GCC_CLRWDT(); GCC_DELAY(50000); }
    _emi = 1;
}

// ─── delay_ms ──────────────────────────────────────────────────────────────
void delay_ms(unsigned int ms) 
{ 
    unsigned int i, j; 
    for (i = 0; i < ms; i++)
        for (j = 0; j < 100; j++)
            asm("nop");
}

// ─── delay_us ──────────────────────────────────────────────────────────────
void delay_us(unsigned int us) 
{ 
    unsigned int i; 
    while (us--)
        for (i = 0; i < 4u; i++)
            asm("nop");
}