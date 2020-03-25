#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
static int S = 0;

char dim_advance(){
  char ledFlags = 0;
  switch(S){
  case 0:
    S = 1;
    return ledFlags;
  case 1:
    S = 2;
    return ledFlags;
  case 2:
    S = 3;
    return ledFlags;
    break;
  case 3:
    S = 0;
    ledFlags = LED_RED;
    return ledFlags;
    break;
  }
}
