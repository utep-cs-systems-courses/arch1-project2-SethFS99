#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void __interrupt_vec(WDT_VECTOR) WDT(){//250 interrupts/sec
  static char blink_count = 0;
  if (blink_count++ == 125 ) {
    state_advance();
    blink_count = 0;
  }
}
/*
void __interrupt_vec(WDT_VECTOR) WDT(){// 250 interrupts/sec

  static char blink_count = 0;
  if (++blink_count == 250) {
    sm_slow_clock();
    blink_count = 0;
  }
  sm_fast_clock();
  sm_update_led();
  led_update();
}*/