# tenThirteen.s (echoN.s)
# Prompts user to enter a single character.
# The character is echoed. If it is a numeral, say N,
# it is echoed N+1 times
# Mahesh Gautam - 24 Oct 2014
# useful constant
	.equ STDIN,0
	.equ STDOUT,1
# stack frame
	.equ count,-8
	.equ response,-4
	.equ localSize,-16
#read only data
	.section .rodata
instruct:
	.ascii "A single numeral, N, is echoed N+1 times, other characters"
	.asciz "are echoed once. ’q’ ends program.\n\n"
prompt:
	.string "Enter a single character: "
msg:
	.string "You entered: "
bye:
	.string "End of program.\n"
newline:
	.byte '\n'
#code
	.text
	.globl main
	.type main, @function
main:
	pushq %rbp # save caller’s base pointer
	movq %rsp, %rbp # establish ours
	addq $localSize, %rsp # local vars

	movl $instruct, %esi # instruct user
instructLup:
	cmpb $0, (%esi) # end of string?
	je runLoop # yes, run program
	movl $1, %edx # no, one character
	movl $STDOUT, %edi
	call write
	incl %esi # next char
	jmp instructLup # check at top of loop
runLoop:
	movl $prompt, %esi # prompt user
promptLup:
	cmpb $0, (%esi) # end of string?
	je getChar # yes, get user input
	movl $1, %edx # no, one character
	movl $STDOUT, %edi
	call write
	incl %esi # next char
	jmp promptLup # check at top of loop

getChar:
	leaq response(%rbp), %rsi # place to put user input
	movl $2, %edx # include newline
	movl $STDIN, %edi
	call read

	movb response(%rbp), %al # get input character
	cmpb $'q', %al # if 'q’
	je allDone # end program
#otherwise, set up count loop
	movl $1, count(%rbp) # assume not numeral
	cmpb $'0', %al # check for numeral
	jb echoLoop
	cmpb $'9', %al
	ja echoLoop
	andl $0xf, %eax # numeral, convert to int
	incl %eax # echo N+1 times
	movl %eax, count(%rbp) # save counter
echoLoop:
	movl $msg, %esi # pointer to the string
msgLoop:
	cmpb $0, (%esi) # end of string?
	je doChar # yes, show character
	movl $1, %edx # no, one character
	movl $STDOUT, %edi
	call write
	incl %esi # next char
	jmp msgLoop # check at top of loop

doChar:
	movl $1, %edx # one character
	leaq response(%rbp), %rsi # in this mem location
	movl $STDOUT, %edi
	call write

	movl $1, %edx # and a newline
	movl $newline, %esi
	movl $STDOUT, %edi
	call write

	decl count(%rbp) # count--
	jne echoLoop # continue if more to do
	jmp runLoop # else get next character

allDone:
	movl $bye, %esi # ending message
doneLup:
	cmpb $0, (%esi) # end of string?
	je cleanUp # yes, get user input
	movl $1, %edx # no, one character
	movl $STDOUT, %edi
	call write
	incl %esi # next char
	jmp doneLup # check at top of loop

cleanUp:
	movl $0, %eax # return 0 ;
	movq %rbp, %rsp # delete local vars.
	popq %rbp # restore caller’s base pointer
	ret # return to caller
	








	
