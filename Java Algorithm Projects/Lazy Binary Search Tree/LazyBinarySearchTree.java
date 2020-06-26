import java.util.ArrayList;

public class LazyBinarySearchTree
{
    // Member Fields used throughout
    private int size;
    private String preOrderOutput;
    private TreeNode root;
    private ArrayList<Integer> heights = new ArrayList<>();

    // Constructor
    LazyBinarySearchTree()
    {
        root = null;
        size = 0;
    } // end constructor

    // TreeNode class for each node to hold specific data
    private class TreeNode
    {
        // Node data
        int key;
        TreeNode leftChild;
        TreeNode rightChild;
        boolean deleted;

        // Node Constructor
        TreeNode()
        {
            leftChild = null;
            rightChild = null;
            deleted = false;
        } // end constructor

        // Node Constructor with a newKey
        TreeNode(int newKey)
        {
            key = newKey;
            leftChild = null;
            rightChild = null;
            deleted = false;
        } // end constructor

    } // end TreeNode class

    // Insert Method
    public boolean insert (int newKey)
    {
        // If newKey is out of range throw exception
        if(newKey < 1 || newKey > 99)
            throw new IllegalArgumentException("Error in insert: IllegalArgumentException raised");

        // If there is no root then make a new node with this key being the root
        if(root == null)
        {
            // Make root with this being the key
            root = new TreeNode();
            root.key = newKey;
            size++;             // Increase size
            return true;
        } // end if

        // Otherwise if there is a root already
        else
        {
            // Prepare to insert a new node
            TreeNode current = root, previous = null;
            boolean right = false;

            // While the current node being inspected isn't null
            while(current != null)
            {
                // If the newKey wanting to be inserted is greater than the current's node key
                if(newKey > current.key)
                {
                    // Move to the right of tree to inspect it
                    // Keep track of the previous node just in case
                    // This node is null so the previous can point to
                    // The new node
                    previous = current;
                    current = current.rightChild;
                    right = true;               // keep track if it goes left or right

                } // end if

                // If the newKey is lower than the node's current key
                else if (newKey < current.key)
                {
                    // Move to the left of tree to inspect it
                    // Keep track of the previous node just in case
                    // This node is null so the previous can point to
                    // The new node
                    previous = current;
                    current = current.leftChild;
                    right = false;              // keep track if it goes left or right
                } // end else if

                // If the keys equal and it is deleted then undelete it
                else if (newKey == current.key && current.deleted)
                {
                    current.deleted = false;
                    return false;
                } // end if

                // Otherwise they equal and it is not deleted so don't do anything
                else
                    return false;
            } // end while

            // Make the actual new node now
            TreeNode newNode = new TreeNode(newKey);

            //If it's suppose to go right, place it there
            if(right)
                previous.rightChild = newNode;

            // If it's suppose to go left, place it there
            else
                previous.leftChild = newNode;

            size++; // increase size

            return true;
        } // end else
    } // end Insert

    // Delete Method
    public boolean delete (int newKey)
    {
        // If the newKey is out of range throw exception
        if(newKey < 1 || newKey > 99)
            throw new IllegalArgumentException("Error in delete: IllegalArgumentException raised");

        // Create temp pointer
        TreeNode current = root;

        // While current is not null goes inside
        while(current != null)
        {
            // If the current node's key matches the key and it is already deleted then do nothing
            if(current.key == newKey && current.deleted)
               return false;

            // If the keys match and it is not deleted then delete it
             else if (current.key == newKey && !current.deleted)
             {
                 current.deleted = true;
                 return true;
             } // end else if

            // If the key is bigger than the node's key then move right
             else if (newKey > current.key)
                 current = current.rightChild;

             // If the key is smaller than the node's key then move left
             else if (newKey < current.key)
                 current = current.leftChild;
        } // end while

        return false;
    } // end delete

    // FindMin method
    public int findMin()
    {
        // If tree is empty
        if(root == null)
            return -1;

        // Temp pointer to a node
        TreeNode current = root;

        // While the left child isn't null go inside
        while(current.leftChild != null)
        {
            // If the left child is deleted, then we are going to check
            // if there is any other node not deleted beyond it
            if(current.leftChild.deleted) {

                // Call findNotDelete method to find node that is not deleted
                TreeNode temp = findNotDelete(current.leftChild, "min");

                // If it returns a node that is deleted that means there is no
                // node beyond it that is not deleted thus break away from the loop
                // because the current is the smallest number
                if (temp.deleted) {
                    break;
                }
                // Otherwise it returned the next node that wasn't deleted
                else
                    current = temp;
            } // end if

            // If the node is not deleted continue to go left
            else
                current = current.leftChild;
        } // end while

        return current.key;
    } // end findMin

    // FindMax Method
    public int findMax()
    {
        // If tree is empty return -1
        if(root == null)
            return -1;

        // Temp node to loop thru the tree
        TreeNode current = root;

        // While it has a left node go inside
        while(current.rightChild != null)
        {
            // If the left child is deleted, then we are going to check
            // if there is any other node not deleted beyond it
            if(current.rightChild.deleted) {

                // Call findNotDelete to find the node that is not deleted
                TreeNode temp = findNotDelete(current.rightChild, "max");

                // If it returns a node that is deleted that means there is no
                // node beyond it that is not deleted thus break away from the loop
                // because the current is the smallest number
                if (temp.deleted) {
                    break;
                }

                // Otherwise it found a node that is not deleted and is beyond the previous one
                // so assign current to this node
                else
                    current = temp;
            } // end if

            // If the right child is not deleted then continue to go right
            else
                    current = current.rightChild;
        } // end while

        return current.key;
    } // end findMax

    // Private class used in findMax and findMin that allows to find a node that is not deleted
    private TreeNode findNotDelete(TreeNode node, String direction)
    {
        // If we are finding min
        if(direction == "min") {
            // Go to the left most node that is not deleted or
            // Until you reach the end of the tree based on the node given
            while (node.deleted && node.leftChild != null)
                node = node.leftChild;

        } // end if

        // Otherwise help findMax
        else
        {
            // Go to the right most node that is not deleted or
            // Until you reach the end of the tree based on the node given
            while (node.deleted && node.rightChild != null)
                node = node.rightChild;

        } // end else
        return node;
    } // end private class findNotDeleted

    // Contains method
    public boolean contains (int newKey)
    {
        // If key given is out of range throw exception
        if(newKey < 1 || newKey > 99)
            throw new IllegalArgumentException("Error in contains: IllegalArgumentException raised");

        // If tree empty return false
        if(root == null)
            return false;

        // Otherwise
        else
        {
            // Temp pointer to node
            TreeNode current = root;

            // While current is not null go inside
            while(current != null)
            {
                // If they match and it is not deleted then return true
                if(current.key == newKey && !current.deleted)
                    return true;

                // If they match and it is deleted then return false
                else if(current.key == newKey && current.deleted)
                    return false;

                // If key given is greater than key of node: go right
                else if(newKey > current.key)
                    current = current.rightChild;

                // If key given is less than key of node: go left
                else if(newKey < current.key)
                    current = current.leftChild;
            } // end while

            return false;
        } // end else

    } // end contains

    // toString method
    @Override
    public String toString()
    {
        // Call preOrderPrint to preorder print to a string called preOrderOutput
        // then return that string
        preOrderPrint();
        return preOrderOutput;
    }

    // Height Method
    public int height ()
    {
        // Temp pointer to node
        TreeNode current = root;

        // If empty return 0
        if(root == null)
            return 0;

        // Initialize the height to 0
        int height = 0;

        // If the left side isn't empty check the heights of it
        if(root.leftChild != null)
            height(root.leftChild, height);

        // If the right side isn't empty check the heights of it
        if(root.rightChild != null)
            height(root.rightChild, height);

        // All of the heights have been stored in an array list
        // So just find the maximum height and return it
        for(int i = 0; i < heights.size(); i++)
        {
            if(heights.get(i) > height)
                height = heights.get(i);
        }

      return height;
    } // end Height

    // Overloaded method that helps the public class height
    // Private class that helps public class height to find the maximum height
    private int height(TreeNode node, int ht)
    {
        // If it came in here then it moved an edge so we add one
        // to ht (height)
        ht++;

        // If has a left child call height again with an updating height
        if(node.leftChild != null)
            // It will return the height of that current node
            ht = height(node.leftChild, ht);

        // If it has a right child call height again with an updating height
        if(node.rightChild != null)
            // It will return the height of that current node
            ht = height(node.rightChild, ht);

        // Once it reaches here it has reached a leaf so add it to the array list
        heights.add(ht);

        // Decrease ht (height) because we are moving back an edge
        ht--;

        return ht;
    }

    // Size method
    public int size()
    {
        // We are keep track of size with a variable so just
        // Return size
        return size;
    }

    // Private method that helps initialize the preOrderOutput string
    // So it can be return in the toString method
    private void preOrderPrint()
    {
        // If it is not empty
        TreeNode current = root;
        if(current != null)
        {
            // Check if current is not deleted print w/o an asterisk
            if(!current.deleted)
                preOrderOutput = current.key + " ";

            // If it is deleted print with an asterisk
            if(current.deleted)
                preOrderOutput = "*" + current.key + " ";

            // Go the left side of the tree first
            if(current.leftChild != null)
                preOrderPrint(current.leftChild);

            // Then go to the right side
            if(current.rightChild != null)
                preOrderPrint(current.rightChild);
        } // end if
    } // end preOrderPrint

    // Overload method that helps the preOrderPrint class which in turn helps the toString method
    // In reality, these methods are used to add to a string so the toString method can return
    // that string which is preOrderOutput
    private void preOrderPrint(TreeNode node)
    {
        // If the node is not deleted add to string w/o an asterisk
        if(!node.deleted)
            preOrderOutput += node.key + " ";

        // If the node is deleted add to string w/ an asterisk
        if(node.deleted)
            preOrderOutput += "*" + node.key + " ";

        // Continue going left
        if(node.leftChild != null)
            preOrderPrint(node.leftChild);

        // Continue going right
        if(node.rightChild != null)
            preOrderPrint(node.rightChild);
    } // end preOrderPrint
} // end LazyBinarySearchTree
