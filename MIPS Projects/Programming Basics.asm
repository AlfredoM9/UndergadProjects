# Author: Alfredo Mejia
# Course: SE 3340.502
# Descrp: This program will ask for the user's name and then save it.
#	  It will then ask for three integers between the numbers 1 - 100.
#	  The program will then calculate the output based on given equations.
#	  Finally, the program will output the user's name along with the calculated
#	  output.
######################################################################################################################################################

		.data
inputA:		.word		0		
inputB:		.word		0	
inputC:		.word		0
outputA:	.word		0
outputB:	.word		0
outputC:	.word		0
name:		.space		20
promptN:	.asciiz		"Please enter your name: "
promptI:	.asciiz		"Please enter an integer between 1-100: "
promptR:	.asciiz		"your answers are: "

	.text
main:
	# Prompt for name
	li	$v0, 4
	la	$a0, promptN
	syscall
	
	# Save name
	li	$v0, 8
	la	$a0, name
	li	$a1, 20
	syscall
	
	# Prompt for integer A
	li	$v0, 4
	la	$a0, promptI
	syscall
	
	# Save integer A
	li	$v0, 5
	syscall
	sw	$v0, inputA
	
	# Prompt for integer B
	li	$v0, 4
	la	$a0, promptI
	syscall
	
	# Save integer B
	li	$v0, 5
	syscall
	sw	$v0, inputB
	
	# Prompt for integer C
	li	$v0, 4
	la	$a0, promptI
	syscall
	
	# Save integer C
	li	$v0, 5
	syscall
	sw	$v0, inputC
	
	# Store words into registers
	lw	$t0, inputA
	lw	$t1, inputB
	lw	$t2, inputC
	
	# Calculate ans1 = 2a - b + 9
	mul	$t3, $t0, 2
	sub	$t3, $t3, $t1
	addi	$t3, $t3, 9
	
	# Store ans1
	sw	$t3, outputA
	
	# Calculate ans2 = c - b + (a-5)
	add	$t3, $t0, -5
	sub	$t4, $t2, $t1
	add	$t3, $t3, $t4
	
	# Store ans2
	sw	$t3, outputB
	
	# Calculate ans3 = (a -3) + (b + 4) - (c + 7)
	add	$t3, $t0, -3
	addi	$t4, $t1, 4
	addi	$t5, $t2, 7
	add	$t3, $t3, $t4
	sub	$t3, $t3, $t5
	
	# Store ans3
	sw	$t3, outputC
	
	# Store results into registers
	lw	$t0, outputA
	lw	$t1, outputB
	lw	$t2, outputC
	
	# Display Name
	li	$v0, 4
	la	$a0, name
	syscall 
	
	# Display Prompt
	li	$v0, 4
	la	$a0, promptR
	syscall
	
	# Display Result 1
	li	$v0, 1
	move	$a0, $t0
	syscall
	
	# Display Space
	li	$v0, 11
 	li	$a0, 32
	syscall
	
	# Display Result 2
	li	$v0, 1
	move	$a0, $t1
	syscall
	
	# Display Space
	li	$v0, 11
	li	$a0, 32
	syscall
	
	# Display Result 3
	li	$v0, 1
	move	$a0, $t2
	syscall
	
	# Syscall to exit program
	li $v0, 10
	syscall


###########################################################################################################################################

# Sample Run 1:
#	Please enter your name: Alfredo
#	Please enter an integer between 1-100: 99
#	Please enter an integer between 1-100: 99
#	Please enter an integer between 1-100: 99
#	Alfredo
#	your answers are: 108 94 93

# Sample Run 2:
#	Please enter your name: Alfredo
#	Please enter an integer between 1-100: 56
#	Please enter an integer between 1-100: 87
#	Please enter an integer between 1-100: 23
#	Alfredo
#	your answers are: 34 -13 114

#Sample Run 3:
#	Please enter your name: Alfredo
#	Please enter an integer between 1-100: 98
#	Please enter an integer between 1-100: 76
#	Please enter an integer between 1-100: 54
#	Alfredo
#	your answers are: 129 71 114

#Sample Run 4:
#	Please enter your name: Alfredo
#	Please enter an integer between 1-100: 12
#	Please enter an integer between 1-100: 34
#	Please enter an integer between 1-100: 56
#	Alfredo
#	your answers are: -1 29 -16