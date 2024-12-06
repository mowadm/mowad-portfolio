# Michael Mowad
# Project 6
# Simple hangman game given a word list file

import random

# global variable of longest word length
maxLength = 0

# loadFile
# given file name loads a word list into a dictionary
def loadFile(name):
    try:
        # open file
        global maxLength
        file = open(name, 'r')
        line = file.readline()

        # dictionary of lists
        dictionary = dict()

        # while line is not blank, read line and append to appropriate list
        while line != '':
            # get word length
            word = line.rstrip('\n').lower()
            length = len(word)
            # if word length not in dictionary then add
            if length not in dictionary:
                dictionary[length] = []
            # add word to appropriate list
            dictionary[length].append(word)

            # update max length
            if length > maxLength:
                maxLength = length

            line = file.readline()

        # close file and return the dictionary
        file.close()
        return dictionary
    except:
        print("Error loading file. Exiting program...")
        exit()



def main():
    # load dictionary
    dictionary = loadFile('wordlist.txt')

    while True:
        # introduce user and get valid input
        print('\nWelcome to Hangman')
        while True:
            wordLength = input(f"What world length would you like to play (3 to {maxLength}) ==> ")
            try:
                wordLength = int(wordLength)
            except ValueError:
                print("Please enter an integer")
                continue

            if 3 <= wordLength <= maxLength:
                break
            else:
                print(f"Please enter a number from 3 to {maxLength}")

        # randomly select word from word length list
        wordList = dictionary[wordLength]
        index = random.randint(0, len(wordList) - 1)
        word = wordList[index]

        # create censored string reflecting word
        revealed = []
        for index in range(wordLength):
            revealed.append('*')

        # initialize guesses and list of guesses
        guesses = (2 * wordLength - 1)
        guessedList = []

        while True:

            # Check that the user has remaining guesse
            if guesses == 0:
                print("Game Over! You've run out of guesses")
                print(f"The word was: {word}")
                break

            # Print revealed word so far and prompt for guess
            print(f"\n{''.join(revealed)}")
            print(f"You have {guesses} guesses remaining")
            guess = input("Type a letter or a word to guess: ")

            # if guess is not in terms of alphabet, reprompt
            if not guess.isalpha():
                print("Please enter a valid letter or word")
                continue

            # check if guess has already been tried, if not add to list
            if guess in guessedList:
                print(f"You already guessed {guess} please try another letter/word")
                continue
            else:
                guessedList.append(guess)

            # letter handling
            if len(guess) == 1:
                total = 0
                # check each index of word for guessed letter.
                # if present, increment total found and reveal letter
                for index in range(wordLength):
                    if guess == word[index]:
                        total += 1
                        revealed[index] = guess

                # print number of letters found
                print(f"There are {total} '{guess}'s!")

                # if no more '*' are remaining, all letters have been found and user wins
                if '*' not in revealed:
                    print("Congratulations! You completed the word")
                    break

            # word handling
            elif 3 <= len(guessedList) <= maxLength:
                # if guess is correct, user wins
                if guess == word:
                    print(f"Congratulations! You guessed the word")
                    break
                else:
                    print(f"Sorry {guess} was not the word.")
            # invalid input
            else:
                print("Please enter either a single letter or a valid word")
                continue
            # Decrement guesses
            guesses -= 1


main()
