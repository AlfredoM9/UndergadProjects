		.data
arry:		.align  2
		.space	80
buffer:		.space	80
fileName:	.asciiz	"input.txt"

	.text
main:
la	$a0, fileName			#Pass file name
la	$a1, buffer			#Pass buffer address
jal	readFile			#Call function to read file
add	$s0, $v0, $zero			#Save the number of bytes read
ble	$s0, $zero, exit		#If numOfBytes <= 0 then exit

la	$a0, arry			#Pass the address of the array
li	$a1, 20				#Pass the limit of words for the array
la	$a2, buffer			#Pass the address of the buffer
jal	toArray				#Call the toArray function

add	$s7, $v0, $zero			#Save the number of words to a secure register

la	$a0, arry			#Pass the array
add	$a1, $s7, $zero			#Pass the number of words in the array
jal printArry				#Call the printing function

la	$a0, arry			#Pass the array
add	$a1, $s7, $zero			#Pass the number of words in the array
jal selectionSort

la	$a0, arry			#Pass the array
add	$a1, $s7, $zero			#Pass the number of words in the array
jal printArry

jal exit

################################################################################################
toArray:
add	$t0, $zero, $zero		#Initialize the amount of words in the array
addi	$t1, $zero, 48			#Initialize to the ascii code of lowest digit
addi	$t2, $zero, 57			#Initialize to the ascii code of largest digit
#add	$t3, $zero, $zero		#Control variable for the loop
#addi	$t4, $zero, 80			#Hold the limit of bytes for the loop (iterations)
addi	$t5, $zero, 10			#Initialize to the ascii code of a new line character
add	$t7, $zero, $zero		#This will hold the number read then passed to the array
add	$s0, $zero, $zero		#Treat it as a boolean variable to multiply


loop:
lb	$t6, ($a2)			#Load a byte
beqz	$t6, end
#bge	$t3, $t4, end			#Check if we are within the bytes limit

blt	$t6, $t1, goNextLoop		#If not a number go to goNextLoop
bgt	$t6, $t2, goNextLoop		#If not a number go to goNextLoop
subi	$t6, $t6, 48			#Otherwise subtract 48 to convert it to an int

mul	$s0, $s0, $t5			#If there was a previous digit then get ready to multiply with 10
mul	$t7, $t7, $s0			#If there was a previous digit then multiply with 10
add	$t7, $t7, $t6 			#Then add the current digit to it

addi	$s0, $zero, 1			#Set it to true (1) because we still haven't encountered an endline
addi	$a2, $a2, 1			#Go to next byte
#addi	$t3, $t3, 1			#Increment control variable

j loop					#Go to next iteration

goNextLoop:		
add	$s0, $zero, $zero		#We have encountered an endline so the boolean variable becomes false so we won't multiply with 10
beq	$t6, $t5, nextWord		#If it is a newline character then save the set of integers as word in the array otherwise just continue skipping the characters (this is so the array won't be filled with zeros)
#addi	$t3, $t3, 1			#Increment the control variable
addi	$a2, $a2, 1			#Increment the buffer address

j loop					#Go to next iteration


nextWord:
bge	$t0, $a1, end			#If there is enough space in the array for another word otherwise exit
sw	$t7, ($a0)			#Save the set of integers as a word in the array
addi	$a0, $a0, 4 			#Increment the address of the array by 4 bytes (1 word)
add	$t7, $zero, $zero		#Initialize the variable that holds the number back to zero
#addi	$t3, $t3, 1			#Increment the control variable
addi	$a2, $a2, 1			#Increment the buffer address
addi	$t0, $t0, 1			#Increment the number of words in the array

j loop					#Go to next iteration

end:
add	$v0, $t0, $zero			#Return the number of words in the array (for later use)
jr	$ra				#Return to the call

############################################################################################################
printArry:
add	$t0, $a1, $zero			#Store the number of words in the array
add	$t2, $a0, $zero			#Store the address of the array

printLoop:
blez	$t0, endPrinting		#While there is some words in the array left: continue, otherwise exit
lw	$t1, ($t2)			#Load the first word from the array
li	$v0, 1				#Print an integer
add	$a0, $t1, $zero			#Pass the word
syscall					#Print the word

li	$v0, 11				#Print a character
li	$a0, 32				#Pass the ascii value for a space
syscall					#Print a space

addi	$t2, $t2, 4			#Increment address of array to the next word
subi	$t0, $t0, 1			#Subtract the amount of words left to read

j printLoop				#Go to next iteration

endPrinting:
li	$v0, 11				#Print a character
li	$a0, 10				#Pass the ascii value for a space
syscall	
jr	$ra				#Return to the call
#############################################################################################
selectionSort:
sub	$a3, $a1, 1			#Initialize the words you need to check (size - 1)
add	$t0, $zero, $zero		#Control variable (i = 0)
sortLoop:
beq	$t0, $a3, exitSort		#If the control variable is greater than (size - 1) then exit
add	$t1, $t0, $zero			#Otherwise initialize the min pos for later use (min = i)

addi	$t2, $t0, 1			#Initialize the other control variable for the inner loop (i = j + 1)
nestedLoop:
beq	$t2, $a1, continueLoop		#If we checked all the words already then exit inner loop ( j < size )
sll	$t3, $t1, 2			#Otherwise multiply min by 4 to get correct position element
add	$t3, $t3, $a0			#Add to get correct address
lw	$t3, ($t3)			#Load the word

sll	$t4, $t2, 2			#Multiply by 4 to get correct position element
add	$t4, $t4, $a0			#
lw	$t4, ($t4)

blt	$t4, $t3, adjustMin

addi	$t2, $t2, 1
j nestedLoop

adjustMin:
add	$t1, $t2, $zero
addi	$t2, $t2, 1
j nestedLoop

continueLoop:
sll	$t3, $t0, 2
add	$t3, $t3, $a0
lw	$t4, ($t3)

sll	$t5, $t1, 2
add	$t5, $t5, $a0
lw	$t6, ($t5)

sw	$t4, ($t5)
sw	$t6, ($t3)

addi	$t0, $t0, 1

j sortLoop

exitSort:
jr $ra


#############################################################################################
readFile:
add	$t0, $a0, $zero			#Store file name separately
add	$t1, $a1, $zero			#Store buffer separately

li	$v0, 13				#Open file
li	$a1, 0				#Flag
li	$a2, 0				#Mode
syscall

add	$t3, $v0, $zero			#Store file descriptor

li	$v0, 14				#Read file
add	$a0, $t3, $zero			#Pass the file descriptor
add	$a1, $t1, $zero			#Pass the buffer address
li	$a2, 80				#Pass the maximum number of characters
syscall

add	$t4, $v0, $zero			#Store the number of bytes read

li	$v0, 16				#Close file
add	$a0, $t3, $zero			#Pass the file descriptor
syscall

add	$v0, $t3, $zero			#Return the number of bytes read
jr	$ra				#Return to the next instruction following the call

###########################################################################################################
exit:
li	$v0, 10				#exit program
syscall
