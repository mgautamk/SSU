# sInt2dec.s
# Converts signed int to corresponding signed decimal string
# Mahesh gautam, Nov 21 2014
	
# Calling sequence
# 	esi <- value of the int
# 	rdi <- address of string
# 	call sInt2dec
# 	returns zero
# Code
	.section .rodata
ten: .long 10
	
	.text
	.globl sInt2dec
	.type sInt2dec, @function
sInt2dec:
	pushq %rbp # save callers frame ptr
	movq %rsp, %rbp # our stack frame
	
	cmpl $0, %esi # >= 0?
	jge positive # yes, just convert it
	movb $’-’, (%rdi) # store minus sign
	incq %rdi # and move the pointer
	negl %esi # negate the number
positive:
	call uInt2dec # arguments are correct
	
	movl $0, %eax # return 0
	movq %rbp, %rsp # delete local vars.
	popq %rbp # restore caller frame ptr
	ret
