#include "HangmanWord.h"

//Defining static vectors
std::vector<std::string> HangmanWord::easyWords;
std::vector<std::string> HangmanWord::mediumWords;
std::vector<std::string> HangmanWord::hardWords;

/*
Description:   The default constructor for the HangmanWord class
*/
HangmanWord::HangmanWord(Difficulty selectedDifficulty)
{
   difficulty = selectedDifficulty;

   //Seed the random number generator
   srand(static_cast<unsigned int>(time(0)));

   //Randomly select a word based on chosen difficulty. The appropriate word file will be opened if it has not yet been read
   switch (difficulty)
   {
   case EASY:
      //If the easy vector hasn't been filled yet, then read the easy word file
      if (HangmanWord::easyWords.empty())
      {
         readWordFile(EASY_WORDS_FILE_PATH, HangmanWord::easyWords);
      }

      //Once vector has been filled, randomly assign the word member to a value from the easyWords vector
      word = HangmanWord::easyWords.at(rand() % HangmanWord::easyWords.size());
      break;
   case MEDIUM:
      //If the medium vector hasn't been filled yet, then read the medium word file
      if (HangmanWord::mediumWords.empty())
      {
         readWordFile(MEDIUM_WORDS_FILE_PATH, HangmanWord::mediumWords);
      }

      //Once vector has been filled, randomly assign the word member to a value from the mediumWords vector
      word = HangmanWord::mediumWords.at(rand() % HangmanWord::mediumWords.size());
      break;
   case HARD:
      //If the hard vector hasn't been filled yet, then read the hard word file
      if (HangmanWord::hardWords.empty())
      {
         readWordFile(HARD_WORDS_FILE_PATH, HangmanWord::hardWords);
      }

      //Once vector has been filled, randomly assign the word member to a value from the hardWords vector
      word = HangmanWord::hardWords.at(rand() % HangmanWord::hardWords.size());
      break;
   }
   
} //end constructor

/*
Description:   Reads each word from the given file into the given vector. Used for loading the 
               word files into memory
Input:         wordFilePath:
               The path to the word file to be opened.
               words:
               A reference to the member vector to fill with the words from the word file.
               Passed by reference to simplify implementation.
*/
void HangmanWord::readWordFile(std::string wordFilePath, std::vector<std::string> &words)
{
   std::ifstream wordFile;    //The word file to open
   std::string currentWord;   //The word currently being read from the word file

   //Attempt to open the file and validate that it opened correctly
   wordFile.open(wordFilePath);

   if (!wordFile)
   {
      throw std::runtime_error("Could not open file \"" + wordFilePath + "\".");
   }

   //If the file opened correctly, then iterate through each word in the file and put it into the given vector
   while (wordFile >> currentWord)
   {
      words.push_back(currentWord);
   }

   wordFile.close();
} //end function readWordFile