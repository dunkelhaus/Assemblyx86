#div.c in assembly
.equ counter, 32
	
.data

dividend :
	.long 12

divisor :
	.long 4

remainder :
	.long 0

quotient :
	.long 32

nbits :
	.long 0

count :
	.byte 0

i:
	.long 31

.text
	#eax is used to store the dividend
	#edi is used to store the divisor
	#ecx is used to store the remainder
        #edx is used to store the quotient
        #esi is used to store the number of bits in the dividend
        #ebx is used to store the number of bits in the bits function
        #ebp is used to store the number of iterations

.globl _start
_start:
	movl dividend, %eax
	movl $dividend, %ebp
	movl (%ebp), %ecx
	movl divisor, %edi
	movl remainder, %ecx
	movl quotient, %edx             
        movl i, %esi
	movl $0, %ebx   
                             
nobit:
        incl %ebx
        cmpl $0, %eax
        jz bitreducer
        shr $1, %eax
        decl %esi
        jnz nobit

afterloopreturn :
	movl %edx, %ebx
        jmp top2

bitreducer: 
	decl %ebx
	movl (%ebp), %eax
	movl $0, %edx
	jmp top2

top2:
	
        movl %ecx, %esi
        movl %ebx, %ecx	
	shl  $1, %esi
	shr %cl, %eax
	movl %esi, %ecx
	and $1, %eax
	movl %eax, %esi #esi stores the bit
        movl (%ebp), %eax
	shl $0, %esi
	or %esi, %ecx
	cmpl %edi, %ecx
	jge top3
	decl %ebx
	jge top2

nextjdone:         
	movl %edx, %eax
	movl %ecx, %edx
	jmp done

top3:
	subl %edi, %ecx #check
	pushl %edi
        pushl %ecx
	movl $1, %edi
	movl %ebx, %ecx
	shl  %cl, %edi
	or %edi, %edx
	popl %ecx
	popl %edi
	decl %ebx
	jmp top2

done:   movl %edi, %edi	
