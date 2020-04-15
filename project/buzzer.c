#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define _A 1760
#define _C 2093
#define _E 1318

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  TA0CCR0 = cycles; 
  TA0CCR1 = cycles >> 5;		/* one half cycle */
}

void song() {
  buzzer_set_period(_A);
  length();
  buzzer_set_period(_C);
  length();
  buzzer_set_period(_E);
  length();
}

void length() {
  __delay_cycles(16000000/1);
}
    
    
  

