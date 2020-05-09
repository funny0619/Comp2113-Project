#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <unistd.h>
#include "functions.h"


/*
  Function Memorizing does not take inputs.
  Function output: An integer (0 is lose; 1 is small prize; 2 is medium prize; 3 is big prize; 5 is quit game)
  What the function does: The function generates a memorizing game.
  It first asks for the user's consent for playing the game.
  Then it requests for the number of characters the user wants to attempt to memorize.
  Then the system randomly generates the characters, and clears the screen after 2 seconds.
  Then it asks for  user's input to enter the character in the exact same order. The user can make 5 mistakes max.
  A prize is given if the user memorized it correctly. 
  Depending on the character length, the reward may be small, medium or big.
*/

int Memorizing() {
	std::string decision;
	std::cout << "Play Memorize Bananza? (Y/N) ";
	std::cin >> decision;
	while(!(decision == "N" || decision == "n" || decision == "Y" || decision == "y")) {
	  std::cout << "Please input valid response" << std::endl;
	  std::cout << "Play Memorize Bananza? (Y/N)" << std::endl;
	  std::cin >> decision;
  }
  if (decision == "N" || decision == "n") {
  	return 5;
  }

	int attempts = 5;
	int seconds = 2;
	int number_of_char = 0;
	std::cout << "The following challenge tests your memorizing skills! Please enter the number of characters you want to attempt: ";
	std::cin >> number_of_char;
	while(number_of_char < 1 || std::cin.fail()) {
		std::cin.clear();
    std::cin.ignore(10000, '\n');
	  std::cout << "Please input valid number of characters ";
	  std::cin >> number_of_char;
  }
	std::cout << "You will now be shown " << number_of_char << " symbols for " << seconds << " SECONDS, then enter the symbols in the same order!" << std::endl;
	std::cout << "Press 'S' to start the game: ";
	std::cin >> decision;
	while(!(decision == "S" || decision == "s")) {
	  std::cout << "Please input valid response" << std::endl;
	  std::cout << "Press 'S' to start the game: " << std::endl;
	  std::cin >> decision;
  }

	std::srand(time(0));
	char char_pool[] = {"abcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*+=?{}[]-<>/"};  
	char * symbols = new char [number_of_char];
	char * playerInput = new char [number_of_char];

	for (int i = 0; i < number_of_char; ++i) {
		//generate a random char for each symbols[i]
		symbols[i] = char_pool[std::rand()%55];
	
		//make output appear for a limited time
	}
  for (int i = 0; i < number_of_char; ++i) {
    std::cout << symbols[i] << " ";
  }
  std::cout << std::endl;
  sleep(seconds);
  system("clear");//change this to system("clear"); on linux machine

	for (int i = 0; i < number_of_char; ++i) {
		//ask for user input
		std::cin >> playerInput[i];
		while ((playerInput[i] != symbols[i]) && attempts > 0) {
			--attempts;
			std::cout << "This is the wrong symbol! You have " << attempts << " chances left!" << std::endl;
			std::cin >> playerInput[i];
		}
		if (attempts < 1) {
			std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "You're memorizing skills are horrible" << std::endl;
			return 0;
			break;
		}
	}

	if (attempts > 0) {
		std::cin.clear();
    std::cin.ignore(10000, '\n');
		if(number_of_char <= 4) {
      std::cout << "You win a small prize!" << std::endl;
			return 1;
    }
		else if(number_of_char > 4 && number_of_char <= 7) {
      std::cout << "You win a medium prize!" << std::endl;
			return 2;
    }
		else if(number_of_char >= 8) {
      std::cout << "You win a big prize!" << std::endl;
			return 3;
    }
	}

	return 5;
	delete [] symbols;
	delete [] playerInput;
}