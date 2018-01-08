# getInt.s
# reads an int from standard in
# Mahesh Gautam, Nov 21 2014

# Calling sequence
#	 rdi <- pointer where to store the int
#	 call getInt
#	 returns 0
	
# Stack frame
	.equ outPtr,-24
	.equ buffer,-12
	.equ localSize,-32
# Code
	.text
	.globl getInt
	.type getInt, @function
getInt:
	pushq %rbp # save callers frame ptr
	movq %rsp, %rbp # our stack frame
	addq $localSize, %rsp # local vars.
	
	movq %rdi, outPtr(%rbp) # save argument
	
	movl $12, %esi # max number of chars
	leaq buffer(%rbp), %rdi # place where string stored
	call readLn # read it
	
	movq outPtr(%rbp), %rsi # place to store number
	leaq buffer(%rbp), %rdi # address of string
	call dec2sInt # convert string to int
	
	movl $0, %eax # return 0
	movq %rbp, %rsp # delete local vars.
	popq %rbp # restore caller frame ptr
	ret
