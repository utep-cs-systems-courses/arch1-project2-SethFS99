	.arch msp430g2553
	.p2align 1,0
	.data

State:
	.word 1		;State variable S goes from 0-3

	.text
jt:
	.word default
	.word option1
	.word option2
	.word option3
	.word option4
	.global dim_advance
dim_advance:
	CMP #4,&State
	JHS default
	mov &State,r12
	add r12,r12
	mov jt(r12),r0
option1:
	mov #2,&State
	ret 0
	jmp out
option2:
	mov #3,&State
	ret 0
	jmp out
option3:
	mov #4,&State
	ret 0
	jmp out
option4:
	mov #1,&State
	ret BIT0
	jmp out
default:
	mov #1,&State
	ret 0
out:
	ret 0
