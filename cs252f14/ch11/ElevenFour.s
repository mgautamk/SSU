# EcoString.s OR ElevenFour.s
# Prompts user to enter a string, then echoes it.
# Mahesh Gautam - Nov 7th 2014
# stack froame
	.equ theString,-256
	.equ localSize,-256
# read only data
	.data
usrprmpt:
	.string "Enter a text string:\n"
usrmsg:
	.string "You entered:\n"
newline:
	.string "\n"
#code
	.text
	.globl main
	.type main, @function
main:
	pushq %rbp # save caller base pointer
	movq %rsp, %rbp # establish our base pointer
	addq $localSize, %rsp # local vars.

	movl $usrprmpt, %edi # tell user what to do
	call writeStr

	leaq theString(%rbp), %rdi # place for user response
	call readLn

	movl $usrmsg, %edi # echo for user
	call writeStr
	leaq theString(%rbp), %rdi
	call writeStr

	movl $newline, %edi # some formatting for user
	call writeStr

	movl $0, %eax # return 0 ;
	movq %rbp, %rsp # delete local variables
	popq %rbp # restore caller base pointer
	ret
	
	
	
