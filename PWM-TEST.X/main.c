#include "mcc_generated_files/mcc.h"

#define _XTAL_FREQ 8000000

void PWM3_LoadDutyValue(uint16_t dutyValue);

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    //RA3 analog
    ANSELA = 0x08;
    //RA(CCP3) Output
    TRISA = 0xF7;
    
    
    //pwm initialize
    // CCP3M PWM; DC3B 3; 
	CCP3CON = 0x3C;    
	// CCPR3L 127; 
	CCPR3L = 0x7F;    
	// CCPR3H 0; 
	CCPR3H = 0x00;    
	// Selecting Timer 2
	CCPTMRS0bits.C3TSEL = 0x0;
    
    //timer2 initialize
     // PR2 255; 
    PR2 = 0xFF;
    // TMR2 0; 
    TMR2 = 0x00;
    // Clearing IF flag.
    PIR1bits.TMR2IF = 0;
    // T2CKPS 1:1; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0x04;
    
    uint16_t count = 0;

    while (1)
    {
        if(count == 1023){
            count = 0;
        }
        
        PWM3_LoadDutyValue(count);
        
        __delay_ms(10);
        
        count++;
    }
}

void PWM3_LoadDutyValue(uint16_t dutyValue)
{
   // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR3L = ((dutyValue & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP3CON = ((uint8_t)(CCP3CON & 0xCF) | ((dutyValue & 0x0003)<<4));
}

/**
 End of File
*/