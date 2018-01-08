# dec2sInt.s
# Converts string of numerals to decimal int, signed version
# Mahesh gautam
	
# Calling sequence
#	 rsi <- address of place to store the int
# 	 rdi <- address of string
# 	 call dec2sInt
#	 returns 0
	
# Stack frame
	.equ negFlag,-4
	.equ localSize,-16
# Code
	.text
	.globl dec2sInt
	.type dec2sInt, @function
dec2sInt:
	pushq %rbp # save caller frame ptr
	movq %rsp, %rbp # our stack frame
	addq $localSize, %rsp # space for local var
	
	movl $0, negFlag(%rbp) # assume false
	
	cmpb $'-', (%rdi) # minus sign?
	jne checkPlus # no, check for plus sign
	movl $1, negFlag(%rbp) # negFlag = true ;
	incq %rdi # skip minus sign
	jmp doIt # and do the conversion
checkPlus:
	cmpb $'+', (%rdi) # plus sign?
	jne doIt # no, ready for conversion
	incq %rdi # skip plus sign
doIt:
	call dec2uInt # arguments are correct
	              # absolute value now stored
	cmpl $0, negFlag(%rbp) # negative?
	je done # no, all done
	negl (%rsi) # change sign
done:
	movl $0, %eax # return 0
	movq %rbp, %rsp # delete local vars
	popq %rbp # restore caller frame ptr
	ret
