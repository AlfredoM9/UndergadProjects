/* Descr: This class would hold an item's details.
*         It would hold the item's ID, the price
*         and the item's description. It will have
*         a constructor that will initialize all of
*         its member fields. It will also implement
*         the IDedObject interface which means it will
*         implement the getID and printID method. Finally
*         it will have the toString method to print all
*         of its member fields
 */

package Project2;
import java.util.List;

public class MyItem implements IDedObject{

    // Private members
    private int itemID;
    private int itemPrice;
    private List<Integer> itemDescription;

    // Constructor
    MyItem()
    {
        itemID = -999999999;
        itemPrice = -999999999;;
        itemDescription = null;
    }

    // Constructor with Parameters (initialize the member fields)
    MyItem (int ID, int price, List<Integer> items)
    {
        itemID = ID;
        itemPrice = price;
        itemDescription = items;
    }

    // Returns item ID
    public int getID()
    {
        return itemID;
    }

    // Returns a string that is the item's ID
    public String printID()
    {
        return "The ID is: " + itemID;
    }

    // Prints all of the member fields by just the name of the object
    @Override
    public String toString()
    {
        // Adds all members to a string
        String output = itemID + " " + itemPrice;
        for (int i = 0; i < itemDescription.size(); i++)
        {
            output = output + " " + itemDescription.get(i);
        }

        return output;
    } // end of toString

} // end of MyItem class
