# ExtraCredit.s
# Prompts user to enter a Hexadecimal, then displays its decimal equivalent
# Mahesh Gautam - 10 Oct 2014

# Stack frame
	.equ anInt,-4
	.equ localSize,-16
# Read only data
	.section .rodata
prompt:
	.string "Enter a Hexidecimal number and I will convert it to Decimal: "
scanFormat:
	.string "%x"
printFormat:
	.string "%x = %i\n"
# Code
	.text # switch to text segment
	.globl main
	.type main, @function
main:
	pushq %rbp # save caller’s base pointer
	movq %rsp, %rbp # establish our base pointer
	addq $localSize, %rsp # for local variable

	movl $prompt, %edi # address of prompt text string
	movl $0, %eax # no floating point args.
	call printf # invoke printf function

	leaq anInt(%rbp), %rsi # place to store integer
	movl $scanFormat, %edi # address of scanf format string
	movl $0, %eax # no floating point args.
	call scanf # invoke scanf function

	movl anInt(%rbp), %edx # the integer
	movl anInt(%rbp), %esi # two copies
	movl $printFormat, %edi # address of printf text string
	movl $0, %eax # no floating point args.
	call printf # invoke printf function

	movl $0, %eax # return 0
	movq %rbp, %rsp # delete local variables
	popq %rbp # restore caller’s base pointer
	ret # back to calling function

	
