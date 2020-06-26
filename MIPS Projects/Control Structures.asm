# Author: Alfredo Mejia
# Date  : 9/22/19
# Course: SE 3340.502
# Descrp: This program will get a string from the user and calculate
#	  the amount of words and characters the string contains. It
#	  will then save the results into memory and repeat until the 
#	  user exits.
######################################################################################################################################################

		
				
		.data
prompt: 	.asciiz "Enter text here: "
len: 		.word 100
str: 		.space 100 	# maximum of 100 characters
charCount: 	.word 0
wordCount: 	.word 0
wordPrompt: 	.asciiz " total words "
charPrompt: 	.asciiz " total characters \n"
exitPrompt: 	.asciiz "You have exited the program"
progEnd: 	.asciiz "Message: "


		.text
main:
mainLoop:
		#show a dialog box to user to get string input
		la $a0, prompt
		la $a1, str
		lw $a2, len
		li $v0, 54
		syscall
		#check status in a1
		beq $a1, -2, exit 	#cancel choosen
		beq $a1, -3, exit 	#blank input and ok choosen
		#we can process now, call function count by passing address and length in a0 and a1
		la $a0, str
		lw $a1, len
		jal count
		#we receive count of characters and words in v0 and v1.Then we store in memory
		sw $v0, charCount
		sw $v1, wordCount
		#display the string and counts
		la $a0, str 
		li $v0, 4
		syscall
		#display word count
		lw $a0, wordCount
		li $v0, 1
		syscall
		la $a0, wordPrompt
		li $v0, 4
		syscall
		#display char count
		lw $a0, charCount
		li $v0, 1
		syscall
		la $a0, charPrompt
		li $v0, 4
		syscall
		b mainLoop
exit:
		#display exit message
		la $a0, progEnd
		la $a1, exitPrompt
		li $v0, 59
		syscall
		#exit
		li $v0, 10
		syscall
###################################################################################################
#function count receives address of string in a0 and length in a1
#returns character count in v0 and word count in v1
####################################################################################################
count:

		#save s0 on stack by making space for 4 bytes
		addi $sp, $sp, -4
		sw $s0, 0($sp) 		#save value of s0 on stack
		move $s0, $a0
		li $t1, 0 		#char count
		li $t2, 1 		#word count
countLoop:
		lb $t3, ($s0)		#load byte
		beq $t3, '\n', exitLoop #go to exitLoop on seeing newline or null terminator
		beq $t3, '\0', exitLoop
		add $t1, $t1, 1 	#increment char count
		beq $t3, ' ', IncrWord
		b NextLoc
IncrWord:
		addi $t2, $t2, 1
NextLoc:
		addi $s0, $s0, 1
		b countLoop
exitLoop:
		#pop back s0 from stack
		lw $s0, 0($sp)
		add $sp, $sp, 4
		#return values in v0 and v1
		move $v0, $t1
		move $v1, $t2
		jr $ra