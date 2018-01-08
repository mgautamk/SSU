# writeStr.s
# Writes a C-style text string to the standard output (screen).
# Mahesh Gautam Nov 7th 2014

# Calling secquence
# rdi <- address of string to be written
# call writestr
# returns number of characters written

# Useful constant
	.equ STDOUT,1
# Stack frame, showing local variables and arguments
	.equ stringAddr,-16
	.equ count,-4
	.equ localSize,-16

	.text
	.globl writeStr
	.type writeStr, @function
writeStr:
	pushq %rbp # save base pointer
	movq %rsp, %rbp # new base pointer
	addq $localSize, %rsp # local vars. and arg.

	movq %rdi, stringAddr(%rbp) # save string pointer
	movl $0, count(%rbp) # count = 0 ;
writeLoop:
	movq stringAddr(%rbp), %rax # get current pointer
	cmpb $0, (%rax) # at end yet?
	je done # yes, all done

	movl $1, %edx # no, write one character
	movq %rax, %rsi # points to current char
	movl $STDOUT, %edi # on the screen
	call write
	incl count(%rbp) # count++ ;
	incl stringAddr(%rbp) # stringAddr++ ;
	jmp writeLoop # and check for end
done:
	movl count(%rbp), %eax # return count
	movq %rbp, %rsp # restore stack pointer
	popq %rbp # restore base pointer
	ret # back to caller
	
	
