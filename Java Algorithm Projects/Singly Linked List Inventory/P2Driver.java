/* Author: Alfredo Mejia
*  Net ID: axm180023
*  Date:   10/6/2019
*  Course: SE 3345.004
*  Descrp: This class is the main class. When compiled there will be
*          two arguments passed. One for the input file and the other
*          for the output file. Then after it is executed the output
*          file will have the necessary output according to the input
*          file. So basically, this class will read in an input file
*          and do the necessary commands as described by the command
*          in the file and per the assignment description.
*
 */

package Project2;

import java.io.File;
import java.util.List;
import java.util.Scanner;
import java.util.*;
import java.io.PrintWriter;

public class P2Driver {
    public static void main(String[] args){

        // If it doesn't have two arguments then an error should occur
        if (args.length!=2) {
            System.out.print("Error Incorrect Arguments:" + Arrays.toString(args));
            System.exit(0);

        }

        // Otherwise use scanner to read in from file
        Scanner in;
        try
        {
            // Create necessary objects to read and write into files
            File input_file = new File(args[0]);
            in = new Scanner(input_file);
            File output_file = new File(args[1]);
            PrintWriter  out;
            out = new PrintWriter(output_file);

            // Create linked list
            IDedLinkedList<MyItem> LL = new IDedLinkedList();

            String operation = "";
            int lineno = 0;


            int id, price;
            boolean result;
            List<Integer> name = new LinkedList<>();

            // Obtain command
            whileloop:
            while (in.hasNext())
            {
                lineno++;

                operation = in.next();
                if(operation.charAt(0) == '#')
                {
                    in.nextLine();
                    continue;
                }

                // Check which command was read
                switch (operation)
                {
                    // If end was read then stop
                    case "End":
                        break whileloop;

                    // If insert then use the necessary method
                    case "Insert":
                        try
                        {
                            id = in.nextInt();
                            price = in.nextInt();
                            name.clear();
                            while(true) {
                                int val = in.nextInt();
                                if(val == 0) { break; }
                                else { name.add(val); }
                            }
                            // Add the item to the front
                            MyItem new_item = new MyItem(id, price, name);
                            result = LL.insertAtFront(new_item);
                            //result = Insert the item into the linkedlist and get true or false
                            out.println(result ? "True" :"False");
                        }

                        // Catch error
                        catch (Exception e)
                        {
                            out.println("ERROR");
                        }

                        break;

                    // If findID then use the method to do use
                    case "FindID":
                        try
                        {
                            id = in.nextInt();
                            MyItem item1 = LL.findID(id);

                            // If not found then print null
                            if(item1 == null)
                                out.println("NULL");

                            // Otherwise print item's info
                            else
                                out.println(item1.toString());
                        }
                        catch (Exception e)
                        {
                            out.println("ERROR");
                        }
                        break;

                    // If command is to delete: do so
                    case "DeleteID":
                        try
                        {
                            id = in.nextInt();
                            //Call the DeleteID method and printID method to print to the output file the entire item in a line. If the item is not found or the list is empty print Null
                            MyItem  item1 = LL.delete(id);

                            // If not found then print null
                            if(item1 == null)
                                out.println("NULL");

                            // Otherwise print deleted item's info
                            else
                                out.println(item1.toString());
                        }
                        catch (Exception e)
                        {
                            out.println("ERROR");
                        }

                        break;

                    // If command is to delete the front: do so
                    case "Delete":
                        //If the list is not empty print and delete the first item in the list. if the list is empty print Null
                        MyItem  item1 = LL.deleteFromFront();

                        // If the list is empty print null
                        if(item1 == null)
                            out.println("NULL");

                        // Otherwise print deleted item's info
                        else
                            out.println(item1.toString());
                        break;

                    // If command is PrintTotal: then do so
                    case "PrintTotal":
                        //Call the printtotal method of the linkedlist and print the given int into the output file.
                        int total = LL.printTotal();
                        out.println(total);
                        break;

                    default:
                        out.println("ERROR");
                        in.nextLine();

                } // end of case

            } // end of while

            // Close files
            in.close();
            out.close();

        } // end of try
        catch(Exception e)
        {
            System.out.println("Exception: " + e.getMessage());
        }


    }// end of main method

} // end of P2Driver class

