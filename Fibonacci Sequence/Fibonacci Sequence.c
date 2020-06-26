/* Author: Alfredo Mejia
 * Course: SE 3377.0W5
 * Date  : 12/8/19
 * Assgin: Assignment 4
 * Descrp: This program will perform two different functions via different threads. One of the functions will take a positive integer N, as the parameter and find the sum of these first N consecustive integers. The other function will also take a positive integer N, but  will calculate and store an array of integers following the fibonacci sequence of length N. In main, the program will first ask the user for a greater than zero integer before creating the threads. If the user enters a zero or lower, then an error message will appear and the user will have to insert another number again until the number is valid. Once a valid number is obtained, the threads will be created and a message indicating the creation of the 2 threads will appear. One of the thread will execute the sum of N integers, while the other thread will calcualte the fibonacci sequence. Once both threads are finished a message will appear indicating they are finished followed by main outputting the sum of the N and the output of the fibonacci sequence.
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global Varaibles to help keep track of the threads
int sum = 0;
int numThreads = 2;
long *fibSeq;

// Function that helps get the sum of the first N integers
void *getSum (void *N)
{
        // Convert N to a long to use as a variable
        long size = (long) N;
        int temp = 0, i;

        // Loop through, adding the consecutive integers to get the sum
        for(i = 1; i <= size; i++)
                temp += i;

        // Store in global variable
        sum = temp;

        // Print finished message
        printf("Thread 1 (sum of first N num) has finished...\n");

        // A thread has finished so subtract
         numThreads--;

        // Exit thread
        pthread_exit(NULL);

} // end getSum

// Function that stores fibonacci sequence
void *getFibSequence(void *N)
{
        // Convert N to a variable to use
        long size = (long) N;
        long *tempFib;

        // Create an array with sufficient space
        tempFib = (long*)calloc(size, sizeof(long));

        // If size is 1 then it's the base case
        if(size == 1)
                tempFib[0] = 0;

        // Otherwise
        else
        {
                // Set the first two base cases
                tempFib[0] = 0;
                tempFib[1] = 1;

                // Calculate the rest using fib(n) = fib(n-1) + fib(n-2)
                int i;
                for(i = 2; i < size; i++)
                        tempFib[i] = tempFib[i-1] + tempFib[i-2];

        } // end else

        // Store the address of the array to global variable
        fibSeq = tempFib;

        // Subtract
        printf("Thread 0 (fibonacci sequence) has finished...\n");

        // One less thread active so subtract
        numThreads--;

        // Exit thread
        pthread_exit(NULL);

} // end getFibSeq

// main
int main()
{
        // Variable for user input
        long size;

        do
        {
                // Print prompt
                printf("Enter a positive non-zero number to calculate the sum of the first N numbers and to calculate the fibonacci sequence containing N elements using two different threads: ");

                // Store user input
                scanf("%ld", &size);

                // If less than 1 then print error message
                if(size < 1)
                        printf("Error! Please read instructions and enter a valid number. \n");

        }while(size <= 0); // while user input is less or equal to zero then keep on asking

        // Two thread objects for two different threads
        pthread_t fibThread;
        pthread_t sumThread;

        // Print message and start a new thread with the getfibSeq function
        printf("Thread 0 (fibonacci sequence) is starting...\n");
        int returnFibT = pthread_create(&fibThread, NULL, getFibSequence, (void *)size);

        // Print message and start a new thread with the getSum function
        printf("Thread 1 (sum of first N num) is starting...\n");
        int returnSumT = pthread_create(&sumThread, NULL, getSum, (void *)size);

        // If either thread fails then print message and exit the program
        if(returnFibT || returnSumT)
        {
                printf("An error has occured in creating the threads. This program will now terminate \n");
                exit(-1);
        } // end if

        // Wait for the threads to finish so we can access the global variables
        while (numThreads > 0)
        {
        }

        // Print output. The only reason as to why I printed the first number by itself is
        // because I wanted the commas between numbers to look good so that was necessary
        printf("The first %ld number(s) in the Fibonacci sequence are: ", size);
        printf("%ld", fibSeq[0]);
        int i;

        for(i = 1; i < size; i++)
                printf(", %ld", fibSeq[i]);

        printf("\n");

        // Print the output of the results of the other function
        printf("The sum of the first %ld number(s) is: %ld \n", size, sum);
        // Free up the space allocated at first
        free(fibSeq);

        // Exit all threads
        pthread_exit(NULL);
} // end main
