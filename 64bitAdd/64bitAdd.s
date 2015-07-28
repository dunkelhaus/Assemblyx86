# add two 64 bit numbers together
# EAX holds lower 32 bits
# EDX holds upper 32 bits
# EBX traverses num1
# ECX traverses num2

.data

num1: 
	.long 12
	.long 12

num2:
	.long 12
	.long 12

sum:
	.long 0
	.long 0

.text

.globl _start

allNegative:
	incl %edx
 	ret
_start:
	movl $num1, %ebx
	movl $num2, %ecx
	addl (%ebx), %edx
	addl (%ecx), %edx
	addl $4, %ebx
	addl $4, %ecx
	addl (%ebx), %eax
	addl (%ecx), %eax
	jl allNegative
done: movl %ebx, sum 
