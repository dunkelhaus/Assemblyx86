# Program to find the edit distance between two strings
# EAX holds the actual edit distance
# EBX goes through oldDist
# ECX goes through curDist
# EDX holds string length

.data

string1: 
	.space 100

string2:
	.space 100

word1len:
	.long 0

word2len:
	.long 0

oldDist:
	.rept 100
	.long 0
	.endr

curDist:
	.rept 100
	.long 0
	.endr

.text # code section begins

.globl _start
_start:
#	movl $string1sp, string1
#	movl $string2sp, string2
	movl $string1, %edi
	xorb %al, %al 
	movl $-1, %ecx 
	repne scasb 

	subl $string1, %edi
	movl %edi, word1len
	
	movl $string2, %edi
	xorb %al, %al 
	movl $-1, %ecx 
	repne scasb 

	subl $string2, %edi
	movl %edi, word2len
	
	movl $oldDist, %ebx
	movl $curDist, %ecx
	movl $word2len, %eax
	movl (%eax), %edx
	decl %edx
	movl $0, %esi

initDist:
	cmpl %edx, %esi
	jg resetvals
	movl %esi, (%ebx)
	addl $4, %ebx
	movl %esi, (%ecx)
	addl $4, %ecx
	incl %esi
	cmpl %edx, %esi
	jbe initDist

resetvals:
	movl $word1len, %eax
	movl (%eax), %edx
	movl $oldDist, %ebx
	movl $curDist, %ecx
	movl $1, %esi

outerloop:
	cmpl %edx, %esi
	jge afterouter
	movl %esi, (%ecx)

resetj:
	movl $0, %edi
	jmp innerloop

ifloop:
	movl %edi, %eax
	
#oldDistloop:
#	addl $4, %ebx
#	decl %edi
#	jnz oldDistloop

next:
#	subl $4, %ebx
	movl %eax, %edi
	
curDistloop:
	addl $4, %ecx
#	decl %edi
#	jnz curDistloop

next2:
	movl %eax, %edi
	movl (%ebx), %eax
	movl %eax, (%ecx)
	addl $4, %ebx
	jmp innerloop

elseloop:
	movl %edi, %eax

curDistloop2:
	addl $4, %ecx
#	decl %edi
#	jnz curDistloop2
	
after:
	subl $4, %ecx
	movl %eax, %edi

oldDistloop2:
	addl $4, %ebx
#	decl %edi
#	jnz oldDistloop2

after2:
	movl %eax, %edi
	movl (%ebx), %eax
	cmpl %eax, (%ecx)
	jae smallebx
	jl smallecx

smallebx:
	subl $4, %ebx
	cmpl %eax, (%ebx)
	jae outersmallebx1 # eax
	jl outersmallebx2

smallecx:
	subl $4, %ebx
	movl (%ecx), %eax
	cmpl %eax, (%ebx)
	jae outersmallecx2
	jl outersmallebx2

outersmallebx1:
	addl $4, %ebx
	movl (%ebx), %eax
	incl %eax
	subl $4, %ebx
	addl $4, %ecx
	movl %eax, (%ecx)
	addl $4, %ebx
	jmp innerloop

outersmallebx2:
	movl (%ebx), %eax
	incl %eax
	addl $4, %ecx
	movl %eax, (%ecx)
	addl $4, %ebx
	jmp innerloop

outersmallecx2:
	movl (%ecx), %eax
	incl %eax
	addl $4, %ecx
	movl %eax, (%ecx)
	addl $4, %ebx
	jmp innerloop

innerloop:
	decl %esi
	call setstrings
	movb (%edx, %edi), %al
	movb (%ebp, %esi), %ah
	incl %edi
	incl %esi
	pushl %esi
	movl $word2len, %esi
	movl (%esi), %edx
	popl %esi
	cmpl %edi, %edx
	jle afterinner
	cmpb %al, %ah
	jz ifloop
	jnz elseloop
	jmp afterinner

setstrings:
	movl $string1, %ebp
	movl $string2, %edx
	ret

afterinner:
	incl %esi
	movl %esi, %eax
	movl $word1len, %esi
	movl (%esi), %edx
	movl %eax, %esi

esilooper:
	decl %esi
	decl %esi
	jg esilooper
	jz evenesi
	jl oddesi

evenesi:
	movl $oldDist, %ecx
	movl $curDist, %ebx
	movl %eax, %esi
	jmp outerloop

oddesi:
	movl $oldDist, %ebx
	movl $curDist, %ecx
	movl %eax, %esi
	jmp outerloop

afterouter:
	movl $word2len, %eax
	movl (%eax), %edx
	movl %edx, %esi
	decl %esi

oldDistfinal:
	addl $4, %ebx
	decl %esi
	jnz oldDistfinal

continuing:
	movl (%ebx), %eax

done:  movl $word1len, %edx
