#include <msp430.h>
#include "led.h"
#include "stateMachines.h"
#include "switches.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;
unsigned char led_dim = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

static int IncDec_PWM = 1;


void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_changed = 1;
  led_dim = 1;
  led_update();
}

void led_update()
{
  if (led_changed | led_dim | switch_state_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];
    
    P1OUT &= (0xff^LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;		     // set bit for on leds
  }
  switch_state_changed = 0;
  led_changed = 0;
  led_dim = 0;
}

void dim() {
  DCOCTL = 0;
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  P1DIR |= BIT6;
  P1SEL |= BIT6;

  TA0CCR0 |= 1000-1;
  TA0CCR1 |= 1;
  TA0CCTL1 |= OUTMOD_7;
  TA0CTL |= TASSEL_2 + MC_1;

  TA1CCR0 |= 4000-1;
  TA1CCTL0 |= CCIE;
  TA1CTL |= TASSEL_2 + MC_1;

  _BIS_SR(LPM0_bits + GIE);
}

void led_count() {
  static char leds = 0;
  switch (leds) {
  case 0:
    red_on = 0;
    green_on = 0;
    leds = 1;
    break;
  case 1:
    red_on = 1;
    green_on = 0;
    leds = 2;
    break;
  case 2:
    red_on = 0;
    green_on = 1;
    leds = 3;
    break;
  case 3:
    red_on = 1;
    green_on = 1;
    leds = 0;
    break;
  }
  led_update();
  return 1;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void) {
  while (1) {
    TA0CCR1 += IncDec_PWM*2;
    if (TACCR1 > 998 || TA0CCR1 < 2)
      IncDec_PWM = -IncDec_PWM;
  }
}


