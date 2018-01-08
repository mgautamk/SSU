# putInt.s
# writes a signed int to standard out
# Mahesh Gautam - 21 Nov 2014

# Calling sexquence
#	edi <- value of the int
#	call putInt

# Stack frame
	.equ buffer,-12
	.equ localSize,-16
# Code
	.text
	.globl putInt
	.type putInt, @function
putInt:
	pushq %rbp # save callers frame ptr
	movq %rsp, %rbp # our stack frame
	addq $localSize, %rsp # local vars.

	movl %edi, %esi # number to convert
	leaq buffer(%rbp), %rdi # place to store string
	call sInt2dec # do the conversion to string

	leaq buffer(%rbp), %rdi # place where string stored
	call writeStr # write it

	movl $0, %eax # return 0
	movq %rbp, %rsp # delete local vars.
	popq %rbp # restore caller frame ptr
	ret
	
