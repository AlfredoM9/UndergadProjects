# Descriptions: 

### Programming Basics:
Created a simple MIPS program that uses the registers for three input values and three output values. In addition, a variable is used to hold the user’s name and three variables are used to hold messages. The program asks the user for its name which is saved to memory and for three integers. Then simple calculations are done on the three input integers which are then displayed to the user.

### Control Structures:
Created a MIPS program that uses system calls to get an input string from the user and the program counts the amount of words and characters in the words. This data is then returned from a function in specified registers. The results are outputted to the user and repeated until the user enters a blank string or cancels. The stack registers are used to keep track of the data. Finally, another system call is used to say goodbye before the program ends.

### BMI Calculator:
Created a MIPS program that calculates the BMI of the user that inputs its name, height, and weight. The program then stores the data into registers, does calculations in the registers, and stores the BMI into another register. The program then outputs the BMI to the user along with his/her name.

### FP Operations:
Created a MIPS program that reads an input file into a buffer in memory. The string “numbers” are extracted from the file and converted into integers. The integers are then stored in an array. The array is then printed to the console. The array is then sorted using selection sort and followed by another print to the console. Finally, the program calculates the mean, median, and standard deviation followed by another print to the console. 

### Overall:
Created a Java solution using semaphores to the unisex bathroom problem in which the user specifies the number of toilets available in a restroom. The problem is that men can enter if toilets are available and same goes for women, but one gender cannot enter if the opposite gender is in the restroom. The solution was done using threads and semaphores. The solution is also deadlock free so the threads should concurrently be doing work dependent on the semaphore.  