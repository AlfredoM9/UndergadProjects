/* Author: Alfredo
*  Net ID: axm180023
*    Date: 11/30/2019
*  Course: SE 3345.004
*  Descrp: This program accepts 4 arguments, any other number of arguments will generate an error.
*          The 4 arguments are a number to indicate the size of the array, the name of the file
*          for the report time of the quick sort, the name of the file where the unsorted array
*          will be printed, and the name of the file where the sorted array will be printed.
*          This program will first generate a random generated array of the specified size using QuickSorter.java.
*          An exception is throw if the size is less than zero. Then it writes the unsorted array
*          to the specified file. Next, it calls the quick sort function to sort the array and returns the time
*          it took to do such operation. We do this for a total of 4 times each specifying different techniques
*          to choose the pivot. Finally, we write the sorted array to the specified file. All exception handling is
*          handled for IO exceptions.
 */
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.time.Duration;
import java.util.ArrayList;
import java.util.Arrays;

public class Main {

    // Main Class
    public static void main (String[] args)
    {
        // If not enough arguments display error message and exit program
        if (args.length != 4)
        {
            System.out.print("Error Incorrect Arguments:" + Arrays.toString(args));
            System.exit(0);
        } // end if

        // Convert the arguments into local variables
        int arraySize = Integer.parseInt(args[0]);
        String reportFileName = args[1];
        String unsortedFileName = args[2];
        String sortedFileName = args[3];

        // Create an array of duration to hold more than one and create an array list
        Duration[] duration = new Duration[4];
        ArrayList<Integer> list = new ArrayList<>();

        // Generate random list with specified size
        try
        {
            list = QuickSorter.generateRandomList(arraySize);
        } // end try

        // Catch if invalid array size
        catch (Exception e)
        {
            System.out.print("Error! Invalid Array Size");
            System.exit(0);
        } // end catch

        // Write the unsorted array to the file
        try
        {
            FileWriter fileWriter = new FileWriter(unsortedFileName);
            PrintWriter printWriter = new PrintWriter(fileWriter);
            for(int i = 0; i < arraySize; i++)
                printWriter.println(list.get(i));
            printWriter.close();
        } // end try

        // Catch if a file error occurs
        catch (IOException e)
        {
            e.printStackTrace();
        }

        // Sort the array choosing the first element as the pivot
        ArrayList<Integer> tempList1 = list;
        duration[0] = QuickSorter.timedQuickSort(tempList1, QuickSorter.PivotStrategy.FIRST_ELEMENT, 0, arraySize - 1);

        // Sort the array choosing a random element as the pivot
        ArrayList<Integer> tempList2 = list;
        duration[1] = QuickSorter.timedQuickSort(tempList2, QuickSorter.PivotStrategy.RANDOM_ELEMENT, 0, arraySize - 1);

        // Sort the array choosing the median of three random elements as the pivot
        ArrayList<Integer> tempList3 = list;
        duration[2] = QuickSorter.timedQuickSort(tempList3, QuickSorter.PivotStrategy.MEDIAN_OF_THREE_RANDOM_ELEMENTS, 0, arraySize - 1);

        // Sort the array choosing the median of three specified elements as the pivot
        duration[3] = QuickSorter.timedQuickSort(list, QuickSorter.PivotStrategy.MEDIAN_OF_THREE_ELEMENTS, 0, arraySize - 1);


        // Write to the file the new sorted array
        try
        {
            FileWriter fileWriter = new FileWriter(sortedFileName);
            PrintWriter printWriter = new PrintWriter(fileWriter);
            for(int i = 0; i < arraySize; i++)
                printWriter.println(list.get(i));
            printWriter.close();
        } // end try

        // Catch if a file error occurs
        catch (IOException e)
        {
            e.printStackTrace();
        } // end catch

        // Write the report to the file
        try
        {
            FileWriter fileWriter = new FileWriter(reportFileName);
            PrintWriter printWriter = new PrintWriter(fileWriter);
            printWriter.println("Array Size = " + arraySize);
            printWriter.println("FIRST_ELEMENT : " + duration[0]);
            printWriter.println("RANDOM_ELEMENT : " + duration[1]);
            printWriter.println("MEDIAN_OF_THREE_RANDOM_ELEMENTS : " + duration[2]);
            printWriter.println("MEDIAN_OF_THREE_ELEMENTS : " + duration[3]);
            printWriter.close();
        } // end try

        // Catch if a file error occurs
        catch (IOException e)
        {
            e.printStackTrace();
        } // end catch

    } // end main

} // end main class
