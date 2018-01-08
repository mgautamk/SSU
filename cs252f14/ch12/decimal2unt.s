# decimal2unt.s
# prompts a user to enter an integer in decimal, then converts it
# to int format.
# Mahesh Gautam - Nov 21 2014

# Constant
	.equ buffSize,12

# Stack frame
	.equ buffer,-16
	.equ theInt,-4
	.equ localSize,-16

# Read only data
	.section .rodata
prompt:
	.asciz "Please enter an integer in decimal: "
format:
	.asciz "You entered %i\n"

# Code
	.text
	.globl main
	.type main, @function
main:
	pushq %rbp # save frame pointer
	movq %rsp, %rbp # new frame pointer
	addq $localSize, %rsp # local vars.

# Tell user what to do.
	movq $prompt, %rdi # prompt user
	call writeStr

# Get decimal number
	movl $buffSize, %esi # max number of chars
	leaq buffer(%rbp), %rdi # place for user input
	call readLn # get user input string

# convert the string to int format
	leaq theInt(%rbp), %rsi # place to store the int
	leaq buffer(%rbp), %rdi # user’s string
	call dec2uInt

	movl theInt(%rbp), %esi # display results
	movq $format, %rdi
	movl $0, %eax
	call printf

	movl $0, %eax # return 0
	movq %rbp, %rsp # restore stack pointer
	popq %rbp # restore base pointer
	ret # back to OS
