
.globl knapsack

.equ wordsize, 4

.text

knapsack:

	# prologue
	push %ebp
	movl %esp, %ebp

	# push all live registers for use
	pushl %esi
	pushl %ebx
	pushl %edi

	# name all variable offsets
	.equ weights, 2*wordsize
	.equ values, 3*wordsize
	.equ num_items, 4*wordsize
	.equ capacity, 5*wordsize
	.equ cur_value, 6*wordsize
	
	movl num_items(%ebp), %edi # edi is num_items
	movl $0, %esi # esi is i, incrementing up to edi
	movl weights(%ebp), %ecx # ecx starts weights, alt values
	movl cur_value(%ebp), %edx # best_value
	movl capacity(%ebp), %eax # eax holds capacity
	movl cur_value(%ebp), %ebx # ebx holds cur_value
	
mainloop:
	
	cmpl %esi, %edi
	jbe endmethod
	push %edx
	movl %eax, %edx
	subl (%ecx), %edx
	cmpl $0, %edx
	jae ifloop
	jb afterfor
	
ifloop:
	
	movl values(%ebp), %ecx
	addl (%ecx), %ebx # cur_value
	push %ebx
	movl %edx, %eax # capacity
	push %eax
	subl %esi, %edi # num_items
	subl $1, %edi
	push %edi
	leal wordsize(%ecx), %ecx # values
	push %ecx 
	movl weights(%ebp), %ecx # weights
	leal wordsize(%ecx), %ecx
	push %ecx
	call knapsack # recurse
	cmpl %ebx, %edx
	ja afterfor
	jbe lessernew

lessernew:
	
	movl %ebx, %edx
	
afterfor:
	
	movl cur_value(%ebp), %ebx
	incl %esi
	movl num_items(%ebp), %edi
	cmpl %esi, %edi
	ja mainloop
	jbe endmethod

endmethod:
	
	addl $(6*wordsize), %esp
	# restore registers
	popl %edi
	popl %ebx
	popl %esi
	# epilogue
	movl %ebp, %esp
	pop %ebp
	ret
