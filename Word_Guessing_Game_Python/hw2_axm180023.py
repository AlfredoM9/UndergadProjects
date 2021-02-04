# Author: Alfredo Mejia
# Class : CS 4395.001
# Date  : 9/5/2020
# Descrp: This program follows closely the instructions given in the description for
#         homework 2. This program is going to accept one system argument as the path
#         to a text file. If an incorrect number of arguments is passed or if the path
#         is incorrect an error message will appear and the program will terminate. The
#         file will be read and a function will be called to calculate its lexical diversity.
#         Minimal preprocessing will occur such as removing the punctuation and the lexical
#         diversity will be printed. Then another function will be called that will preprocess
#         the data according to the instructions and return all the tokens and nouns in the text.
#         Another function will accept these objects as arguments and create a dictionary of the noun
#         and its count appearance in the file. Any printing functions specified in the directions will be
#         executed. The 50 most common used nouns will be used as part of a guessing game. The user
#         must guess the word by specifying a letter each iteration. Depending on the correctness of the
#         guess the user will accumulate points or lose points. The game is over until the user has
#         negative points or the user terminates the program.
#

# Imports
import sys
from nltk import word_tokenize
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
import nltk
from random import randint
from random import seed


# Descr: This is the main function. It will first validate if the correct number of arguments were passed. If not,
# an error message will appear. The program will try to open the file and if the path is incorrect it will catch
# the error and print a message. The program will call four functions, lexical diversity function that will calculate
# the lexical diversity and print it. This function doesn't return anything. The preprocess text function will
# preprocess the text according to the instructions and return the tokens and the nouns of the file. The get
# common nouns will return the most common nouns and the guessing game will use the common nouns to start the game.
def main():
    # If invalid number of arguments -> exit the program
    if len(sys.argv) != 2:
        sys.exit('Invalid number of arguments')

    # Try to open the file and read it
    try:
        file = open(sys.argv[1], 'r')
        raw_text = file.read()
        file.close()

    # If unable to read file, display error message, and exit the program
    except OSError:
        print('An error as occurred. Please make sure the path is properly being passed.')
        sys.exit()

    # Call functions that executes the instructions in hw2
    lexical_diversity(raw_text)  # Part 2 (calculate lexical diversity)
    tokens, nouns = preprocess_text(raw_text)  # Part 3 (preprocess text)
    common_nouns = get_common_nouns(tokens, nouns)  # Part 4 (get most common nouns)
    guessing_game(common_nouns)  # Part 5 (start game)


# Descr: Calculate and print lexical diversity
def lexical_diversity(raw_text):
    # Tokenize and preprocess
    tokens = word_tokenize(raw_text)
    tokens = [word.lower() for word in tokens if word.isalpha()]

    # Print lexical diversity formatted to 2 decimal places
    print('\nLexical Diversity: %.2f' % (len(set(tokens)) / len(tokens)))


# Descr: This function will preprocess the text according to the instructions
# specified in part 3 a, b, c, d and execute part e and f. It will get the
# unique lemmas from the file, do pos tagging on the unique lemmas, then
# get only the nouns of those lemmas. Then it will return the whole tokens
# and the nouns found.
def preprocess_text(raw_text):
    # Preprocess raw text
    tokens = word_tokenize(raw_text)  # Part 3.A
    tokens = [word.lower() for word in tokens if word.isalpha() and  # Part 3.A
              word not in stopwords.words('english') and len(word) > 5]
    # Lemmatize tokens
    wnl = WordNetLemmatizer()
    lemmas = [wnl.lemmatize(word) for word in tokens]  # Part 3.B
    # Get unique Lemmas
    unique_lemmas = set(lemmas)  # Part 3.B
    # Get tags
    tags = nltk.pos_tag(unique_lemmas)  # Part 3.C
    print('\nFirst 20 Tagged Items: \n')
    print(tags[:20])  # Part 3.C
    # Get nouns
    nouns = [word[0] for word in tags if word[1].startswith('N')]  # Part 3.D
    print('\nNumber of tokens: ' + str(len(tokens)))  # Part 3.E
    print('\nNumber of nouns: ' + str(len(nouns)))  # Part 3.E

    # return tokens and nouns
    return tokens, nouns  # Part 3.F


# Descr: This function will create a dictionary from the nouns and its count of appearance in the
# list of tokens. The function will sort this dictionary based on the count and print the
# 50 most common words. Then the 50 most common nouns will then be converted into a list.
# The list will then be returned
def get_common_nouns(tokens, nouns):
    # Create dictionary
    noun_counts = {noun: tokens.count(noun) for noun in nouns}
    # Sort dictionary
    noun_counts = sorted(noun_counts.items(), key=lambda x: x[1], reverse=True)
    # Validation
    if len(noun_counts) < 50:
        sys.exit('Error. The number of nouns in the text is less than 50.')
    # Print 50 most common nouns in the file
    print('\n50 Most Common Nouns: ')
    print(noun_counts[:50])
    # Convert 50 most common nouns to a list
    common_nouns = [n[0] for n in noun_counts[:50]]
    # Return list
    return common_nouns


# Descr: This function will initiate the guessing game. The function will randomly choose
# a word from the most common nouns and the user is prompted to guess the word by inserting
# a single letter with each iteration. If the letter is inside the word then the user will
# get one point and the letters inside the word will be shown with that letter. If the letter is
# not inside the word then the user will lose a point. If the user guesses all the letters right
# another word will be chosen. The program ends until the user gets a negative score or the user
# ends the program.
def guessing_game(common_nouns):
    seed(1234)
    # Print rules
    print_rules()
    # Initialize score, user input history, and new word boolean
    # to indicate if a new word is to be chosen
    score = 5
    user_history = []
    new_word = True

    # Repeat until score is negative
    while score >= 0:
        # If new word is needed get new random noun
        if new_word:
            word_guess = common_nouns[randint(0, 49)]
            new_word = False

        # Keeps track if user guessed all letters correctly
        finished = 0

        # Print each letter. If the user hasn't guessed it show _
        # Otherwise show the letter
        for i in word_guess:
            if i in user_history:
                finished += 1
                print(i, end=" ")
            else:
                print('_', end=" ")

        # If the user guessed all the letters
        # Show message and restart the game
        if finished == len(word_guess):
            print('\nYou solved it!')
            print('\nCurrent Score: ' + str(score))
            print('Guess another word: ')
            new_word = True
            user_history = []
            continue

        # Get user input
        user_input = input('\nGuess a letter: ')
        user_input = user_input[:1]
        user_input = user_input.lower()

        # If previously inserted then alert the user
        if user_input in user_history:
            print('This letter was previously entered. Try again.')

        # If guess correctly, add a point, and alert user
        elif user_input in word_guess and len(user_input) == 1:
            score += 1
            print('Right! Score is now: ' + str(score))

        # Exit program
        elif user_input == '!':
            print('\nFinal Score: ' + str(score))
            break

        # Otherwise, guessed incorrectly, user loses a point
        else:
            score -= 1
            print('Sorry, guess again. Score is now: ' + str(score))

        user_history.append(user_input)

    # If the user loses show the word the user couldn't guess
    if score < 0:
        print('\nYou lost! The word was: ' + word_guess)

    print('\nThanks for playing. Hope you enjoyed it.')


# Descr: Simply prints the rules to the game
def print_rules():
    print('\nLet\'s play a guessing game!')
    print('\nHere are the rules:')
    print('\t1. A word is going to be chosen from the most common nouns. You must guess the word.\n'
          '\t2. To guess the word a single letter must be entered. The word does not contain punctuation.\n'
          '\t3. You start with 5 points. If you guess a letter correctly you get one point.\n'
          '\t4. If you guess the letter incorrectly you lose a point.\n'
          '\t5. If you finished guessing the whole word then another word would be chosen and the game repeats.\n'
          '\t6. The game ends until you reach -1 points or you enter the character \'!\'.\n'
          '\n'
          'Note: This game only accepts one letter at a time. If a multiple characters or single non-alpha '
          'characters are inserted the first letter found in the string will be counted as the input. If no letter is '
          'found then it would be an automatic point deduction. If a repeated letter is inserted then a message would '
          'appear and the score will remain unaffected.')
    print('\nAlright. Let\'s begin!')
    print('\nYour Score: 5\n')


# Point of start of the program
if __name__ == '__main__':
    main()
