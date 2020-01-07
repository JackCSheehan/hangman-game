#ifndef HANGMAN_WORD_H
#define HANGMAN_WORD_h

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "Difficulty.h"

/*
The HangmanWord class, when instantiated, automatically selects a word to be used in the next game.
Word lists compiled from:
                  wiktionary.org
                  ef.edu
                  wordfinder.yourdictionary.com
                  dictionary.com
*/
class HangmanWord
{
private:
   std::string word;                               //The word to use in the next game
   Difficulty difficulty;                          //The selected difficulty

   static std::vector<std::string> easyWords;      //Easy words that have been loaded from the easy words file
   static std::vector<std::string> mediumWords;    //Medium words that have been loaded from the medium words file
   static std::vector<std::string> hardWords;      //Hard words that have been loaded from the easy words file

   //Word file paths
   const std::string EASY_WORDS_FILE_PATH = "res/easy_words.txt";
   const std::string MEDIUM_WORDS_FILE_PATH = "res/medium_words.txt";
   const std::string HARD_WORDS_FILE_PATH = "res/hard_words.txt";

   void readWordFile(std::string, std::vector<std::string>&);

public:
   HangmanWord(Difficulty);

   //Getter
   std::string getWord() const { return word;  }

   //Setter
   void setWord(std::string w) { word = w; }

};

#endif

