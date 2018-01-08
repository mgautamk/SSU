# dec2uInt.s
# Converts string of numerals to decimal unsigned int
# Mahesh Gautam - 21 Nov 2014

# Calling sequence
#	rsi <- address of place to store the int
#	rdi <- address of string
#	call dec2uInt
#	returns 0
# Code
	.text
	.globl dec2uInt
	.type dec2uInt, @function
dec2uInt:
	pushq %rbp # save caller frame ptr
	movq %rsp, %rbp # our stack frame
	
	movl $0, %eax # subtotal = 0
loop:
	movb (%rdi), %cl # get current character
	cmpb $0, %cl # end of string?
	je done # yes, all done
	andl $0xf, %ecx # no, convert char to int
	imull $10, %eax # 10 x subtotal
	addl %ecx, %eax # add current int to subtotal
	incq %rdi # move pointer
	jmp loop # and check again
done:
	movl %eax, (%rsi) # store the int
	
	movl $0, %eax # return 0
	movq %rbp, %rsp # delete local vars
	popq %rbp # restore caller frame ptr
	ret
