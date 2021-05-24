# myTeam.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).

########################################################################################################################

# Author: Alfredo Mejia
# Date: 5/2/21
# Descrp: This program executes the algorithm in choosing the best action for my pacman agents.
#         It uses a star search with the goal constanting changing depending on the game state.
#         The g value depends on the goal and the heurisitc is the maze distance to the goal.


# Imports
from captureAgents import CaptureAgent
import util


# Creation of team
def createTeam(firstIndex, secondIndex, isRed,
               first='OffensiveAgent', second='DefensiveAgent'):
    # The following line is an example only; feel free to change it.
    return [eval(first)(firstIndex), eval(second)(secondIndex)]


##########
# Agents #
##########

# Base Agent for Offensive and Defensive Agent
class BaseAgent(CaptureAgent):
    # Initialization of class
    def registerInitialState(self, gameState):
        # Initialize the parent class Capture Agent
        CaptureAgent.registerInitialState(self, gameState)

        # Many attributes to calculate the best action
        self.walls = self.getWalls(gameState)
        self.currentPosition = gameState.getInitialAgentPosition(self.index)
        self.previousPosition = gameState.getInitialAgentPosition(self.index)
        self.isWeak = False
        self.isPacman = False
        self.foodAttacking = self.getFood(gameState)
        self.foodDefending = self.getFoodYouAreDefending(gameState)
        self.capsulesAttacking = self.getCapsules(gameState)
        self.capsulesDefending = self.getCapsulesYouAreDefending(gameState)
        self.goal = None
        self.foodCarrying = 0
        self.halfMaze = (self.walls[len(self.walls) - 1][0] + 1) / 2
        self.enemies = []
        self.closestEscape = self.currentPosition
        self.maxHeight = sorted(self.walls, key=lambda x: x[1], reverse=True)[0][1]
        self.counter = 0
        self.escapeRoutes = self.getEscapeRoutes()

        # Create the enemy base agent class
        for enemy in self.getOpponents(gameState):
            self.enemies.append(EnemyAgent(enemy, gameState, self.halfMaze))

    # Choose action is defined in the child class
    def chooseAction(self, gameState):
        util.raiseNotDefined()

    # Calls necessary methods to update the attributes
    def updateData(self, gameState):
        self.previousPosition = self.currentPosition
        self.currentPosition = gameState.getAgentPosition(self.index)
        self.isWeak = self.getIsWeak(gameState)
        self.isPacman = self.getIsPacman()
        self.getFoodCarring()
        self.foodAttacking, self.foodDefending = self.getTeamFood(gameState)
        self.capsulesAttacking = self.getCapsules(gameState)
        self.closestEscape = self.getClosestEscape()

        # Update the data of the enemy too
        for enemy in self.enemies:
            enemy.updateData(gameState)

    # Determines if the agent is weak
    def getIsWeak(self, gameState):
        capsules = self.getCapsulesYouAreDefending(gameState)

        # If the enemy got a capsule on our side
        if len(capsules) != len(self.capsulesDefending):
            # Keep track of the number of moves and return true
            self.counter = 1
            self.capsulesDefending = capsules
            return True

        # If the agent died, then it is not weak
        elif self.isWeak and 0 < self.counter < 40 and self.getMazeDistance(self.currentPosition,
                                                                              self.previousPosition) > 1:
            self.counter = 0
            return False

        # If not dead, increase counter of moves
        elif self.isWeak and 0 < self.counter < 40:
            self.counter += 1
            return True

        # Once it reaches 40 then it is not weak anymore
        elif self.counter >= 40:
            self.counter = 0
            return False

    # Determines if the agent is pac-man
    def getIsPacman(self):
        # If it is in the other side then return true
        if (self.red and self.currentPosition[0] >= self.halfMaze) or (
                not self.red and self.currentPosition[0] < self.halfMaze):
            return True

        # Otherwise, return false
        else:
            return False

    # Get the updated food
    def getTeamFood(self, gameState):
        foodMatrix = self.getFood(gameState)
        foodAttack = []

        # Get food that you're attacking
        for x_index, xfood in enumerate(foodMatrix):
            for y_index, yfood in enumerate(foodMatrix[x_index]):
                if yfood:
                    foodAttack.append((x_index, y_index))

        foodMatrix = self.getFoodYouAreDefending(gameState)
        foodDefend = []

        # Get food that you're defending
        for x_index, xfood in enumerate(foodMatrix):
            for y_index, yfood in enumerate(foodMatrix[x_index]):
                if yfood:
                    foodDefend.append((x_index, y_index))

        # Return food
        return foodAttack, foodDefend

    # Update the number of food carrying
    def getFoodCarring(self):
        # If agent is at a food attacking then increase the food carrying
        if self.currentPosition in self.foodAttacking:
            self.foodCarrying = self.foodCarrying + 1

        # If the pacman reached their side or died then food carrying is 0
        elif not self.isPacman or self.getMazeDistance(self.currentPosition, self.previousPosition) > 1:
            self.foodCarrying = 0

    # Get the walls position
    def getWalls(self, gameState):
        wallsMatrix = gameState.getWalls()
        walls = []

        # Get walls positions
        for x_index, xwall in enumerate(wallsMatrix):
            for y_index, wall in enumerate(wallsMatrix[x_index]):
                if wall:
                    walls.append((x_index, y_index))

        # Returns walls
        return walls

    # Get the closest escape to the pacman
    def getClosestEscape(self):
        # If pacman calculate closest escape
        if self.isPacman:
            possible_exits = [(escape, self.getMazeDistance(self.currentPosition, escape)) for escape in self.escapeRoutes]
            possible_exits.sort(key=lambda x: x[1])

            return possible_exits[0][0]

        # Otherwise return current position
        else:
            return self.currentPosition

    # Get all the escape routes positions
    def getEscapeRoutes(self):
        # If red change the x axis
        if self.red:
            escapeRoutes = [(self.halfMaze - 1, j) for j in range(self.maxHeight) if (self.halfMaze - 1, j) not in self.walls]
        else:
            escapeRoutes = [(self.halfMaze, j) for j in range(self.maxHeight) if (self.halfMaze, j) not in self.walls]

        # Return the escape routes
        return escapeRoutes


# Enemy agent class
class EnemyAgent(CaptureAgent):
    # Initialization
    def __init__(self, index, gameState, halfMaze):
        # Initialize the parent class
        CaptureAgent.__init__(self, index)

        # Not accessible for outside
        self.__halfMaze = halfMaze

        # Accessible attributes
        self.counter = 0
        self.enemyCurrentPosition = gameState.getInitialAgentPosition(index)
        self.enemyPreviousPosition = gameState.getInitialAgentPosition(index)
        self.enemyIsWeak = False
        self.enemyIsPacman = False
        self.enemyFoodAttacking = self.getFood(gameState)
        self.enemyFoodDefending = self.getFoodYouAreDefending(gameState)
        self.enemyCapsulesAttacking = self.getCapsules(gameState)
        self.enemyCapsulesDefending = self.getCapsulesYouAreDefending(gameState)
        self.enemyFoodCarrying = 0
        self.registerInitialState(gameState)

    # Initialize the parent class
    def registerInitialState(self, gameState):
        CaptureAgent.registerInitialState(self, gameState)

    # Method that updates all attributes
    def updateData(self, gameState):
        self.enemyPreviousPosition = self.enemyCurrentPosition
        self.enemyCurrentPosition = gameState.getAgentPosition(self.index)
        self.enemyIsWeak = self.getIsWeak(gameState)
        self.enemyIsPacman = self.getIsPacman()
        self.getFoodCarring()
        self.enemyFoodAttacking, self.enemyFoodDefending = self.getEnemyFood(gameState)
        self.enemyCapsulesAttacking = self.getCapsulesAttacking(gameState)

    # Determines if the enemy is weak
    def getIsWeak(self, gameState):
        capsules = self.getCapsulesYouAreDefending(gameState)

        # If the number of capsules changes for the enemy defending, then it is weak
        if len(capsules) != len(self.enemyCapsulesDefending):
            self.counter = 1
            self.enemyCapsulesDefending = capsules
            return True

        # If it died then it is no longer weak
        elif self.enemyIsWeak and 0 < self.counter < 40 and self.getMazeDistance(self.enemyCurrentPosition,
                                                                                   self.enemyPreviousPosition) > 1:
            self.counter = 0
            return False

        # If it is still weak and there are moves left increase counter
        elif self.enemyIsWeak and 0 < self.counter < 40:
            self.counter += 1
            return True

        # If counter pass 40 then it is no longer weak
        elif self.counter >= 40:
            self.counter = 0
            return False

    # Determines if the enemy is pacman
    def getIsPacman(self):
        if (self.red and self.enemyCurrentPosition[0] >= self.__halfMaze) or (
                not self.red and self.enemyCurrentPosition[0] < self.__halfMaze):
            return True

        else:
            return False

    # Gets the food attacking and defending for the enemy
    def getEnemyFood(self, gameState):
        foodMatrix = self.getFood(gameState)
        foodAttack = []

        # Get food attacking
        for x_index, xfood in enumerate(foodMatrix):
            for y_index, yfood in enumerate(foodMatrix[x_index]):
                if yfood:
                    foodAttack.append((x_index, y_index))


        foodMatrix = self.getFoodYouAreDefending(gameState)
        foodDefend = []

        # Get food defending
        for x_index, xfood in enumerate(foodMatrix):
            for y_index, yfood in enumerate(foodMatrix[x_index]):
                if yfood:
                    foodDefend.append((x_index, y_index))

        # Return food
        return foodAttack, foodAttack

    # Get the capsules you are attacking
    def getCapsulesAttacking(self, gameState):
        capsules = [[capsule, self.getMazeDistance(capsule, self.enemyCurrentPosition)] for capsule in
                    self.getCapsules(gameState)]
        capsules.sort(key=lambda x: x[1])

        return capsules

    # Calculate the number of food you are carrying
    def getFoodCarring(self):
        # If in the position of food, increase food carrying
        if self.enemyCurrentPosition in self.enemyFoodAttacking:
            self.enemyFoodCarrying = self.enemyFoodCarrying + 1

        # If reached their side or dead, make food carrying zero
        elif not self.enemyIsPacman or self.getMazeDistance(self.enemyCurrentPosition, self.enemyPreviousPosition) > 1:
            self.enemyFoodCarrying = 0


# Offensive Agent
class OffensiveAgent(BaseAgent):

    # Returns the best action depending on the game state
    def chooseAction(self, gameState):
        # Update the attributes
        self.updateData(gameState)

        # Update the goal
        self.updateGoal()

        # Perform a star search
        action = self.astar()

        # Return action
        return action

    # Performs a star search and returns best action
    def astar(self):
        # Create the queue and push initial state
        astar_queue = util.PriorityQueue()
        astar_queue.push((self.currentPosition, [], 0), 0)
        open_list = {}

        # Create dictionary for the closed list
        closed_list = {}
        currentState = None

        # While the queue is not empty
        while not astar_queue.isEmpty():
            # Pop the state
            currentState = astar_queue.pop()

            # Get successors
            successors = self.getSuccessors(currentState[0])

            # For each successor
            for succ in successors:
                # If the successor is the goal
                if succ[0] == self.goal:
                    # If there is nothing in the current state return the successor's action
                    if len(currentState) <= 0 or len(currentState[1]) <= 0:
                        return succ[1]

                    # Return the first action
                    return currentState[1][0]

                # Calculate g, h and add them
                g = succ[2] + currentState[2]
                h = self.getMazeDistance(succ[0], self.goal)
                f = g + h

                # If the position is in the open list and it has a lower cost, skip
                if succ[0] in open_list.keys() and open_list[succ[0]] < f:
                    continue

                # If the position is in the closest list and it has a lower cost, skip
                elif succ[0] in closed_list.keys() and closed_list[succ[0]] < f:
                    continue

                # Otherwise add it to the queue and the open list
                else:
                    astar_queue.push((succ[0], currentState[1] + [succ[1]], g), f)
                    open_list[succ[0]] = f

            # Add the popped state to the closest list
            closed_list[currentState[0]] = currentState[2]

        # If error, stop
        if len(currentState) <= 0 or len(currentState[1]) <= 0:
            return 'Stop'

        # Return action
        return currentState[1][0]

    # Method that updates the goal
    def updateGoal(self):

        # Get closest food
        closestFood = []
        closestFood4Enemy0 = {}
        closestFood4Enemy1 = {}
        for food in self.foodAttacking:
            closestFood.append([food, self.getMazeDistance(food, self.currentPosition)])
            closestFood4Enemy0[food] = self.getMazeDistance(food, self.enemies[0].enemyCurrentPosition)
            closestFood4Enemy1[food] = self.getMazeDistance(food, self.enemies[1].enemyCurrentPosition)

        closestFood.sort(key=lambda x:x[1])

        # Get closest capsule
        closestCapsules = []
        closestCapsule4Enemy0 = {}
        closestCapsule4Enemy1 = {}
        for capsule in self.capsulesAttacking:
            closestCapsules.append([capsule, self.getMazeDistance(capsule, self.currentPosition)])
            closestCapsule4Enemy0[capsule] = self.getMazeDistance(capsule, self.enemies[0].enemyCurrentPosition)
            closestCapsule4Enemy1[capsule] = self.getMazeDistance(capsule, self.enemies[1].enemyCurrentPosition)

        closestCapsules.sort(key=lambda x:x[1])
        self.closestCapsuleAttack = closestCapsules[0][0] if len(closestCapsules) > 0 else ()

        # Get closest exit
        closestExits = []
        closestExits4Enemy0 = {}
        closestExits4Enemy1 = {}
        for exit in self.escapeRoutes:
            closestExits.append([exit, self.getMazeDistance(exit, self.currentPosition)])
            closestExits4Enemy0[exit] = self.getMazeDistance(exit, self.enemies[0].enemyCurrentPosition)
            closestExits4Enemy1[exit] = self.getMazeDistance(exit, self.enemies[1].enemyCurrentPosition)

        closestExits.sort(key=lambda x:x[1])

        # Get closest capsules defending
        closestCapsulesDefending4Enemy0 = []
        closestCapsulesDefending4Enemy1 = []
        for capsule in self.capsulesDefending:
            closestCapsulesDefending4Enemy0.append([capsule, self.getMazeDistance(capsule, self.enemies[0].enemyCurrentPosition)])
            closestCapsulesDefending4Enemy1.append([capsule, self.getMazeDistance(capsule, self.enemies[1].enemyCurrentPosition)])

        closestCapsulesDefending4Enemy0.sort(key=lambda x:x[1])
        closestCapsulesDefending4Enemy1.sort(key=lambda x:x[1])

        # If there are capsules defending, get the closest to each enemy
        if len(self.capsulesDefending) >= 1:
            self.closestCapsulesDefending4Enemy0 = closestCapsulesDefending4Enemy0[0][0]
            self.closestCapsulesDefending4Enemy1 = closestCapsulesDefending4Enemy1[0][0]

        # Otherwise, assign them to empty tuples
        else:
            self.closestCapsulesDefending4Enemy0 = ()
            self.closestCapsulesDefending4Enemy1 = ()

        # No one is on defense
        if self.enemies[0].enemyIsPacman and self.enemies[1].enemyIsPacman:
            # If no food left
            if len(closestFood) <= 2:
                self.goal = closestExits[0][0]

            # If no food left in our side
            elif len(self.foodDefending) <= 2 and not self.isWeak:
                # Get the key (position) with the smallest value (dist)
                closestExit4Enemy0_Position = min(closestExits4Enemy0, key=closestExits4Enemy0.get)
                closestExit4Enemy1_Position = min(closestExits4Enemy1, key=closestExits4Enemy1.get)

                # If enemy 0 is closer to the exit than enemy 1 then go to enemy 0 otherwise go to enemy 1
                self.goal = self.enemies[0].enemyCurrentPosition if closestExits4Enemy0[closestExit4Enemy0_Position] < closestExits4Enemy1[closestExit4Enemy1_Position] else self.enemies[1].enemyCurrentPosition

            # Otherwise go to closest food
            else:
                self.goal = closestFood[0][0]

        # Enemy 1 is on defense
        elif self.enemies[0].enemyIsPacman and not self.enemies[1].enemyIsPacman:
            bestRatio = []

            # If no food left or we have food carrying: check exit
            if len(closestFood) <= 2 or self.foodCarrying > 0:
                for exit, dist in closestExits:
                    ratio = (dist * 1.0) / (closestExits4Enemy1[exit] + (self.foodCarrying * 5.0)) if (closestExits4Enemy1[exit] + self.foodCarrying) >= 1 else 1000
                    if len(bestRatio) <= 0 or ratio < bestRatio[1]:
                        bestRatio = [exit, ratio]

            # If we have food, check which one is the best to go for
            if len(closestFood) > 2:
                for food, dist in closestFood:
                    ratio = (dist * 1.0) / closestFood4Enemy1[food] if closestFood4Enemy1[food] >= 1 else 1000
                    if len(bestRatio) <= 0 or ratio < bestRatio[1]:
                        bestRatio = [food, ratio]

            # If we have capsules, check which one is the best to go for
            if len(closestCapsules) >= 1:
                for capsule, dist in closestCapsules:
                    ratio = ((dist/5.0) * 1.0) / closestCapsule4Enemy1[capsule] if closestCapsule4Enemy1[
                                                                                 capsule] >= 1 else 1000
                    if ratio < bestRatio[1]:
                        bestRatio = [capsule, ratio]

            ### Goal Assignment

            # If the enemy is weak and we have food get the closest food
            if self.enemies[1].enemyIsWeak and self.enemies[1].counter <= 30 and len(closestFood) > 2:
                self.goal = closestFood[0][0]

            # If we are about to lose go to the enemy
            elif len(self.foodDefending) <= 2 and not self.isWeak:
                self.goal = self.enemies[0].enemyCurrentPosition

            # Otherwise get the best option
            else:
                self.goal = bestRatio[0]

        # Enemy 0 is on defense
        elif not self.enemies[0].enemyIsPacman and self.enemies[1].enemyIsPacman:
            bestRatio = []

            # If no food left or we have food carrying: check exit
            if len(closestFood) <= 2 or self.foodCarrying > 0:
                for exit, dist in closestExits:
                    ratio = (dist * 1.0) / (closestExits4Enemy0[exit] + (self.foodCarrying * 5.0)) if (closestExits4Enemy0[exit] + self.foodCarrying) >= 1 else 1000
                    if len(bestRatio) <= 0 or ratio < bestRatio[1]:
                        bestRatio = [exit, ratio]

            # If we have food, check which one is the best to go for
            if len(closestFood) > 2:
                for food, dist in closestFood:
                    ratio = (dist * 1.0) / closestFood4Enemy0[food] if closestFood4Enemy0[food] >= 1 else 1000
                    if len(bestRatio) <= 0 or ratio < bestRatio[1]:
                        bestRatio = [food, ratio]

            # If we have capsules, check which one is the best to go for
            if len(closestCapsules) >= 1:
                for capsule, dist in closestCapsules:
                    ratio = ((dist/5.0) * 1.0) / closestCapsule4Enemy0[capsule] if closestCapsule4Enemy0[
                                                                                 capsule] >= 1 else 1000
                    if ratio < bestRatio[1]:
                        bestRatio = [capsule, ratio]

            ### Goal Assignment

            # If the enemy is weak and we have food get the closest food
            if self.enemies[0].enemyIsWeak and self.enemies[0].counter <= 30 and len(closestFood) > 2:
                self.goal = closestFood[0][0]

            # If we are about to lose go to the enemy
            elif len(self.foodDefending) <= 2 and not self.isWeak:
                self.goal = self.enemies[1].enemyCurrentPosition

            # Otherwise get the best option
            else:
                self.goal = bestRatio[0]

        # Both are in defense
        else:
            bestRatio = []

            # If no food left or we have food carrying: check exit
            if len(closestFood) <= 2 or self.foodCarrying > 0:
                for exit, dist in closestExits:
                    ratio = (dist * 1.0) / (closestExits4Enemy0[exit] + closestExits4Enemy1[exit] + (self.foodCarrying * 5.0)) \
                        if (closestExits4Enemy0[exit] + closestExits4Enemy1[exit] + self.foodCarrying) >= 1 else 1000

                    if len(bestRatio) <= 0 or ratio < bestRatio[1]:
                        bestRatio = [exit, ratio]

            # If we have food, check which one is the best to go for
            if len(closestFood) > 2:
                for food, dist in closestFood:
                    ratio = (dist * 1.0) / (closestFood4Enemy0[food] + closestFood4Enemy1[food]) \
                            if (closestFood4Enemy0[food] + closestFood4Enemy1[food]) >= 1 else 1000

                    if len(bestRatio) <= 0 or ratio < bestRatio[1]:
                        bestRatio = [food, ratio]

            # If we have capsules, check which one is the best to go for
            if len(closestCapsules) >= 1:
                for capsule, dist in closestCapsules:
                    ratio = ((dist/5.0) * 1.0) / (closestCapsule4Enemy0[capsule] + closestCapsule4Enemy1[capsule]) \
                                if (closestCapsule4Enemy0[capsule] + closestCapsule4Enemy1[capsule]) >= 1 else 1000

                    if ratio < bestRatio[1]:
                        bestRatio = [capsule, ratio]

            ### Goal Assignment

            # If enemies weak, go to nearest food
            if self.enemies[0].enemyIsWeak and self.enemies[1].enemyIsWeak and self.enemies[0].counter <= 30 and self.enemies[1].counter and len(closestFood) > 2:
                self.goal = closestFood[0][0]

            # Otherwise get the best option
            else:
                self.goal = bestRatio[0]

    # Method that gets the successors
    def getSuccessors(self, position):
        # Generate successors
        successors = [[(position[0] + 1, position[1]), 'East', 0.0],
                      [(position[0] - 1, position[1]), 'West', 0.0],
                      [(position[0], position[1] + 1), 'North', 0.0],
                      [(position[0], position[1] - 1), 'South', 0.0]]
        successors = [succ for succ in successors if succ[0] not in self.walls]

        ### Calculate the G value for each successor

        # No one is on defense
        if self.enemies[0].enemyIsPacman and self.enemies[1].enemyIsPacman:
            # For each successor
            for succ in successors:
                # If we are in our territory, prefer paths to pass through the enemy and capsules defending
                if ((succ[0][0] < self.halfMaze and self.red) or (
                        succ[0][0] >= self.halfMaze and not self.red)) and not self.isWeak:
                    g1 = self.getMazeDistance(succ[0], self.enemies[0].enemyCurrentPosition) if self.goal != self.enemies[0].enemyCurrentPosition else 1
                    g2 = self.getMazeDistance(succ[0], self.enemies[1].enemyCurrentPosition) if self.goal != self.enemies[1].enemyCurrentPosition else 1
                    g3 = self.getMazeDistance(succ[0], self.closestCapsulesDefending4Enemy0) if len(
                        self.closestCapsulesDefending4Enemy0) > 0 else 0
                    g4 = self.getMazeDistance(succ[0], self.closestCapsulesDefending4Enemy1) if len(
                        self.closestCapsulesDefending4Enemy1) > 0 else 0

                    succ[2] = g1 + g2 + g3 + g4

                # If we are in our territory and weak, prefer paths away from the enemies
                elif ((succ[0][0] < self.halfMaze and self.red) or (
                        succ[0][0] >= self.halfMaze and not self.red)) and self.isWeak:

                    g1 = self.getMazeDistance(succ[0], self.enemies[0].enemyCurrentPosition)
                    g2 = self.getMazeDistance(succ[0], self.enemies[1].enemyCurrentPosition)

                    if (g1 + g2) <= 0:
                        succ[2] = 1000

                    else:
                        succ[2] = 1.0 / (g1 + g2)

                # Otherwise all moves have the same cost
                else:
                    succ[2] = 1

            # Return successors
            return successors

        # Enemy 1 is on defense
        elif self.enemies[0].enemyIsPacman and not self.enemies[1].enemyIsPacman:
            successors = self.getSuccHelper(successors, 0, 1)
            return successors

        # Enemy 0 is on defense
        elif not self.enemies[0].enemyIsPacman and self.enemies[1].enemyIsPacman:
            successors = self.getSuccHelper(successors, 1, 0)
            return successors

        # Both are in defense
        else:
            for succ in successors:
                # If we are in our territory, all moves have same cost
                if (succ[0][0] < self.halfMaze and self.red) or (succ[0][0] >= self.halfMaze and not self.red):
                    succ[2] = 1

                # Otherwise, we prefer paths away from the enemy, close to an exit, and paths were we can reach before the enemies
                else:
                    g1 = self.getMazeDistance(succ[0], self.closestEscape) if self.goal not in self.escapeRoutes else 1
                    g2 = self.getMazeDistance(succ[0], self.enemies[0].enemyCurrentPosition)
                    g3 = self.getMazeDistance(succ[0], self.enemies[1].enemyCurrentPosition)

                    g4 = self.getMazeDistance(self.enemies[0].enemyCurrentPosition, self.goal) - self.getMazeDistance(succ[0], self.goal)
                    g5 = self.getMazeDistance(self.enemies[1].enemyCurrentPosition, self.goal) - self.getMazeDistance(succ[0], self.goal)

                    g6 = self.getMazeDistance(succ[0], self.closestCapsuleAttack) if len(self.closestCapsuleAttack) > 0 and self.goal != self.closestCapsuleAttack else 0

                    denominator = (g2 * 5.0) + (g3 * 5.0) + g4 + g5
                    if denominator <= 0:
                        succ[2] = 1000

                    else:
                        succ[2] = ((g1 + g6) * 1.0) / denominator

        # return successors
        return successors

    # Method that helps the getSuccessors method
    def getSuccHelper(self, successors, attacker, defender):
        # for each successor
        for succ in successors:
            # If we are in our territory and not weak, prefer paths passing through the enemy and the capsules defending
            if ((succ[0][0] < self.halfMaze and self.red) or (
                    succ[0][0] >= self.halfMaze and not self.red)) and not self.isWeak:
                g1 = self.getMazeDistance(succ[0], self.enemies[attacker].enemyCurrentPosition) if self.goal != self.enemies[attacker].enemyCurrentPosition else 1

                if attacker == 0:
                    g2 = self.getMazeDistance(succ[0], self.closestCapsulesDefending4Enemy0) if len(self.closestCapsulesDefending4Enemy0) > 0 else 0

                else:
                    g2 = self.getMazeDistance(succ[0], self.closestCapsulesDefending4Enemy1) if len(
                        self.closestCapsulesDefending4Enemy1) > 0 else 0

                succ[2] = g1 + g2

            # If we are weak, then prefer paths away from the enemy
            elif ((succ[0][0] < self.halfMaze and self.red) or (
                    succ[0][0] >= self.halfMaze and not self.red)) and self.isWeak:

                g1 = self.getMazeDistance(succ[0], self.enemies[attacker].enemyCurrentPosition)

                if g1 <= 0:
                    succ[2] = 1000

                else:
                    succ[2] = 1.0 / g1

            # Otherwise, prefer paths away from the enemy, close to an exit, and a path were we can reach the goal before the enemy
            else:
                g1 = self.getMazeDistance(succ[0], self.closestEscape) if self.goal not in self.escapeRoutes else 1
                g2 = self.getMazeDistance(succ[0], self.enemies[defender].enemyCurrentPosition)
                g3 = self.getMazeDistance(self.enemies[defender].enemyCurrentPosition, self.goal) - self.getMazeDistance(
                    succ[0], self.goal)

                g4 = self.getMazeDistance(succ[0], self.closestCapsuleAttack) if len(self.closestCapsuleAttack) > 0 and self.goal != self.closestCapsuleAttack else 0

                denominator = (g2 * 5.0) + g3

                if denominator <= 0 or succ[2] == self.enemies[defender].enemyCurrentPosition:
                    succ[2] = 1000

                else:
                    succ[2] = (1.0 * (g1 + g4)) / denominator

        # Return successors
        return successors


# Defensive Agent
class DefensiveAgent(BaseAgent):

    # Returns the best action depending on the game state
    def chooseAction(self, gameState):
        # Update attributes
        self.updateData(gameState)

        # Update the goal
        self.updateGoal()

        # Perform a star search
        action = self.astar()

        # Return action
        return action

    # Method that updates the goal
    def updateGoal(self):
        # Get closest food
        closestFood = []
        closestFood4Enemy0 = {}
        closestFood4Enemy1 = {}
        for food in self.foodAttacking:
            closestFood.append([food, self.getMazeDistance(food, self.currentPosition)])
            closestFood4Enemy0[food] = self.getMazeDistance(food, self.enemies[0].enemyCurrentPosition)
            closestFood4Enemy1[food] = self.getMazeDistance(food, self.enemies[1].enemyCurrentPosition)

        closestFood.sort(key=lambda x:x[1])

        # Get closest capsule
        closestCapsules = []
        closestCapsule4Enemy0 = {}
        closestCapsule4Enemy1 = {}
        for capsule in self.capsulesAttacking:
            closestCapsules.append([capsule, self.getMazeDistance(capsule, self.currentPosition)])
            closestCapsule4Enemy0[capsule] = self.getMazeDistance(capsule, self.enemies[0].enemyCurrentPosition)
            closestCapsule4Enemy1[capsule] = self.getMazeDistance(capsule, self.enemies[1].enemyCurrentPosition)

        closestCapsules.sort(key=lambda x:x[1])
        self.closestCapsuleAttack = closestCapsules[0][0] if len(closestCapsules) > 0 else ()

        # Get closest exit
        closestExits = []
        closestExits4Enemy0 = {}
        closestExits4Enemy1 = {}
        for exit in self.escapeRoutes:
            closestExits.append([exit, self.getMazeDistance(exit, self.currentPosition)])
            closestExits4Enemy0[exit] = self.getMazeDistance(exit, self.enemies[0].enemyCurrentPosition)
            closestExits4Enemy1[exit] = self.getMazeDistance(exit, self.enemies[1].enemyCurrentPosition)

        closestExits.sort(key=lambda x:x[1])

        # Get the closest exit for each enemy
        closestExit4Enemy0_Position = min(closestExits4Enemy0, key=closestExits4Enemy0.get)
        closestExit4Enemy1_Position = min(closestExits4Enemy1, key=closestExits4Enemy1.get)

        self.closestExit4Enemy0_Position = closestExit4Enemy0_Position
        self.closestExit4Enemy1_Position = closestExit4Enemy1_Position

        # Get closest capsules defending
        closestCapsulesDefending4Enemy0 = []
        closestCapsulesDefending4Enemy1 = []
        for capsule in self.capsulesDefending:
            closestCapsulesDefending4Enemy0.append([capsule, self.getMazeDistance(capsule, self.enemies[0].enemyCurrentPosition)])
            closestCapsulesDefending4Enemy1.append([capsule, self.getMazeDistance(capsule, self.enemies[1].enemyCurrentPosition)])

        closestCapsulesDefending4Enemy0.sort(key=lambda x:x[1])
        closestCapsulesDefending4Enemy1.sort(key=lambda x:x[1])

        # If we have capsules defending, create variable of the position of closest capsule
        if len(self.capsulesDefending) >= 1:
            self.closestCapsulesDefending4Enemy0 = closestCapsulesDefending4Enemy0[0][0]
            self.closestCapsulesDefending4Enemy1 = closestCapsulesDefending4Enemy1[0][0]

        # Otherwise assign it to an empty tuple
        else:
            self.closestCapsulesDefending4Enemy0 = ()
            self.closestCapsulesDefending4Enemy1 = ()

        # Both are on offense
        if self.enemies[0].enemyIsPacman and self.enemies[1].enemyIsPacman and not self.isWeak:
            # If we have a lot of food left, go to the closest enemy
            if len(self.foodDefending) >= 10:
                self.goal = self.enemies[0].enemyCurrentPosition if self.getMazeDistance(self.enemies[0].enemyCurrentPosition, self.currentPosition) < self.getMazeDistance(self.enemies[1].enemyCurrentPosition, self.currentPosition) else self.enemies[1].enemyCurrentPosition

            # Otherwise go to the enemy to the closest exit
            else:
                # If enemy 0 is closer to the exit than enemy 1 then go to enemy 0 otherwise go to enemy 1
                self.goal = self.enemies[0].enemyCurrentPosition if closestExits4Enemy0[closestExit4Enemy0_Position] < closestExits4Enemy1[closestExit4Enemy1_Position] else self.enemies[1].enemyCurrentPosition

        # Enemy 0 is on offense, then the goal is to get enemy 0
        elif self.enemies[0].enemyIsPacman and not self.enemies[1].enemyIsPacman and not self.isWeak:
            self.goal = self.enemies[0].enemyCurrentPosition

        # Enemy 1 is on offense, then the goal is to get enemy 1
        elif not self.enemies[0].enemyIsPacman and self.enemies[1].enemyIsPacman and not self.isWeak:
            self.goal = self.enemies[1].enemyCurrentPosition

        # No one is on offense
        else:
            bestRatio = []

            # If no food left or we have food carrying: check exit
            if len(closestFood) <= 2 or self.foodCarrying > 0:
                for exit, dist in closestExits:
                    ratio = (dist * 1.0) / (closestExits4Enemy0[exit] + closestExits4Enemy1[exit] + (self.foodCarrying * 5.0)) \
                        if (closestExits4Enemy0[exit] + closestExits4Enemy1[exit] + self.foodCarrying) >= 1 else 1000

                    if len(bestRatio) <= 0 or ratio < bestRatio[1]:
                        bestRatio = [exit, ratio]

            # If we have food, check which one is the best to go for
            if len(closestFood) > 2:
                for food, dist in closestFood:
                    ratio = (dist * 1.0) / (closestFood4Enemy0[food] + closestFood4Enemy1[food]) \
                        if (closestFood4Enemy0[food] + closestFood4Enemy1[food]) >= 1 else 1000

                    if len(bestRatio) <= 0 or ratio < bestRatio[1]:
                        bestRatio = [food, ratio]

            # If we have capsules, check which one is the best to go for
            if len(closestCapsules) >= 1:
                for capsule, dist in closestCapsules:
                    ratio = ((dist/5.0) * 1.0) / (closestCapsule4Enemy0[capsule] + closestCapsule4Enemy1[capsule]) \
                        if (closestCapsule4Enemy0[capsule] + closestCapsule4Enemy1[capsule]) >= 1 else 1000

                    if ratio < bestRatio[1]:
                        bestRatio = [capsule, ratio]

            ### Goal Assignment

            # If enemies weak and there is food, get the closest food
            if self.enemies[0].enemyIsWeak and self.enemies[1].enemyIsWeak and self.enemies[0].counter <= 30 and self.enemies[1].counter and len(closestFood) > 2:
                self.goal = closestFood[0][0]

            # Otherwise go to the best option
            else:
                self.goal = bestRatio[0]

    # Method that gets the successors
    def getSuccessors(self, position):
        # Generate successors
        successors = [[(position[0] + 1, position[1]), 'East', 0.0],
                      [(position[0] - 1, position[1]), 'West', 0.0],
                      [(position[0], position[1] + 1), 'North', 0.0],
                      [(position[0], position[1] - 1), 'South', 0.0]]
        successors = [succ for succ in successors if succ[0] not in self.walls]

        # Both are on offense
        if self.enemies[0].enemyIsPacman and self.enemies[1].enemyIsPacman:
            for succ in successors:
                # If no food left, just go to the goal (enemy)
                if len(self.foodDefending) <= 2 and not self.isWeak:
                    succ[2] = 1

                # If we are not weak then we are chasing an enemy prefering paths closest to the exits and capsules defending
                elif not self.isWeak:
                    g1 = self.getMazeDistance(succ[0], self.enemies[0].enemyCurrentPosition) if self.goal != self.enemies[
                        0].enemyCurrentPosition else 1
                    g2 = self.getMazeDistance(succ[0], self.enemies[1].enemyCurrentPosition) if self.goal != self.enemies[
                        1].enemyCurrentPosition else 1
                    g3 = self.getMazeDistance(succ[0], self.closestCapsulesDefending4Enemy0) if len(
                        self.closestCapsulesDefending4Enemy0) > 0 else 0
                    g4 = self.getMazeDistance(succ[0], self.closestCapsulesDefending4Enemy1) if len(
                        self.closestCapsulesDefending4Enemy1) > 0 else 0
                    g5 = self.getMazeDistance(succ[0], self.closestExit4Enemy1_Position)
                    g6 = self.getMazeDistance(succ[0], self.closestExit4Enemy0_Position)

                    succ[2] = g1 + g2 + (g3 * 5.0) + (g4 * 5.0) + g5 + g6

                # We are weak and in our territory run away from the enemy
                elif ((succ[0][0] < self.halfMaze and self.red) or (
                        succ[0][0] >= self.halfMaze and not self.red)) and self.isWeak:

                    g1 = self.getMazeDistance(succ[0], self.enemies[0].enemyCurrentPosition)
                    g2 = self.getMazeDistance(succ[0], self.enemies[1].enemyCurrentPosition)

                    if (g1 + g2) <= 0:
                        succ[2] = 1000

                    else:
                        succ[2] = 1.0 / (g1 + g2)

                # On the enemy side, doesn't matter because no one is on defense
                else:
                    succ[2] = 1

            # Return successors
            return successors

        # Enemy 0 is on offense
        elif self.enemies[0].enemyIsPacman and not self.enemies[1].enemyIsPacman:
            successors = self.getSuccHelper(successors, 0, 1)
            return successors

        # Enemy 1 is on offense
        elif not self.enemies[0].enemyIsPacman and self.enemies[1].enemyIsPacman:
            successors = self.getSuccHelper(successors, 1, 0)
            return successors

        # No one is on offense
        else:
            for succ in successors:
                # If we are in our territory, prefers paths to close to the enemy nearest to the boarder
                if (succ[0][0] < self.halfMaze and self.red) or (succ[0][0] >= self.halfMaze and not self.red):
                    succ[2] = self.getMazeDistance(succ[0], self.closestExit4Enemy0_Position) if self.closestExit4Enemy0_Position < self.closestExit4Enemy1_Position else self.getMazeDistance(succ[0], self.closestExit4Enemy1_Position)

                # Prefers paths away from the enemy and paths that make the agent reach the goal before the enemy
                else:
                    g1 = self.getMazeDistance(succ[0], self.closestEscape) if self.goal not in self.escapeRoutes else 1
                    g2 = self.getMazeDistance(succ[0], self.enemies[0].enemyCurrentPosition)
                    g3 = self.getMazeDistance(succ[0], self.enemies[1].enemyCurrentPosition)

                    # Not sure if this would be effective
                    g4 = self.getMazeDistance(self.enemies[0].enemyCurrentPosition, self.goal) - self.getMazeDistance(
                        succ[0], self.goal)
                    g5 = self.getMazeDistance(self.enemies[1].enemyCurrentPosition, self.goal) - self.getMazeDistance(
                        succ[0], self.goal)

                    g6 = self.getMazeDistance(succ[0], self.closestCapsuleAttack) if len(self.closestCapsuleAttack) > 0 and self.goal != self.closestCapsuleAttack else 0

                    denominator = g2 + g3 + g4 + g5

                    if denominator <= 0:
                        succ[2] = 1000

                    else:
                        succ[2] = ((g1 + g6) * 1.0) / denominator

            # Return successors
            return successors

    # Method that helps the getSuccessors method
    def getSuccHelper(self, successors, attacker, defender):
        for succ in successors:
            # If no food, go to the enemy
            if len(self.foodDefending) <= 2 and not self.isWeak:
                succ[2] = 1

            # If not weak, then prefer paths along the capsules defending
            if not self.isWeak:
                if attacker == 0:
                    g1 = self.getMazeDistance(succ[0], self.closestCapsulesDefending4Enemy0) if len(self.closestCapsulesDefending4Enemy0) > 0 else 1
                    g2 = self.getMazeDistance(succ[0], self.closestExit4Enemy0_Position)

                else:
                    g1 = self.getMazeDistance(succ[0], self.closestCapsulesDefending4Enemy1) if len(
                        self.closestCapsulesDefending4Enemy1) > 0 else 1
                    g2 = self.getMazeDistance(succ[0], self.closestExit4Enemy1_Position)

                succ[2] = (g1 * 5.0) + g2

            # If weak go away from the enemy
            elif ((succ[0][0] < self.halfMaze and self.red) or (
                    succ[0][0] >= self.halfMaze and not self.red)) and self.isWeak:

                g1 = self.getMazeDistance(succ[0], self.enemies[attacker].enemyCurrentPosition)

                if g1 <= 0:
                    succ[2] = 1000

                else:
                    succ[2] = 1.0 / g1

            # Otherwise prefer paths closest to the exit, away from the enemy, and paths that you'll get there before the enemy
            else:
                g1 = self.getMazeDistance(succ[0], self.closestEscape) if self.goal not in self.escapeRoutes else 1
                g2 = self.getMazeDistance(succ[0], self.enemies[defender].enemyCurrentPosition)
                g3 = self.getMazeDistance(self.enemies[defender].enemyCurrentPosition, self.goal) - self.getMazeDistance(
                    succ[0], self.goal)

                g4 = self.getMazeDistance(succ[0], self.closestCapsuleAttack) if len(self.closestCapsuleAttack) > 0 and self.closestCapsuleAttack != self.goal else 0

                denominator = g2 + g3

                if denominator <= 0:
                    succ[2] = 1000

                else:
                    succ[2] = (1.0 * (g1 + g4)) / denominator

        # Return successors
        return successors

    # Performs a star search and returns best action
    def astar(self):
        # Create the queue and push initial state
        astar_queue = util.PriorityQueue()
        astar_queue.push((self.currentPosition, [], 0), 0)
        open_list = {}

        # Create dictionary for the closest list
        closed_list = {}
        currentState = None

        # While the queue is not empty
        while not astar_queue.isEmpty():
            # Pop the state
            currentState = astar_queue.pop()

            # Get successors
            successors = self.getSuccessors(currentState[0])

            # For each successor
            for succ in successors:
                # If the successor is the goal
                if succ[0] == self.goal:
                    # If there is nothing in the current state return the successor's action
                    if len(currentState) <= 0 or len(currentState[1]) <= 0:
                        return succ[1]

                    # Return the first action
                    return currentState[1][0]

                # Calculate g, h and add them
                g = succ[2] + currentState[2]
                h = self.getMazeDistance(succ[0], self.goal)
                f = g + h

                # If the position is in the open list and it has a lower cost, skip
                if succ[0] in open_list.keys() and open_list[succ[0]] < f:
                    continue

                # If the position is in the closest list and it has a lower cost, skip
                elif succ[0] in closed_list.keys() and closed_list[succ[0]] < f:
                    continue

                # Otherwise add it to the queue and the open list
                else:
                    astar_queue.push((succ[0], currentState[1] + [succ[1]], g), f)
                    open_list[succ[0]] = f

            # Add the popped state to the closest list
            closed_list[currentState[0]] = currentState[2]

        # If error, stop
        if len(currentState) <= 0 or len(currentState[1]) <= 0:
            return 'Stop'

        # Return action
        return currentState[1][0]


