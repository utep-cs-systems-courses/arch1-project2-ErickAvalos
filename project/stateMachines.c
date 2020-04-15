#include <stdlib.h>
#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

void stateMachine() {
  char state = CURRENT_STATE;
  switch(state) {
  case 1:
    //state = 1;
    dim();
    break;
  case 2:
    //state = 2;
    led_update();
    led_count();
    break;
  case 3:
    //state = 3;
    song();
    break;
  case 4:
    //state = 4;
    song();
  }
}
