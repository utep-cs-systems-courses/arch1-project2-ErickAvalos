#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "libTimer.h"

char switch_state_down, switch_state_changed; /* effectively boolean */
char sw_one, sw_two, sw_thr, sw_fou, CURRENT_STATE;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler() {
  char hold = 0;
  char p2val = switch_update_interrupt_sense();
  sw_one = (p2val & SW1) ? 0 : 1;
  sw_two = (p2val & SW2) ? 0 : 1;
  sw_thr = (p2val & SW3) ? 0 : 1;
  sw_fou = (p2val & SW4) ? 0 : 1;
  //switch_state_changed = 1;
  //led_update();
  if(sw_one){
    hold = 1;
    CURRENT_STATE = 1;
    or_sr(0x18);
  }
  if(sw_two){
    hold = 2;
    CURRENT_STATE = 2;
    or_sr(0x18);
  }
  if(sw_thr){
    hold = 3;
    CURRENT_STATE = 3;
    or_sr(0x18);
  }
  if(sw_fou){
    hold = 4;
    CURRENT_STATE = 4;
    or_sr(0x18);
  }
  else {
    if(hold != 1 | hold != 2 | hold != 3 | hold != 4) {
      hold = 0;
      or_sr(0x18);
    }
    CURRENT_STATE = hold;
    or_sr(0x18);
  }
  CURRENT_STATE = hold;
  or_sr(0x18);
  led_update();
}
 
