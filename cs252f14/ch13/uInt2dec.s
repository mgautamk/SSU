# uInt2dec.s
# Converts unsigned int to corresponding unsigned decimal string
# Calling sequence
# esi <- value of the int
# rdi <- address of string
# call uInt2dec
# returns zero
# Stack frame
	.equ array,-12
	.equ localSize,-16
# Read only data
	.section .rodata

ten: 	.long 10
# Code
	.text
	.globl uInt2dec
	.type uInt2dec, @function

uInt2dec:
	pushq %rbp # save callers frame ptr
	movq %rsp, %rbp # our stack frame
	addq $localSize, %rsp # local vars.
	leaq array(%rbp), %rcx # ptr to local array
	movb $0, (%rcx) # null byte
	movl %esi, %eax # the number to conv.
charLup:
	movl $0, %edx # high-order = 0
	divl ten # divide by ten
	orb $0x30, %dl # convert to ascii
	incq %rcx # next location
	movb %dl, (%rcx) # store the character
	cmpl $0, %eax # anything left?
	jne charLup # yes, do it

copyLup:
	cmpb $0, (%rcx) # NUL char?
	je allDone # yes, copy it
	movb (%rcx), %dl # get achar
	movb %dl, (%rdi) # store it
	incq %rdi # move pointers
	decq %rcx
	jmp copyLup # and check again

allDone:
	movb (%rcx), %dl # get NUL char
	movb %dl, (%rdi) # and store it
	movl $0, %eax # return count;
	movq %rbp, %rsp # delete local vars.
	popq %rbp # restore caller frame ptr
ret
