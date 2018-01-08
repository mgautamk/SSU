# averageInts
# Prompts user for 10 integers, stores them in an array, then
# displays their average.
# Mahesh Gautam 21 Nov 2014

# number of elements in the array
	.equ nInts,10
# Stack frame
	.equ rbxSave,total-8
	.equ total,index-4
	.equ index,intArray-8
	.equ intArray,-4*nInts
	.equ localSize,rbxSave
# Read only data
	.section .rodata
prompt:
	.string "Enter an integer: "
msg:
	.string "The average is: "
endl:
	.string "\n"
# Code
	.text
	.globl main
	.type main, @function
main:
	pushq %rbp # save caller frame pointer
	movq %rsp, %rbp # set our frame pointer
	addq $localSize, %rsp # local variables
	andq $-16, %rsp # 16-byte boundary
	movq %rbx, rbxSave(%rbp) # save reg for OS

	movq $0, index(%rbp) # index = 0
	leaq intArray(%rbp), %rbx # the array

# store user values in the array
StoreLup:
	cmpq $nInts, index(%rbp) # all filled?
	jae sum # yes, sum them

	movl $prompt, %edi # no, prompt user
	call writeStr

	movq index(%rbp), %rax # get index value
	leaq (%rbx,%rax,4), %rdi # place to store int
	call getInt

	incq index(%rbp) # index++
	jmp StoreLup # do rest of elements

sum:
	movq $0, index(%rbp) # restart at beginning
	movl $0, total(%rbp) # init total
sumLup:
	cmpl $nInts, index(%rbp) # all summed?
	jae display # yes, display total

	movq index(%rbp), %rax # get index value
	movl (%rbx,%rax,4), %eax # no, add current
	addl %eax, total(%rbp)

	incq index(%rbp) # index++
	jmp sumLup # do rest of elements

display:
	movl $msg, %edi # tell user about it
	call writeStr


	movl total(%rbp), %eax # compute the average
	movl $0, %edx # create 64-bit dividend
	cmpl $0, %eax # is it negative?
	jge pos # no
	movl $-1, %edx # sign extend dividend
pos:
	movl $nInts, %ebx # get divisor
	idivl %ebx # signed division

	movl %eax, %edi # and show the average
	call putInt

	movl $endl, %edi
	call writeStr

	movq rbxSave(%rbp), %rbx # restore reg
	movl $0, %eax # return 0 ;
	movq %rbp, %rsp # remove local vars
	popq %rbp # restore caller frame ptr
	ret # back to OS
	
