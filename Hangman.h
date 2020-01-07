#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <climits>
#include "HangmanWord.h"

/*
The hangman class contains all of the functionality and display functions necessary to play a game of hangman.
The actual words are chosen randomly by the HangmanWord class.
*/
class Hangman
{
private:
   std::string targetWord;       //The target word that users try to guess
   char *userGuess;              //An array of characters that holds the letters the user has guessed so far; NOT a C-string as no space is allocated for \0
   int missesLeft;               //The number of misses the user has left before the game ends
   bool hasWordBeenGuessed;      //Keeps track of whether or not the user has guessed the target word
   Difficulty difficulty;        //The difficulty selected by the user

   void displayTutorial();
   void displayDifficultyMenu();
   void displayGameInfo();
   bool isCharacterInTargetWord(char);
   bool hasUserWon();
   char getInput();
   void resetGame();
   std::string stringToLower(std::string);
   void displayPlayAgainMenu(bool &);
   void runWinProcedure();
   void runLossProcedure();

public:
   Hangman();
   ~Hangman() { delete [] userGuess; };

   void display();

   //Getters
   std::string getTargetWord() const { return targetWord; }
   char* getUserGuess() const { return userGuess; }
   int getMissesLeft() const { return missesLeft; }
   bool getHasWordBeenGuessed() const { return hasWordBeenGuessed; }
   Difficulty getDifficulty() const { return difficulty; }

   //Setters
   void setTargetWord(std::string tw) { targetWord = tw; }
};

#endif
