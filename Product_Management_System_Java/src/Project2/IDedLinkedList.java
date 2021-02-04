/* Descr: This will implement a linked list with a generic type that
*         only implements IDedObject. In order for the list to be
*         a linked list I created another class within it. It holds
*         a MyItem object and pointer to the next Node. This
*         class also has the methods necessary to insert, delete,
*         make an empty list, find an ID, and any other needed per
*         the assignment description.
 */

package Project2;

public class IDedLinkedList <AnyType extends IDedObject>{

    // Create head and next pointers
    Node head, next;

    // Constructor
    IDedLinkedList()
    {
        head = null;
        next = null;
    }

    // Create Node to actually have something to point to
    class Node
    {
        // Stores actual value and pointer
        AnyType value;
        Node next;

        // Node Constructor
        Node()
        {
            value = null;
            next = null;
        }

        // Node Constructor with Parameter
        Node (AnyType x)
        {
            value = x;
            next = null;
        }


    } // end of Node class


    // This function makes the linked list empty
    public void makeEmpty()
    {
        Node current = head;
        while(current != null)
        {
            // Points all pointers to null thus the garbage collectors takes care of it
            Node temp = current.next;
            current.next = null;
            current = temp;
        }
    } // end of makeEmpty

    // This function adds an object to the end of the linked list
    // This function isn't needed as the assignment didn't require it however
    // I added it just to practice with my linked list
    public void insert(AnyType x)
    {
        Node input = new Node(x);

        // If empty: make it the head
        if(head == null)
            head = input;

        // Otherwise add it to the end
        else
        {
            Node current = head;
            while(current.next != null)
            {
                current = current.next;
            }

            current.next = input;
        }
    } // end of insert

    // This function adds an object AT THE FRONT of the linked list
    public boolean insertAtFront(AnyType x)
    {
        AnyType found = findID(x.getID());

        // If it is not found then add at the front
        if(found == null)
        {
            Node input = new Node(x);
            input.next = head;
            head = input;
            return true;
        }

        // Otherwise return false
        else
            return false;
    } // end insertAtFront

    // This will find an item with the ID passed and if so the item will be return otherwised
    // it will return null
    public AnyType findID(int ID)
    {
        Node current = head;

        // Transverse the linked list and find one that has the same ID
        while(current != null)
        {
            if(current.value.getID() == ID)
                return current.value;

            current = current.next;
        }

        // If not found return null
        return null;
    } // end findID

    // This function will delete from the front of the list
    public AnyType deleteFromFront()
    {
        if(head == null)
            return null;

        Node temp = head.next;
        head.next = null;
        Node deletedNode = head;
        head = temp;
        return temp.value;
    } // end deleteFromFront

    // This function will delete an item of the list that has a certain ID
    public AnyType delete(int ID)
    {
        Node current = head, temp = null, deletedItem = null;
        int control = 0;
        boolean found = false;

        // Try to find the item with the same ID
        while(current != null)
        {
            if(current.value.getID() == ID)
            {
                found = true;
                temp = current.next;
                current.next = null;
                deletedItem = current;
                break;
            }
            current = current.next;
            control++;
        }

        // If found then delete it
        if(found)
        {
            current = head;
            for (int i = 0; i < control-1; i++)
                current = current.next;
            current.next = temp;
            return deletedItem.value;
        }

        // Otherwise return null
        else
            return null;

    } // end delete

    // This will add all of the IDs from the linked list
    public int printTotal()
    {
        // If empty return -1
        if(head == null)
            return -1;

        // Otherwise loop through it and add all of IDs
        else
        {
            Node current = head;
            int sumOfIDs = 0;
            while(current != null)
            {
                sumOfIDs += current.value.getID();
                current = current.next;
            }

            // Return sum
            return sumOfIDs;
        }
    } // end of printTotal
} // end of IDedLinkedList
