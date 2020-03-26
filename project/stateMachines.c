#include <stdlib.h>
#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char led_count()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 0;
    green_on = 0;
    state = 1;
    break;
  case 1:
    red_on = 1;
    green_on = 0;
    state = 2;
    break;
  case 2:
    red_on = 0;
    green_on = 1;
    state = 3;
    break;
  case 3:
    red_on = 1;
    green_on = 1;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

void reset() {
  red_on = 0;
  green_on = 0;
  led_update();
}

void state_advance(unsigned char r, unsigned char g) {
  red_on = r;
  green_on = g;
  led_changed = 1;
  led_update();
}
//char toggle_green()	/* only toggle green if red is on!  */
/*
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}
*/
/*
void state_advance()		/* alternate between toggling red & green 
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red_green(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}
*/


