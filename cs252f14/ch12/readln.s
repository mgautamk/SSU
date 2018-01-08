#readLn.s
# Reads a line (through the ’\n’ character from standard input. Deletes
# the ’\n’ and creates a C-style text string.
# Mahesh Gautam - Nov 7th 2014

#Calling secquence
# rdi <- address of place to store string
# call readLn
# returns number of characters read (not including NUL)

# Useful constant
	.equ STDIN,0
# Stack frame, showing local variables and arguments
	.equ stringAddr,-16
	.equ count,-4
	.equ localSize,-16

	.text
	.globl readLn
	.type readLn, @function
readLn:
	pushq %rbp # save base pointer
	movq %rsp, %rbp # new base pointer
	addq $localSize, %rsp # local vars. and arg.

	movq %rdi, stringAddr(%rbp) # save string pointer
	movl $0, count(%rbp) # count = 0 ;

	movl $1, %edx # read one character
	movq stringAddr(%rbp), %rsi # into storage area
	movl $STDIN, %edi # from keyboard
	call read
readLoop:
	movq stringAddr(%rbp), %rax # get pointer
	cmpb $'\n', (%rax) # return key?
	je endOfString # yes, mark end of string
	incq stringAddr(%rbp) # no, move pointer to next byte
	incl count(%rbp) # count++ ;
	movl $1, %edx # get another character
	movq stringAddr(%rbp), %rsi # into storage area
	movl $STDIN, %edi # from keyboard
	call read
	jmp readLoop # and look at it

endOfString:
	movq stringAddr(%rbp), %rax # current pointer
	movb $0, (%rax) # mark end of string

	movl count(%rbp), %eax # return count ;
	movq %rbp, %rsp # restore stack pointer
	popq %rbp # restore base pointer
	ret # back to OS
	
