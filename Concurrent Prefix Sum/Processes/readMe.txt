Authors:Bryanth Fung, and Alfredo Mejia

* if needed drafts and prior work leading up to the completion of this program can be submitted along with the systems timestamps and team communication. *

The intention of this program is to compute a prefix sum on a number of given inputs which will be supplied through a file and whose size will be known before reading the file.
After the algorithm is executed and everything is finished the results are saved to an output file.

*Disclaimer
    To run this program a UNIX based System is needed so a Linux, Mac or Windows Machine with "Windows SubSystem for Linux"(WSL) is needed.
    It also requires to have the g++ package, if the system does not have it run the following command: "sudo apt install g++" and it should install it.
    It may also require a somewhat recent version of Linux, this program was written in a WSL with Ubuntu LTS release at this time(2/28/2020)

To run the program the following commands should be executed:
1. g++ cps.cpp
2. ./a.out 'num of inputs' 'input FileName' 'output FileName' 'num of processes'
    *The single quotes are just placeholders they should not be used in the commands.

The executable when compiled results in warnings which cen be ignored as mainly they have to do with pocpinter arithmetic and they have been tested to work as intended.

Functions:
main()-main driver for the program it contains the algorithm for the calculation and the signal calls to handle synchronization as well as checking the argument count.
alertParent()-Child process alerts the parent that it is ready
alertChild()-Parent process alerts the child that it is ready
readFile()-reads the file and checks the inputfile for errors of its data-inputs.
errorCheck()-reads the arguments and error checks the the command for the size of array and the num of processes as well as checking if the files opened successfully.
