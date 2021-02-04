/* Author: Alfredo Mejia, Bryanth Fung
** Course: CS4348.004
**   Date: 3/13/2020
** Assign: Programming Project 2
** Descrp: This program will calculate a prefix sum of a given array inside a file. The program will calculate
**         the prefix sum using m number of threads specified by the user concurrent with a barrier. The program then
**         will ouput the prefix sum to a file specified by the user. Any invalid data such as arguments, files, or
**         data in the files will make the program terminate. For additional documentation refer to the README
**         file.
********************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include<thread>
#include<string.h>
#include<boost/thread.hpp>
#include<boost/thread/barrier.hpp>

using namespace std;

//Create shared array, barrier, and worker threads
boost::barrier* rendevousz;
int* sharedArray;
thread* workers;

//Error checks the opening of the files and the validity of the arguments in the command
// The arguments it takes in are user specified: size of array, input file name, outputfile name
// In addition it accepts ifstream and ofstream objects to be able to open the files specified
void errorCheck(int sizeOfArray, char *inputFileName, char *outputFileName, int numOfProcesses, ifstream& inputFile, ofstream& outputFile)
{
    // Open Files
	inputFile.open(inputFileName);
	outputFile.open(outputFileName);

    // If files fail to open exit program
	if(!inputFile.is_open() || !outputFile.is_open())
	{
		cout << "Error! File(s) failed to open. Must be valid file names" << endl;
		exit(-1);
	}

    // If size of array or number of processes invalid numbers exit program
	if(sizeOfArray <= 0 || numOfProcesses <= 0)
	{
		cout << "Error! Invalid Number(s) Input. Must be greater than zero." << endl;
		exit(-1);
	}

	return;

} // end errorcheck

//reads the input file whose file name is specified when the program execution command is done.
//It also error checks the inputs and if invalid input is in the file it displays error message then exits
//inputFile takes in a file from ifstream, sharedArray is the shared memory that is created before this function call,sizeOfArray is an int value passed as an argument, and diff is an int that calculated the difference on the inputs and processes
void readFile(ifstream& inputFile, int sizeOfArray, int diff)
{
	int counter = 0, placeHolder = 0;

	// While not the end of the file
	while (!inputFile.eof())
	{
		// Input the int from file
		if (inputFile >> placeHolder)
		{
			// Copy to shared Memory
			sharedArray[counter] = placeHolder;
			counter++;

			// If more ints than delcared
			if ((counter) > sizeOfArray)
			{
				cout << "Input File does not contain exactly " << sizeOfArray << " integers" << endl;
				exit(-1);
			}

		} // end if (input>>)

		// If reading failed exit program
		else if (!inputFile.eof())
		{
			cout << "Input Failed has invalid data" << endl;
			exit(-1);

		} // end else if

	} // end while

	// If number of ints is not what is declared exit program
	if (counter < sizeOfArray)
	{
		cout << "Input File does not contain exactly " << sizeOfArray << " integers" << endl;
		exit(-1);
	}

	// If there a difference between number of processes and size of array
	// Make up for it by filling the rest of shared memory with zeros
	if (diff != 0) {
		for (int i = sizeOfArray; i < sizeOfArray + diff; i++) {
			int fill = 0;
			sharedArray[i] = fill;
		}
	}

	return;

} // end readFile

//This reads the threads' calculated ID, its iterations ID, its size of the array, and the amount to skip
//On creation the thread will execute this fucntion to calculate its section and then it will wait for other threads to finish
// Once it finishes it will call itself recursively until the iterationID has reached its limit 
void calculation(int calculatedID, int iterationID, int sizeOfArray, int skipAmount)
{
    // Check if the function has executed enough iterations for calculation
	if(iterationID < ceil(log2(sizeOfArray)))
	{
        // Declare necessarily counters
		int counter = 0;
		int offset = (int)(pow(2, iterationID) + 0.5);

		//j is used to go through array
		for (int j = 0; j < sizeOfArray; j++)
		{
			//If the section of the array is for this specific process
			if (j >= calculatedID && counter < skipAmount)
			{
				counter++;
				//copy the element down as its already done for its iteration
				if (j < offset)
				{
					sharedArray[((iterationID + 1) * sizeOfArray) + j] = sharedArray[(iterationID * sizeOfArray) + j];
					continue;
				}

				//calculate the sums
				else
				{
					int temp1, temp2;
					temp1 = sharedArray[(iterationID * sizeOfArray) + j];
					temp2 = sharedArray[((iterationID * sizeOfArray) + j) - offset];
					temp1 = temp1 + temp2;
					sharedArray[((iterationID + 1) * sizeOfArray) + j] = temp1;
				}

			} // end if (j >= calculatedID....)

			else
				continue;

		} // end of for loop going through the array

        // wait for all threads to finish 
		rendevousz->wait();

        // Recursively call the function
		calculation(calculatedID, ++iterationID, sizeOfArray, skipAmount);
	}
}

//main driver of the program which executes the algorithm for prefix sum 
int main(int argc, char* argv[])
{
    //argument count check
    if(argc != 5)
    {
        cout << "Error! Incorrect Number of Arguments" << endl;
	    return -1;
    }

    // Convert arguments to ints
    int sizeOfArray = atoi(argv[1]);
    int numOfThreads = atoi(argv[4]);

    // Open files
	ifstream inputFile;
	ofstream outputFile;
	
    // Error check
	errorCheck(sizeOfArray, argv[2], argv[3], numOfThreads, inputFile, outputFile);

    // Calculate difference between processes and size of array
	int divisionOfArray = ceil(((double)sizeOfArray / numOfThreads));
	int diff = abs((divisionOfArray * numOfThreads) - sizeOfArray);

    // Recalculate the size of the array
	int fullSize = ((ceil(log2(sizeOfArray + diff)) + 1) * (sizeOfArray + diff));

    // Create array, threads, and barrier with appropriate sizes
	sharedArray = new int[fullSize];
	workers = new thread[numOfThreads];
	rendevousz = new boost::barrier(numOfThreads);
	
	// Read file
	readFile(inputFile, sizeOfArray, diff);

    // Update sizeOfArray
	sizeOfArray += diff;

    // Calculate skip amount and create array of calculated IDs 
	int skipAmount = sizeOfArray / numOfThreads;
	int *calculatedID = new int[numOfThreads];

    // Calculate calculated IDs for each thread
	for (int i = 0; i < numOfThreads; i++)
		calculatedID[i] = i * skipAmount;
	
    // Create worker threads
    // First parameter is the name of the function each thread has to execute
    // Next parameters are the parameters to the function
	for (int i = 0; i < numOfThreads; i++)
		workers[i] = thread(calculation, calculatedID[i], 0, sizeOfArray, skipAmount);
	
    // Wait for all worker threads to terminate
	for (int i = 0; i < numOfThreads; i++)
		workers[i].join();

    //Save results to output file
    for(int i = (ceil(log2(sizeOfArray))) * (sizeOfArray); i < ((ceil(log2(sizeOfArray)) + 1) * (sizeOfArray))-diff; i++)
        outputFile << sharedArray[i] << " ";

    return 0;

} // end main
