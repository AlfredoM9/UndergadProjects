# Author: Alfredo Mejia										#
# Date  : 10/12/19										#
# Course: SE 3340.502										#
# Descrp: This program will ask the user for its name, weight (whole number),			#
#	  and height (inches). It will then save the input as a string, and 			#
#	  integers. The program will then do the necessary arithmetic operations		#
#	  on the integers before calculating the BMI. It will then convert these		#
#	  integers into floats and then divide weight/height to calculate the BMI		#
#	  to then be saved as a float. It will then display the name of the user and		#
#	  its BMI. Finally, the program will check the user's BMI to determine if the		#
#	  user is underweight, has normal weight, overweight, or is obese. After 		#
#	  determining the program will print out a message what the program has determined	#
#	  regarding the user's weight.								#
#################################################################################################
		
		.data
# Variables for input and calculation
height:		.word	0
weight:		.word	0
bmi:		.float	0
name:		.space	20

# Varaibles to hold BMI categories
underWgt:	.float	18.5
normalWgt:	.float	25
overWgt:	.float	30

# Variables to hold messages
prompt:		.asciiz	"What is your name? "
promptHgt:	.asciiz "Please enter your height in inches: "
promptWgt:	.asciiz "Now eneter your weight in pounds (round to a whole number): "
promptBMI:	.asciiz "your bmi is: "
promptUN:	.asciiz	"This is considered underweight."
promptNM:	.asciiz "This is a normal weight."
promptOW:	.asciiz "This is considered overweight."
promptOB:	.asciiz "This is considered obese."

	.text
main:
	# Prompt for name
	li	$v0, 4
	la	$a0, prompt
	syscall
	
	# Save name
	li	$v0, 8
	la	$a0, name
	li	$a1, 20
	syscall
	
	# Prompt for height
	li	$v0, 4
	la	$a0, promptHgt
	syscall
	
	# Save height
	li	$v0, 5
	syscall
	sw	$v0, height
	
	# Prompt for weight
	li	$v0, 4
	la	$a0, promptWgt
	syscall
	
	# Save weight
	li	$v0, 5
	syscall
	sw	$v0, weight
	
	# Load variables into registers
	lw	$t1, height
	lw	$t2, weight
	
	# Multiply weight and height with necessary numbers
	mul	$t1, $t1, $t1	# height
	mul	$t2, $t2, 703	# weight
	
	# Convert height to float
	mtc1	$t1, $f1
	cvt.s.w $f1, $f1
	
	# Convert weight to float
	mtc1	$t2, $f2
	cvt.s.w $f2, $f2
	
	# Divide weight over height to get BMI
	div.s	$f3, $f2, $f1
	
	# Save BMI
	swc1	$f3, bmi
	
	# Display name
	li	$v0, 4
	la	$a0, name
	syscall
	
	# Display message about BMI
	li	$v0, 4
	la	$a0, promptBMI
	syscall
	
	# Display actual BMI
	li	$v0, 2
	l.s	$f12, bmi
	syscall
	
	# Load floats to registers to perform conditional branches
	l.s	$f1, bmi
	l.s	$f2, underWgt
	l.s	$f3, normalWgt
	l.s	$f4, overWgt
	
	# Display newline character
	li	$v0, 11
	la	$a0, 10
	syscall
	
	# Compare the bmi to what is considered underweight
	c.lt.s	$f1, $f2
	
	# If true, jump to underweight prompt
	bc1t unWgtPrompt
	
	# Compare the bmi to what is considered normal weight
	c.lt.s	$f1, $f3
	
	# If true, jump to normal weight prompt
	bc1t nmWgtPrompt
	
	# Compare the bmi to what is considered overweight
	c.lt.s	$f1, $f4
	
	# If true, jump to overweight prompt
	bc1t ovWghtPrompt
	
	# If bmi exceeds what is considered overweight then print obese prompt
	li	$v0, 4
	la	$a0, promptOB
	syscall
	j exit
	
unWgtPrompt:
	# Display underweight message and jump to exit
	li	$v0, 4
	la	$a0, promptUN
	syscall
	j exit
	
nmWgtPrompt: 
	# Display normal weight message and jump to exit
	li	$v0, 4
	la	$a0, promptNM
	syscall
	j exit
	
ovWghtPrompt: 
	# Display overweight message and jump to exit
	li	$v0, 4
	la	$a0, promptOW
	syscall
	j exit
	
exit:
	# Eventually it will jump to exit and it will exit the program
	li	$v0, 10
	syscall
	
	
