#include<msp430.h>
#include"stateMachines.h"
#include"led.h"

void __interrupt_vec(WDT_VECTOR) WDT(){//250 interrupts in a second
  static char blink_count = 0;
  int S = get_S();
  int SS = get_SS();
  switch(S){
  case 1:
    if(blink_count++ == 250){
      // state_advance();
      led_update();
      blink_count = 0;//reset count
    }
    break;
  case 2:
    if (blink_count++ == 125){
      led_update();
      blink_count = 0;
    }
    break;
  case 3:
    switch(SS){
    case 0:
      if(blink_count++ == 250){
	led_update();
	blink_count = 0;
	set_SS(1);
      }else{
	led_update();
      }
      break;
    case 1:
      if(blink_count++ == 250){
	blink_count = 0;
	set_SS(2);
      }else{
	led_update();
      }
      break;
    case 2:
      if(blink_count++ == 250){
	led_update();
	blink_count = 0;
	set_SS(0);
      }else{
	led_update();
      }
      break;
      
    }
    break;
  case 4:
    if(blink_count++ == 40){
    led_update();
    blink_count = 0;
    }
    break;
  }


}
