# EightSeven.s
# Assigns values to four chars and four ints and prints them.
# Mahesh Gautam - 10 Oct 2014

# Stack frame
	.equ a,-1
	.equ b,-2
	.equ c,-3
	.equ d,-4
	.equ w,-8
	.equ x,-12
	.equ y,-16
	.equ z,-20
	.equ arg7,0
	.equ arg8,8
	.equ arg9,16
	.equ localSize,-48
# Read only data
	.section .rodata
format:	
	.string "The values are %c, %i, %c, %i, %c, %i, %c, and %i\n"
#Code
	.text
	.globl main
	.type main, @function
main:
	pushq %rbp # save calling function’s base pointer
	movq %rsp, %rbp # establish our base pointer
	addq $localSize, %rsp # allocate memory for local variables
	movb $'A', a(%rbp) # initialize chars
	movb $'B', b(%rbp)
	movb $'C', c(%rbp)
	movb $'D', d(%rbp)
	movl $12, w(%rbp) # and ints
	movl $34, x(%rbp)
	movl $45, y(%rbp)
	movl $67, z(%rbp)

	movslq z(%rbp), %rax # load z
	movq %rax, arg9(%rsp) # and place on stack
	movzbq d(%rbp), %rax # load d
	movq %rax, arg8(%rsp) # place on stack
	movslq y(%rbp), %rax # load y
	movq %rax, arg7(%rsp) # place on stack
	movl y(%rbp), %r9d
	movzbl c(%rbp), %r9d # load args into regs.
	movl x(%rbp), %r8d
	movzbl b(%rbp), %ecx
	movl w(%rbp), %edx
	movzbl a(%rbp), %esi
	movl $format, %edi # format string
	movl $0, %eax # no floating point values
	call printf

	movq %rbp, %rsp # delete local variables
	popq %rbp # restore calling function’s base pointer
	movl $0, %eax # return 0
	ret
	
