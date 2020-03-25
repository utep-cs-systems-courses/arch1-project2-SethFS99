	.arch msp430g2553

	.text
	.global turn_red	;return bit0 the address of the the red led
turn_red:
	ret BIT0
	.global turn_green	;return bit6 the address of the greed led
turn_green:
	ret BIT6
