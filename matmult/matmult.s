.global matMult

.equ wordsize, 4

.text

#int** matsum(int** a, int** b, int num_rows, int num_cols){
#int i,j;
#int** c;
#c = (int**) malloc(num_rows * sizeof(int*));
#for(i = 0; i < num_rows; i++){
# c[i] = (int*) malloc(num_cols *sizeof(int));
# for(j = 0; j < collen; j++){
#   c[i][j] = a[i][j] + b[i][j];
# }
#}
#}

matMult: #int** matsum(int** a, int** b, int num_rows, int num_cols)
	#on entry stack looks like
	#esp + 24: num_cols_b
	#esp + 20: num_rows_b
	#esp + 16: b
	#esp + 12: num_cols_a
	#esp + 8: num_rows_a
	#esp + 4: a
	#esp: return address
  
	#prologue
	push %ebp
	movl %esp, %ebp
	
	#esi will alternate between a and b
	#edi will hold c
	#ecx will be i. no push because ecx does not contain a live value
	#edx will be j. no push because edx does not contain a live value
	#eax will be used for temp storage. no push because eax does not contain a live value
  	#ebx 	will be used for temp storage
  	subl $wordsize, %esp #make space for i on the stack
  	push %esi
  	push %ebx
  	push %edi
  	
  	#first step is to make space for c
  	movl 3*wordsize(%ebp), %eax # place num_rows in eax
  	shll $2, %eax #num_rows * sizeof(int*). a pointer is 4 bytes big so we shift eax by 2 to multiply 4
	push %eax
	call malloc 
  	movl %eax, %edi #the result of a function call is placed in %eax
  	#so we copy that value over to edi
  	addl $wordsize, %esp #clear our argument off the stack
 	 
  	xorl %ecx, %ecx #i = 0. this is a quick way to set a register to 0
 	 
  	#i < rowlen == i - rowlen < 0
  	#negation i - rowlen >= 0
row_for:
	cmpl 3*wordsize(%ebp), %ecx #this is num_rows
    	jge end_row_for
    
    	#now make the call to malloc
    	movl 4*wordsize(%ebp), %eax #put num_cols in %eax
    	shll $2, %eax #num_cols * sizeof(int*). a pointer is 4 bytes big so we shift eax by 2 to multiply 4
    	push %eax #put argument to malloc on the stack
    	movl %ecx, -wordsize(%ebp) #now need to make sure to save %ecx because malloc could overwrite it
    	call malloc
    	addl $wordsize, %esp #clear our argument off the stack
    	movl -wordsize(%ebp), %ecx #restore ecx to be i again
    	
    	movl %eax, (%edi, %ecx, wordsize) #c[i] = (int*) malloc(num_cols *sizeof(int));
   	 
    	xorl %edx, %edx #j = 0
    	
    	#j < num_cols == j - num_cols < 0
    	#negation: j - num_cols >= 0
col_for:
    	cmpl 5*wordsize(%ebp), %edx
    	jge end_col_for
	xorl %ebx, %ebx # k = 0

k_for:
	cmpl 4*wordsize(%ebp), %ebx
	jge end_k_for
	pushl %eax
    	
    	#bring a[i][k] into %eax
    	movl 2*wordsize(%ebp), %esi #put a int %esi
   	movl (%esi, %ecx, wordsize), %esi #put a[i] into esi
      	movl (%esi, %ebx, wordsize), %eax #put a[i][k] into eax
      	
      	#a[i][k] * b[k][j]
      	movl 5*wordsize(%ebp), %esi #put b int %esi
      	movl (%esi, %ebx, wordsize), %esi #put b[k] into esi
      	imull (%esi, %edx, wordsize) #put a[i][k]*b[k][j] into eax
	cmpl $0, %ebx
	jz fixesi
fixesilabel:
	addl %eax, %esi # sum the values
	popl %eax
	incl %ebx # k++
	jmp k_for
	
      	#eax currently points to c[i]
      	movl %esi, (%eax, %edx, wordsize) #c[i][j] = a[i][k] * b[k][j]

end_k_for:
	
	incl %edx # j++
	jmp col_for

fixesi:
	xorl %esi, %esi
	jmp fixesilabel
      	
end_col_for:
    
    	incl %ecx #i++
    	jmp row_for

end_row_for:
      
  	#put the return value in eax
  	movl %edi, %eax
  
  
  	#restore registers
  	pop %edi
  	pop %ebx
  	pop %esi
  
  
  	#epilogue
  	movl %ebp, %esp
  	pop %ebp
  
  	#go back to where we were called from
  	ret
  
