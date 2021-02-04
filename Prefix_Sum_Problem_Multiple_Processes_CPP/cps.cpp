/* Author: Alfredo Mejia, Bryanth Fung
** Course: CS4348.004
**   Date: 2/28/2020
** Assign: Programming Project 1
** Descrp: This program will calculate a prefix sum of a given array inside a file. The program will calculate
**         the prefix sum using signals and m number of processes specified by the user. The program will then
**         ouput the prefix sum to a file specified by the user. Any invalid data such as arguments, files, or
**         data in the files will make the program terminate. For additional documentation refer to the README
**         file.
********************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/mman.h>

using namespace std;

// Global variables used to track where the signals should go
int mainOrigin = 0;
int childID =-1;

// Function used to signal the parent that child is ready
void alertParent(int sig)
{
    if(mainOrigin != getppid())
        kill(getppid(), SIGUSR1);

} // end alertParent

// Function used to signal the child that parent is ready
void alertChild(int sig)
{
    if(childID != 0)
        kill(childID, SIGUSR2);
        
} // end alertChild

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
void readFile (ifstream& inputFile, void* sharedArray, int sizeOfArray,int diff)
{
	int counter = 0, placeHolder = 0;

    // While not the end of the file
	while(!inputFile.eof())
	{
        // Input the int from file
		if(inputFile >> placeHolder)
		{
            // Copy to shared Memory
			memcpy(sharedArray + (__SIZEOF_INT__*counter), &placeHolder, __SIZEOF_INT__);
			counter++;

            // If more ints than delcared
			if((counter) > sizeOfArray)
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
	if(counter < sizeOfArray)
	{
		cout << "Input File does not contain exactly " << sizeOfArray << " integers" << endl;
		exit(-1);
	}

    // If there a difference between number of processes and size of array
    // Make up for it by filling the rest of shared memory with zeros
    if(diff!=0){
        for(int i=sizeOfArray;i<sizeOfArray+diff;i++){
            int fill=0;
            memcpy(sharedArray+(__SIZEOF_INT__*i),&fill,__SIZEOF_INT__);
        }
    }

	return;	

} // end readFile

//main driver of the program which executes the algorithm for prefix sum 
int main(int argc, char* argv[])
{
    //argument count check
    if(argc != 5)
    {
        cout << "Error! Incorrect Number of Arguments" << endl;
	    return -1;
    }

    // Set up signals
    signal(SIGUSR1, alertParent);
    signal(SIGUSR2, alertChild);
    
    // Convert arguments to ints
    int sizeOfArray = atoi(argv[1]);
    int numOfProcesses = atoi(argv[4]);

    // Open files
	ifstream inputFile;
	ofstream outputFile;
	
    // Error check
	errorCheck(sizeOfArray, argv[2], argv[3], numOfProcesses, inputFile, outputFile);

    // Calculate difference between processes and size of array
    int divisionOfArray=ceil(((double)sizeOfArray/numOfProcesses));
    int diff=abs((divisionOfArray*numOfProcesses)-sizeOfArray);

    // Create shared memory segment
    void *sharedArray = mmap(NULL, __SIZEOF_INT__ * ((ceil(log2(sizeOfArray + diff)) + 1 ) * (sizeOfArray + diff)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Read file
    readFile(inputFile, sharedArray, sizeOfArray,diff);

    // Increase array to make up the difference b/w processes and size of array
    sizeOfArray += diff;
    
    // Create variables used to calculate and track processes
    int skipAmount = sizeOfArray/numOfProcesses;
    int pid = 0;
    int calculatedID = 0;
    mainOrigin = getppid();

   
    //Creates the children and sets the offsets 
    for(int i = 1; i < numOfProcesses; i++)
    {
        if(pid == 0)
        {
            pid = fork();
            childID = pid;
            if(pid > 0)
                break;   // If parent break
            mainOrigin = -1;
            calculatedID = i * skipAmount;
        }

    } // end for loop that create processes

    //i stands for the numbers of iteration needed
    for(int i = 0; i <  ceil(log2(sizeOfArray)); i++)
    {
        int counter = 0;
        int offset = (int)(pow(2, i) + 0.5); // Calculate offset

        //j is used to go through array
        for(int j = 0; j < sizeOfArray; j++)
        {
            //If the section of the array is for this specific process
            if(j >= calculatedID && counter < skipAmount)
            {
                counter++;
                //copy the element down as its already done for its iteration
                if(j < offset)
			    {
				    memcpy(sharedArray + (__SIZEOF_INT__ * (((i + 1) * sizeOfArray) + j)), sharedArray + (__SIZEOF_INT__ * ((i * sizeOfArray) + j)), __SIZEOF_INT__);
				    continue;
			    }
                //calculate the sums
			    else
			    {
				    int temp1, temp2;
				    memcpy(&temp1, sharedArray + (__SIZEOF_INT__ * ((i * sizeOfArray) + j)), __SIZEOF_INT__);
				    memcpy(&temp2, sharedArray + (__SIZEOF_INT__ * (((i * sizeOfArray) + j) - offset)), __SIZEOF_INT__);
				    temp1 = temp1 + temp2;
				    memcpy(sharedArray + (__SIZEOF_INT__ * (((i + 1) * sizeOfArray) + j)), &temp1, __SIZEOF_INT__);
			    }

            } // end if (j >= calculatedID....)

            else
                continue;
            
        } // end of for loop going through the array

        //Child process Signals parent that it is ready
        if(pid == 0)  
            kill(getppid(), SIGUSR1);

        // Otherwise wait for child's signal
        else
            pause();

        //Parent Process Signals Child  it is ready
        if(mainOrigin == getppid())
            kill(pid, SIGUSR2);

        // Otherwise wait for parent's signal
        else
            pause();
            
    } // end of outer for loop for computation

    
    // If parent
    if(pid != 0)
    {
        // Wait for child
        wait(NULL);
        
        //If main parent
        if(getppid() == mainOrigin)
        {
            //save results to output file
            for(int i = (ceil(log2(sizeOfArray))) * (sizeOfArray); i < ((ceil(log2(sizeOfArray)) + 1) * (sizeOfArray))-diff; i++)
            {
                int temp1;
                memcpy(&temp1, sharedArray + (__SIZEOF_INT__ * i), __SIZEOF_INT__);
                outputFile << temp1 << " ";
            }

        } // end if
        
    } // end if
    
    return 0;
} // end main