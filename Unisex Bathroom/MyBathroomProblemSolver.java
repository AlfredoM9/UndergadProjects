import java.util.concurrent.Semaphore;

public class MyBathroomProblemSolver implements BathroomProblemSolverInterface
{
	int n, switchThreshold; 						// the number of toilets in the bathroom & the threshold for moving to the next phase
	int completed = 0, inside = 0; 					// the number of people who have left the bathroom in the current phase & the number of people currently using the bathroom
	int[] waiting = {0, 0}; 						// the number of people of each gender waiting to use the bathroom
	gender turn; 									// the gender type that can use the bathroom currently
	Semaphore[] safeToUse = new Semaphore[] {new Semaphore(0), new Semaphore(0)}; // semaphore for waiting to enter the bathroom
	Semaphore mutex = new Semaphore(1); 	// semaphore for achieving mutual exclusion

	// Constructor
	public MyBathroomProblemSolver(int n)
	{
		this.n = n;				 // Initialize to given input
		switchThreshold = 2 * n; // Initialize to 2n
	}

	/*arriveAtTheBathroom function keeps track of those waiting for the bathroom and calls the necessary functions
	* to verify the next person to enter the bathroom
	* The arriveAtTheBathroom has an argument of gender to know which gender arrived at the bathroom
	* and coordinate the necessary functions to get them inside*/
	public void arriveAtTheBathroom(gender type) 
	{
		try {
			mutex.acquire();										// wait to enter the critical section
			waiting[type.ordinal()] = waiting[type.ordinal()] + 1;	// increment the number of waiters for the gender

			/* check if can enter the bathroom immediately */
			if(!(okayToEnter(type) || okayToSwitch(type)))
			{
				mutex.release();									// leave the critical section
				safeToUse[type.ordinal()].acquire();				// wait until it is appropriate to use the bathroom
			} // end if

			else
			{
				if(turn != type)									// if gender is incompatible with the current phase
					switchGender(type);								// switch the gender type that can now use the bathroom

				waiting[type.ordinal()] = waiting[type.ordinal()] - 1; // decrement the number of waiters
				inside += 1;										// increment the number of occupants
				mutex.release();									// leave the critical section
			} // end else

			/************Helps debug program*************/
			if(type == gender.MAN)
				System.out.println("Man entering...");
			else
				System.out.println("Woman entering...");
			/*******************************************/

		} // end try
		// catch any error a semaphore may throw
		catch (InterruptedException e) {
			e.printStackTrace();
		} // end catch
	} // end arriveAtBathroom

	/*leaveTheBathroom function keeps track of those leaving the bathroom by accepting a gender type as an argument
	* and initializes the necessary functions to allow other people to enter the bathroom*/
	public void leaveTheBathroom(gender type) 
	{
		try {
			mutex.acquire();										// wait to enter the critical section
			inside -= 1;											// decrement the number of occupants
			completed += 1;											// increment the number of people who have left the bathroom

			/************Helps debug program*************/
			if(type == gender.MAN)
				System.out.println("Man leaving...");
			else
				System.out.println("Woman leaving...");
			/*******************************************/

			/* If its okay to enter */
			if(okayToEnter(type))
			{
				waiting[type.ordinal()] = waiting[type.ordinal()] - 1; // decrement the number of waiters
				inside += 1;										// increment the number of occupants
				safeToUse[type.ordinal()].release();				// wake up a person of my gender
			} // end if

			/* If its okay to switch to opposite gender */
			else if (okayToSwitch(oppositeGender(type)))
			{
				switchGender(oppositeGender(type));

				/* calculate the number of people of the other gender to wake up */
				inside = Math.min(n, waiting[oppositeGender(type).ordinal()]); // set the number of occupants
				waiting[oppositeGender(type).ordinal()] = waiting[oppositeGender(type).ordinal()] - inside; // adjust the number of waiters

				// wake up people of the other gender
				for(int i = 0; i < inside; i++)
					safeToUse[oppositeGender(type).ordinal()].release();
			} // end else

			mutex.release(); // leave critical section
		} // end try
		// catch any error a semaphore may throw
		catch (InterruptedException e) {
			e.printStackTrace();
		} // end catch
	} // end leave bathroom

	/*Opposite gender accepts a gender type and returns the opposite of the gender input type*/
	private gender oppositeGender(gender type) {
		if(type == gender.MAN)
			return gender.WOMAN;
		else
			return gender.MAN;
	} // end oppositeGender

	/*okayToSwitch function tests whether it is okay to switch the gender( by accepting the current phase gender as
	* an argument ) and move to the next phase
	* returns true if all the conditions are moving to the next phase as described earlier are met*/
	private boolean okayToSwitch(gender type) {
		if((turn != type) && (inside == 0) && (waiting[type.ordinal()] > 0) && (((inside + completed) >= switchThreshold) || (waiting[oppositeGender(type).ordinal()] == 0)))
			return true;
		else
			return false;
	} // end okayToSwitch

	/*okayToEnter function test whether it is okay to allow a waiting person to use the bathroom using its gender type (argument)
	* returns false if either the bathroom is full or no more people of the current gender will
	* be allowed in the bathroom in the current phase; otherwise, returns true*/
	private boolean okayToEnter(gender type) {
		if((turn == type) && (waiting[type.ordinal()] > 0) && (inside < n) && (((inside + completed) < switchThreshold) || (waiting[oppositeGender(type).ordinal()] == 0)))
			return true;
		else
			return false;
	} // end okayToEnter

	/*switchGender function moves to the next phase by changing the gender type that can now use the bathroom
	* the function accepts a gender type to start next phase*/
	private void switchGender(gender type) {
		completed = 0;	// reset the count
		turn = type;	// switch the gender
	} // end switchGender
} // end MyBathroomProblemSolver
