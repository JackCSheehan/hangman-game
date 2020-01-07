#include "Hangman.h"

//Defining static vectors
std::vector<std::string> HangmanWord::easyWords;
std::vector<std::string> HangmanWord::mediumWords;
std::vector<std::string> HangmanWord::hardWords;

/*
Description:   Constructor for the Hangman class
*/
Hangman::Hangman()
{
   //The default difficulty is medium; initialized here to prevent accidental stale member variables if the difficulty menu is forgotten
   difficulty = MEDIUM;
   missesLeft = MEDIUM;

} //end constructor

/*
Description:   Displays a brief tutorial explaining how the game is played.
*/
void Hangman::displayTutorial()
{
   std::cout << "~Welcome to Hangman!~\n\n"
      << "- Guess the word before you run out of misses\n"
      << "- You can guess either single characters or the entire word\n"
      << "- Select from three different difficulties\n"
      << "- Guesses are not case sensitive and no words have any spaces in them\n\n";
} //end function displayTutorial

/*
Description:   Displays the menu that lets the user choose a difficulty. Will assign the difficulty
               and misses left member variables.
*/
void Hangman::displayDifficultyMenu()
{
   //Difficulty menu choices
   static const int EASY_CHOICE = 1;
   static const int MEDIUM_CHOICE = 2;
   static const int HARD_CHOICE = 3;

   int choice; //The user's choice

   std::cout << "Please select a difficulty:\n"
      << "1) Easy\n\t(Short, simple words, " << EASY << " misses)\n"
      << "2) Medium\n\t(Longer, more complicated words, " << MEDIUM << " misses)\n"
      << "3) Hard\n\t(Much harder, longer words, " << HARD << " misses)\n\n";

   //Get the user's menu input
   std::cin >> choice;

   //Clear error state and clear keyboard buffer in the event of junk input
   std::cin.clear();
   std::cin.ignore(INT_MAX, '\n');

   //Validate the users input and re-prompt until valid input is received
   while (choice < 1 || choice > 3)
   {
      system("cls");
      std::cout << "Invalid input \"" << choice << "\"! Please make sure your input is between " << EASY_CHOICE << " and " << HARD_CHOICE << " (inclusive)\n\n"
         << "1) Easy\n\t(Short, simple words, " << EASY << " misses)\n"
         << "2) Medium\n\t(Longer, more complicated words, " << MEDIUM << "misses)\n"
         << "3) Hard\n\t(Much harder, longer words, " << HARD << " misses)\n\n";

      std::cin >> choice;
   }

   //Assign difficulty and misses left based on the user's choice
   switch (choice)
   {
   case EASY_CHOICE:
      difficulty = EASY;
      missesLeft = EASY;
      break;
   case MEDIUM_CHOICE:
      difficulty = MEDIUM;
      missesLeft = MEDIUM;
      break;
   case HARD_CHOICE:
      difficulty = HARD;
      missesLeft = HARD;
      break;
   }

   //Instantiate a new HangmanWord object to set the target word for this game
   HangmanWord word(difficulty);

   targetWord = word.getWord();

   //Dynamically allocate a new character array to hold the user's responses
   userGuess = new char[targetWord.size()]{ 0 };

} //end function displayDifficultyMenu

/*
Description:   Clears the screen, displays the hangman art, and displays the game info
*/
void Hangman::displayGameInfo()
{
   //Display hangman art
   system("cls");

   std::cout << "  ___________  \n"
             << "  |/       |   \n"
             << "  |        0   \n"
             << "  |       /|\\ \n"
             << "  |        |   \n"
             << "  |       / \\ \n"
             << "  |            \n"
             << "__|__          \n";

   //Display game information
   std::cout << "You have " << missesLeft << " misses left\n\n";

   //Iterate through the user guess and display '_' for letters that haven't been guessed yet
   for (unsigned int letterCount = 0; letterCount < targetWord.length(); letterCount++)
   {
      if (userGuess[letterCount] == 0)
      {
         std::cout << "_ ";
      }
      else
      {
         std::cout << userGuess[letterCount] << " ";
      }
   }

   std::cout << "\n";
} //end function displayHangmanArt

/*
Description:   Checks to see if the given character is a character in the target word.
Input:         character:
               The character that will be searched for in the target word
*/
bool Hangman::isCharacterInTargetWord(char character)
{
   bool wasCharacterFound = false;  //Keeps track of whether or not the passed character was found in the target word

   //Set character to be lowercase so that user input is not case sensitive
   character = std::tolower(character);

   //Iterate through each character in the target word and set the passed character to the corresponding value in the user guess array
   for (unsigned int letterCount = 0; letterCount < targetWord.length(); letterCount++)
   {
      if (targetWord[letterCount] == character)
      {
         userGuess[letterCount] = character;
         wasCharacterFound = true;
      }
   }

   return wasCharacterFound;
} //end function isCharacterInTargetWord

/*
Description:   Used as a win condition in the main game loop to see if the user has won.
Return:        Returns true if the user has won and false if the user has not won.
*/
bool Hangman::hasUserWon()
{
   //Iterate through each character in the user guess
   for (unsigned int letterCount = 0; letterCount < targetWord.length(); letterCount++)
   {
      //If there is still a 0 in the user guess array, then the user has not won
      if (userGuess[letterCount] == 0)
      {
        return false;
      }
   }
   return true;
} //end function hasUserWon

/*
Description:   Gets the user's input and processes it. The user can either
               guess a single character and it will be added to their
               list of known characters or they can enter an entire word
               to try to guess the word itself.
Return:        Returns the character the user guessed if it was within
               the target word, returns -1 if the user guessed the entire
               word correctly, and returns -2 if the user didn't guess a
               character or the word correctly
*/
char Hangman::getInput()
{
   std::string input;   //The user's input

   std::cin >> input;

   //Clear error state and clear keyboard buffer in the event of junk input
   std::cin.clear();
   std::cin.ignore(INT_MAX, '\n');

   //Set the user's input to lowercase so that the game is not case sensitive
   input = stringToLower(input);

   //If the user typed more than one character
   if (input.length() != 1)
   {
      //If the user guessed the target word correctly, return -1
      if (input == targetWord)
      {
         return -1;
      }
   }
   else if (isCharacterInTargetWord(input[0]))
   {
      return input[0];
   }

   //If the user didn't guess the word or a character correctly, return -2
   return -2;
} //end function getInput

/*
Description:   Resets the member variables so that the game may be played again.
*/
void Hangman::resetGame()
{
   //Free the memory for userGuess from last game
   delete [] userGuess;
} //end function resetGame


/*
Description:   Changes the given string to a string of all lowercase characters.
Input:         str:
               The string that will be converted to all lowercase
Return:        Returns the given string in all lowercase
*/
std::string Hangman::stringToLower(std::string str)
{
   for (char& character : str)
   {
      character = std::tolower(character);
   }
   return str;
} //end function stringToLower

/*
Description:   Shows a menu that asks the user if they want to play again and gets their input.
Input:         gameLoopControl:
               A reference to the variable used to control the main game loop; if the user wants to
               play again, this reference will be set to true so that the main game loop will run
               again.
*/
void Hangman::displayPlayAgainMenu(bool &gameLoopControl)
{
   char playAgain;

   //Prompt user if they want to play again and get the input
   std::cout << "Play again? (y/n): ";
   std::cin >> playAgain;

   //Clear error state and clear keyboard buffer in the event of junk input
   std::cin.clear();
   std::cin.ignore(INT_MAX, '\n');

   //Lowercase the user's input so that it is not case sensitive
   playAgain = std::tolower(playAgain);

   //Validate the user's input and re-prompt
   while (playAgain != 'y' && playAgain != 'n')
   {
      std::cout << "Invalid option.\n";
      std::cout << "Play again? (y/n): ";
      std::cin >> playAgain;
   }

   //If the user wants to play again
   if (playAgain == 'y')
   {
      //Reset game and restart input loop
      resetGame();
      gameLoopControl = true;

      //Clear screen before new game starts
      system("cls");

      displayDifficultyMenu();

      displayGameInfo();
   }
   else
   {
      std::cout << "Goodbye!\n";
      exit(EXIT_SUCCESS);
   }
} //end function displayPlayAgainMenu

/*
Description:   Displays all the messages and runs all the functions associated with the user winning
               a game.
*/
void Hangman::runWinProcedure()
{
   //Set the user guess array to read the target word so that the word displays when the user guesses it
   for (unsigned int letterCount = 0; letterCount < targetWord.length(); letterCount++)
   {
      userGuess[letterCount] = targetWord[letterCount];
   }

   displayGameInfo();
   std::cout << "\n\nCongratulations! You win!\n";
} //end function runWinProdedure

/*
Description:   Displays all the messages and runs all the functions associated with the user
               losing a game.
*/
void Hangman::runLossProcedure()
{
   displayGameInfo();

   //Display loss messages
   std::cout << "\n\nSorry! You lost!\n";
   std::cout << "The word was " << targetWord << "\n";
} //end function runLossProdedure

/*
Description:   Display's the Hangman board as well as the portion of the target word that the
               user has guessed.
*/
void Hangman::display()
{
   bool running = true; //Game loop control variable

   //Display a tutorial the first game
   displayTutorial();

   //Display initial difficulty menu
   displayDifficultyMenu();

   //Initial display of the hangman art
   displayGameInfo();

   while (running)
   {
      displayGameInfo();

      //Check loss condition
      if (missesLeft == 0)
      {
         //End the input loop and run loss procedure
         running = false;

         runLossProcedure();

         displayPlayAgainMenu(running);
      }
      //Check the win condition
      else if (hasUserWon())
      {
         //End the input loop and run win procedure
         running = false;

         runWinProcedure();

         displayPlayAgainMenu(running);
      }

      //Get the user's input and process the result
      char inputResult = getInput();

      //If the user guessed the whole word correctly
      if (inputResult == -1)
      {
         //End the input loop and display the win message
         running = false;

         runWinProcedure();

         displayPlayAgainMenu(running);

      } //end if
      //If the user didn't guess the word or character right
      else if (inputResult == -2)
      {
         --missesLeft;
      }
      //If the user correctly guessed a character, then the isCharacterInTargetWord already handled the userGuess array
   }
} //end function displays