/*  Author: Alfredo Mejia
 *  Net ID: axm180023
 *  Date:   10/12/2019
 *  Course: SE 3345.004
 *  Descrp: This class is the main class. When compiled there will be
 *          two arguments passed. One for the input file and the other
 *          for the output file. The input file will have the certain
 *          commands to follow with the lazy binary search tree and
 *          depending on the outcome of the method it will print
 *          the outcome in the output file. The commands are insert,
 *          delete (this is lazy deletion, the node is only marked as
 *          deleted but not physically removed), contains, findMin, findMax,
 *          height, size, and print (it will print in pre-order). Insert,
 *          delete, and contains require an argument (a number) in order
 *          to perform the operation. Any errors will be caught and printed
 *          to the file.
 *
 */


import java.io.File;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class MainBinarySearchDriver {
    public static void main(String[] args) {

        // If it doesn't have two arguments then an error should occur
        if (args.length!=2) {
            System.out.print("Error Incorrect Arguments:" + Arrays.toString(args));
            System.exit(0);
        }

        // Use scanner to read in from a file
        Scanner in;
        try {

            // Initialize scanner and printwriter to read and write from files
            File input_file = new File(args[0]);
            in = new Scanner(input_file);
            File output_file = new File(args[1]);
            PrintWriter  out;
            out = new PrintWriter(output_file);

            // Create LazyBinarySearchTree
            LazyBinarySearchTree myTree = new LazyBinarySearchTree();

            // While there is stuff to read from the file go inside
            while (in.hasNext()) {

                // Initialize the line to a string
                String input = in.next();

                // Lowercase all letters
                input = input.toLowerCase();

                // Create integer to save an int if there command needs it
                Integer number = null;

                //If the string has ':' then we expect a certain command with an integer
                if (input.contains(":")) {
                    // Split it into two: one with a command and the other with an integer
                    String command[] = input.split(":");
                    input = command[0];
                    number = Integer.parseInt(command[1]);
                } // end if

                // Input has the command so we are going to try to match it
                switch (input) {
                    // If it matches with insert
                    case "insert":
                        // Check if we have a number, if we don't print error
                        if(number == null)
                            out.println("Error in Line: " + input);

                        // Otherwise call the insert method of my tree
                        else {
                            // Check if the number is in bounds
                            try {
                                boolean result = myTree.insert(number);
                                if(result)
                                    out.println("True");
                                else
                                    out.println("False");
                            } catch (Exception e) {
                                out.println(e.getMessage());
                            }
                        } // end else
                        break;

                    // If it matches with delete
                    case "delete":

                        // Check if we have a number and if we don't print error
                        if(number == null)
                            out.println("Error in Line: " + input);

                        // If we do then delete
                        else {
                            // Check if the number is in bounds
                            try {
                                boolean result = myTree.delete(number);
                                if(result)
                                    out.println("True");
                                else
                                    out.println("False");
                            } catch (Exception e) {
                                out.println(e.getMessage());
                            }
                        } // end else
                        break;

                    // If it matches with contains
                    case "contains":

                        // If we don't have a number print an error
                        if(number == null)
                            out.println("Error in Line: " + input);

                        // If we do then check if it contains
                        else {
                            // Check if the number is in bounds
                            try {
                                boolean result = myTree.contains(number);
                                if(result)
                                    out.println("True");
                                else
                                    out.println("False");
                            } catch (Exception e) {
                                out.println(e.getMessage());
                            }
                        } // end else
                        break;

                    // If it matches with findmax then call the method
                    case "findmax":
                        out.println(myTree.findMax());
                        break;

                    // If it matches with findmin then call the method
                    case "findmin":
                        out.println(myTree.findMin());
                        break;

                    // If it matches with height then call the method
                    case "height":
                        out.println(myTree.height());
                        break;

                    // If it matches with size then call the method
                    case "size":
                        out.println(myTree.size());
                        break;

                    // If it matches with printtree then call the method
                    case "printtree":
                        out.println(myTree.toString());
                        break;

                    // If none of these match then print error
                    default:
                        out.println("Error in Line: " + input);
                } // end switch case

            } // end while

            // Close files
            in.close();
            out.close();

        } // end try

        // Catch any exception
        catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        } // end catch

    } // end main method
} // end main class
