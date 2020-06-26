import java.time.Duration;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

// QuickSorted used as a utility class
public class QuickSorter {

    // Uses quickSort to sort an array list
    public static <E extends Comparable<E>> Duration timedQuickSort(ArrayList<E> list, PivotStrategy strategy, int startingIndex, int endingIndex)
    {
        // If the list is ever null or strategy immediately throw an exception
        if(list == null || strategy == null)
            throw new IllegalArgumentException("Error! Invalid Empty Arguments");

        // Base case: If the starting index is the same or greater than the ending Index
        if(startingIndex >= endingIndex)
            return null;

        // Variables for the pivot and its index
        int pivotIndex = -1;
        E pivot = null;

        // Start time to record
        long startTime = System.nanoTime();

        // If the pivot is going to be the first element
        // Obtain the index at front and swap with the last index
        if(strategy.equals(PivotStrategy.FIRST_ELEMENT))
        {
            pivotIndex = startingIndex;
            pivot = list.get(pivotIndex);
            swap(list, pivotIndex, endingIndex);
        } // end if

        // Else if we choose a random pivot
        else if (strategy.equals(PivotStrategy.RANDOM_ELEMENT))
        {
            // Generate random index and swap with the last element
            Random random = new Random();
            pivotIndex = random.nextInt((endingIndex - startingIndex)+1) + startingIndex;
            pivot = list.get(pivotIndex);
            swap(list, pivotIndex, endingIndex);
        } // end else if

        // Else if we choose the median of three random elements as the pivot
        else if (strategy.equals(PivotStrategy.MEDIAN_OF_THREE_RANDOM_ELEMENTS))
        {
            int randomIndex;
            Random random = new Random();
            ArrayList<E> random_elements = new ArrayList<>();

            // Generate three random indices within range and obtain the element and add it to another array list
            for(int i = 0; i < 3; i++)
            {
                randomIndex = random.nextInt((endingIndex - startingIndex)+1) + startingIndex;
                random_elements.add(list.get(randomIndex));
            } // end for

            // Sort the array list that has three random elements
            Collections.sort(random_elements);

            // Get the element in the middle
            pivot = random_elements.get(1);
            pivotIndex = list.indexOf(pivot);
            swap(list, pivotIndex, endingIndex);
        } // end else if

        // Otherwise the median of three specified elements is the pivot
        else
        {
            // Create a new array list to hold the three elements so they can be sorted
            ArrayList<E> elements = new ArrayList<>();
            elements.add(list.get(startingIndex));
            elements.add(list.get((startingIndex + endingIndex)/2));
            elements.add(list.get(endingIndex));

            // Sort them
            Collections.sort(elements);

            // Get the median and swap with the last element
            pivot = elements.get(1);
            pivotIndex = list.indexOf(pivot);
            swap(list, pivotIndex, endingIndex);
        } // end else

        // Variables to stop iterations and point to certain elements
        boolean stopStartingIndex = false, stopEndingIndex = false;
        int tempEndingIndex = endingIndex - 1;
        int modifiedIndex = startingIndex;

        // tempEndingIndex and modifiedIndex hold the indices that point to certain elements we are comparing
        // If the beginning pointer hasn't surpassed the ending pointer then go inside the while loop
        while(modifiedIndex <= tempEndingIndex)
        {
            // If we haven't stopped to swap, then compare if the element it points to is smaller to the pivot
            // If so continue to the next element by incrementing
            if(!stopStartingIndex && list.get(modifiedIndex).compareTo(pivot) <= 0)
                modifiedIndex++;

            // Otherwise, make this stop variable true
            else
                stopStartingIndex = true;

            // If we haven't stopped to swap, then compare if the element it points to is larger to the pivot
            // If so continue to the next element by decrementing
            if(!stopEndingIndex && list.get(tempEndingIndex).compareTo(pivot) > 0)
                tempEndingIndex--;

            // Otherwise, make this stop variable true
            else
                stopEndingIndex = true;

            // If both have stopped, then swapped them, turn the variables back to false
            // And continue by decrementing and incrementing the indices
            if(stopEndingIndex && stopStartingIndex)
            {
                swap(list, modifiedIndex, tempEndingIndex);
                stopEndingIndex = false;
                stopStartingIndex = false;
                modifiedIndex++;
                tempEndingIndex--;
            } // end if
        } // end while

        // Finally swap the pivot to where it belongs
        swap(list, modifiedIndex, endingIndex);

        // Sort the sublist to the left of the pivot
        timedQuickSort(list, strategy, startingIndex, modifiedIndex - 1);

        // Sort the sublist to the right of the pivot
        timedQuickSort(list, strategy, modifiedIndex + 1, endingIndex);

        // Record time taken and return
        long finishTime = System.nanoTime();
        Duration elapsedTime = Duration.ofNanos(finishTime - startTime);
        return elapsedTime;
    } // end timedQuickSort

    // Generates a random array list of specified size
    public static ArrayList<Integer> generateRandomList(int size)
    {
        // If size is less than zero throw exception
        if (size < 0)
            throw new IllegalArgumentException("Error! Size for random list is invalid");

        Random random = new Random();
        ArrayList<Integer> array = new ArrayList<>();

        // Generate random number and add it to the list
        for (int i = 0; i < size; i++)
            array.add(random.nextInt());

        // Return array list
        return array;
    } // end generateRandomList

    // enum used to indicate which pivot we are choosing
    public static enum PivotStrategy
    {
        FIRST_ELEMENT,
        RANDOM_ELEMENT,
        MEDIAN_OF_THREE_RANDOM_ELEMENTS,
        MEDIAN_OF_THREE_ELEMENTS
    } // end PivotStrategy

    // Swaps two elements in a list
    private static <E extends Comparable<E>> void swap(ArrayList<E> list, int index1, int index2)
    {
        // Swap elements
        E temp = list.get(index1);
        list.set(index1, list.get(index2));
        list.set(index2, temp);
    } // end swap
} // end QuickSorter
