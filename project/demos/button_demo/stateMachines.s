	.arch msp430g2553
	.data
	S word 0000		;State variable S goes from 0-3

	
	.text			;my states 0 - 3
	.word case0:
	.word case1:
	.word case2:
	.word case3:

	.global dim_advance
dim_advance:
	CMP S,#0
	JEQ case0
	CMP S,#1
	JEQ case1
	CMP S,#2
	JEQ case2
	CMP S,#3
	JEQ case3

case0:
	mov #1,S
	ret 0			;change s and update led

case1:
	move#2,S
	ret 0

case2:
	mov #3,S
	ret 0
case3:
	mov #0,S
	ret BIT0
