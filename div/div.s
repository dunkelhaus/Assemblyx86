	.file	"div.c"
	.text
	.globl	no_bits
	.type	no_bits, @function
no_bits:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	movl	$0, -4(%ebp)
	jmp	.L2
.L5:
	addl	$1, -8(%ebp)
	cmpl	$0, 8(%ebp)
	jne	.L3
	movl	-8(%ebp), %eax
	jmp	.L4
.L3:
	shrl	8(%ebp)
	addl	$1, -4(%ebp)
.L2:
	cmpl	$31, -4(%ebp)
	jle	.L5
	movl	$32, %eax
.L4:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	no_bits, .-no_bits
	.globl	division
	.type	division, @function
division:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	$0, -4(%ebp)
	movl	16(%ebp), %eax
	movl	$0, (%eax)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	no_bits
	movl	%eax, -12(%ebp)
	movl	$0, -8(%ebp)
	movl	-12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -8(%ebp)
	jmp	.L7
.L9:
	movl	16(%ebp), %eax
	movl	(%eax), %eax
	leal	(%eax,%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	movl	-8(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%eax, %ecx
	shrl	%cl, %edx
	movl	%edx, %eax
	andl	$1, %eax
	movl	%eax, -16(%ebp)
	movl	16(%ebp), %eax
	movl	(%eax), %eax
	orl	-16(%ebp), %eax
	movl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	movl	16(%ebp), %eax
	movl	(%eax), %eax
	cmpl	12(%ebp), %eax
	jb	.L8
	movl	16(%ebp), %eax
	movl	(%eax), %eax
	subl	12(%ebp), %eax
	movl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	movl	-8(%ebp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	orl	%eax, -4(%ebp)
.L8:
	subl	$1, -8(%ebp)
.L7:
	cmpl	$0, -8(%ebp)
	jns	.L9
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	division, .-division
	.section	.rodata
.LC0:
	.string	"%lu / %u = "
.LC1:
	.string	"%u R %u\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$0, 16(%esp)
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	atoll
	movl	%eax, 28(%esp)
	movl	12(%ebp), %eax
	addl	$8, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	atoi
	movl	%eax, 24(%esp)
	movl	24(%esp), %eax
	movl	%eax, 8(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	leal	16(%esp), %eax
	movl	%eax, 8(%esp)
	movl	24(%esp), %eax
	movl	%eax, 4(%esp)
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	division
	movl	%eax, 20(%esp)
	movl	16(%esp), %eax
	movl	%eax, 8(%esp)
	movl	20(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.3 20140911 (Red Hat 4.8.3-7)"
	.section	.note.GNU-stack,"",@progbits
