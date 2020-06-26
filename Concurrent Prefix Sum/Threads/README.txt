Authors:Bryanth Fung, and Alfredo Mejia

* if needed drafts and prior work leading up to the completion of this program can be submitted along with the systems timestamps and team communication. *

The intention of this program is to compute a prefix sum on a number of given inputs which will be supplied through a file and whose size will be known before reading the file.
After the algorithm is executed and everything is finished the results are saved to an output file.

*Disclaimer
    To run this program a UNIX based System is needed so a Linux, Mac or Windows Machine with "Windows SubSystem for Linux"(WSL) is needed.
    It also requires to have the g++ package, if the system does not have it run the following command: "sudo apt install g++" and it should install it.
    It may also require a somewhat recent version of Linux, this program was written in a WSL with Ubuntu LTS release at this time(3/13/2020)

    The program was run and tested with also at cs2 linux server from utd per the instructors instruction which is what is assumed is going to be used for grading this assignment.

    Boost for c++ library is needed for this program to run.

To run the program the following commands should be executed:
1. g++ -g -std=c++11 cps.cpp -o cps -lboost_system -lboost_thread
2. ./cps 'num of inputs' 'input FileName' 'output FileName' 'num of processes'
    *The single quotes are just placeholders they should not be used in the commands.

The executable when compiled results in warnings which can be igor each itrnored as mainly they have to do with pointer arithmetic and they have been tested to work as intended.

Functions:
main()-main driver for the program  where the threads join
calculation()-Where our algorithm does it works it takes the necessary information and run the calculation for its iteration.
readFile()-reads the file and checks the inputfile for errors of its data-inputs.
errorCheck()-reads the arguments and error checks the the command for the size of array and the num of processes as well as checking if the files opened successfully.
