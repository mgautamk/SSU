# TenEleven.s (inchars.s)
# Prompts user to enter a text string, then changes each
# character to the next higher one.
# Mahesh Gautam Oct 24th- 2014
# useful constants
	.equ STDIN,0
	.equ STDOUT,1
	.equ SPACE,' ' # lowest printable character
	.equ SQUIGGLE,'~' # highest printable character
# stack frame
	.equ theString, -256
	.equ localSize, -256
# read only data
	.section .rodata
prompt:
	.string "Enter a string of characters: "
msg:
	.string "Incrementing each character: "
newline:
	.byte '\n'
# code
	.text
	.globl main
	.type main, @function
main:
	pushq %rbp # save caller’s base pointer
	movq %rsp, %rbp # establish ours
	addq $localSize, %rsp # local vars.

	movl $prompt, %esi # prompt user
promptLup:
	cmpb $0, (%esi) # end of string?
	je getString # yes, get user input
	movl $1, %edx # no, one character
	movl $STDOUT, %edi
	call write
	incl %esi # next char
	jmp promptLup # check at top of loop

getString:
	leaq theString(%rbp), %rsi # place to put user input
	movl $1, %edx # one character
	movl $STDIN, %edi
	call read
readLup:
	cmpb $'\n', (%rsi) # end of input?
	je incChars # yes, process the string
	incq %rsi # next char
	movl $1, %edx # one character
	movl $STDIN, %edi
	call read
	jmp readLup # check at top of loop

incChars:
	movb $0, (%rsi) # null character for C string
	leaq theString(%rbp), %rsi # pointer to the string
incLoop:
	cmpb $0, (%rsi) # end of string?
	je doDisplay # yes, display the results
	incb (%rsi) # change character
	cmpb $SQUIGGLE, (%rsi) # did we go too far?
	jbe okay # no
	movb $SPACE, (%rsi) # yes, wrap to beginning
okay:
	incq %rsi # next char
	jmp incLoop # check at top of loop
doDisplay:
	movl $msg, %esi # print message for user
dispLoop:
	cmpb $0, (%esi) # end of string?
	je showString # yes, show results
	movl $1, %edx # no, one character
	movl $STDOUT, %edi
	call write
	incl %esi # next char
	jmp dispLoop # check at top of loop

showString:
	leaq theString(%rbp), %rsi # pointer to the string
showLoop:
	cmpb $0, (%rsi) # end of string?
	je allDone # yes, get user input
	movl $1, %edx # no, one character
	movl $STDOUT, %edi
	call write
	incq %rsi # next char
	jmp showLoop # check at top of loop

allDone:
	movl $1, %edx # do a newline for user
	movl $newline, %esi
	movl $STDOUT, %edi
	call write

	movl $0, %eax # return 0 ;
	movq %rbp, %rsp # delete local vars.
	popq %rbp # restore caller’s base pointer
	ret # return to caller
	
