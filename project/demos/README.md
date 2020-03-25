## Description
Use the button demo to load onto the MSP430
The button demo contains all of the finalized working files

buttonMain.c only initializes all procedures and begins the program, not much
to note it doesn't do much work itself

led.c
This file does all the main work, using 2 static variables that keep track of
states that should admitably be transfered to statemachines.c but i didn't
because I was running out of time personally. Using the static variables to
keep track of state the function led_update() will see if a button was pressed
or not, if so move and being the next state appropriately, if no button was
pressed continue into the next substate for that state. State 1 is mapped to
button1, State 2 to button2, etc. State1's goals is just alternate red and
green with no sound at all. State2 alternates red and green leds with a sound
mapped to each one, it should sound skin to a siren on an ambulance. State 3
should go from no light to a dim light to a bright red light. Each with
appropriate sound of none, low tone, high tone. State4 plays a riff of a song
using the frequency of each note not in Hz but in microseconds.

LEDendme.s
This is the assembly file asked of us to be used. All i did was import the
msp430 and return the bits assigned to the red led and green led in the two
functions turn_red and turn_green.

wdInterrupthandler.c
This is the 'clock' in my msp430 that will increment substates in real time
based off of a counter and the state that the main function is in.

statemachines.c
This function is used to create the dimming effect by having a state machine
that is intended to be gone through extremely fast in order to be preceived as
a 'dim' light, it goes in order of off off off on in oder to be dimmed.

buttons.c
This is the function that intialized our buttons on the msp430 and allows for
them to be used.

buzzer.c
This activates the buzzer on the msp430 accessory and plays a tone using
microseconds

p1-interrupt-handler.c
Helps the buttons be read from the msp430 accessory
