#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

int main() {
    configureClocks();
 
    buzzer_init();
    buzzer_set_period(1000);	/* start buzzing!!! */
    buzzer_set_period(2000);
    buzzer_set_period(3000);
    or_sr(0x18);          // CPU off, GIE on
}
