#include <msp430.h>
#include "LEDendme.h"
#include "led.h"
#include "switches.h"
#include "stateMachines.h"
#include "buzzer.h"
static int S = 1;
static int SS = 1;
static int Song_index = 0;
//megalovania
static int Song[] = {13699, 13699, 6803, 0, 4545, 0, 4831, 5102, 5714, 13699, 5714, 5102};
unsigned char red_on = 0, green_on = 0, led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};
void led_init()
{
  P1DIR |= LEDS; // bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}
void set_SS(int k){
  SS = k;
}
int get_SS(){
  return SS;
}
int get_S(){//returns current state, used for the wdt counter thing
  return S;
}
void SSAdvance(){//advances sub state;
  switch(SS){
  case 0:
    SS=1;
    break;
  case 1:
    SS=2;
    break;
  case 2:
    SS = 0;
    break;

  }
}
void change_state(int k){//changes state to recieved input
  switch(k){//my very very basic state machine with static variavle S denoting the current state
  case 1:
    S = 1;
    break;
  case 2:
    S = 2;
    break;
  case 3:
    S = 3;
    break;
  case 4:
    S = 4;
    break;

  }
}
void led_update(){//updates led and sound based on button press or not and accordingly
  char ledFlags = 0; 
  if (switch_state_changed) {
    if(switch_state_down){//if button has be pressed
      SS = 0;
      change_state(1);
    }
    if(switch_state_down2){
      change_state(2);
      SS = 0;
    }
    if(switch_state_down3){
      change_state(3);
      SS=0;
    }
    if(switch_state_down4){
      Song_index = 0;
      change_state(4);
      SS=0;
    }
    switch(S){//after finding the button that has been pressed, begins said state
    case 1://off dim bright state
      ledFlags = turn_red();
      buzzer_set_period(0);
      break;
    case 2://alternating blink and sound
      ledFlags = turn_green();
      buzzer_set_period(9696);
      break;
    case 3://dim both lights and sound with them
      ledFlags = 0;
      buzzer_set_period(10000);
      break;
    case 4://play megalovania with changing lights
      ledFlags = turn_red();
      buzzer_set_period(0);
      break;
    }
    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }else{//meaning swtich state has not changed since last check
    //continues in state that has not yet changed
    switch(S){
    case 1://swap leds with solid tune
      if(SS == 0){
	ledFlags = LED_GREEN;
	SSAdvance();
	break;
      }
      if(SS==1){
	ledFlags = turn_red();
	SSAdvance();
	break;
      }
      if(SS == 2){
	SSAdvance();
	break;
      }
      break;
    case 2://change sound and color together, ambulance 
      if(SS == 0){
	buzzer_set_period(6969);
	ledFlags = LED_RED;
	SSAdvance();
	break;
      }
      if(SS==1){
	buzzer_set_period(9696);
	ledFlags = turn_green();
	SS = 0;
	break;
      }
      if(SS==2){
	SSAdvance();
	break;
      }
      break;
    case 3://off dim bright with note
      if(SS == 0){
	ledFlags = 0;
	buzzer_set_period(0);
	break;
      }
      if(SS == 1){
	ledFlags = dim_advance();
	buzzer_set_period(14000);
	break;
      }
      if(SS == 2){
	ledFlags = LED_RED;
	buzzer_set_period(7000);
	break;
      }
      break;
    case 4://song
      if(SS == 0){
	ledFlags = LED_GREEN;
	if(Song_index > 12){
	  Song_index = 0;
	}
	if(Song[Song_index] == 0){//no note is played no led is lit up
	  ledFlags = 0;
	}
	buzzer_set_period(Song[Song_index++]);
	SS = 1;
	break;
      }else{
	ledFlags = LED_RED;
	if(Song_index > 12){//if song has played final note
	  Song_index = 0;
	}
	if(Song[Song_index] == 0){
	  ledFlags = 0;
	}
	buzzer_set_period(Song[Song_index]);
	Song_index+=1;
	SS = 0;
	break;
      }
      break;
    }
    P1OUT &= (0xff - LEDS) | ledFlags;
    P1OUT |= ledFlags;
  }
  
  switch_state_changed = 0;
}

