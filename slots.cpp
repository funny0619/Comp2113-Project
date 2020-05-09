#include <iostream>
//#include <windows.h>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "functions.h"
//0 is lose
//1 is small prize
//2 is medium prize
//3 is big prize


/*
Function RewardCheck input: char of slot1, char of slot2, char of slot3

Function output: integer value of 2 represents JackPot, integer value of 1 represents medium win
integer value of 0 represents no winnings

What the Function does: checks what tier of win slots has generated, so reward tier can be generated
*/
int RewardCheck(char slot1, char slot2, char slot3) {
  if (slot1 == slot2 || slot2 == slot3 || slot3 == slot1) {
    if (slot1 == slot2 && slot2 == slot3 && slot3 == slot1) {
      return 2;
    }
    return 1;
  }
  return 0;
}
/*
Function SlotInterface input: struct of type Character

Function output: an integer representing big,small,win,lose
0 is lose
2 is medium prize
3 is big prize

What the Function does: the function chooses randmly from the a given array of symboles represted by string.
the function randomly chooses 3 times. 
if more than 2 symbols are the same, the player wins a reward.
*/
int SlotInterface(Character & character) {
  std::string decision;
  std::cout << "Come play slots, I can guarantee good fortune. It only costs 5HP to play (Y/N) ";
  std::string symbols = "!@#$%";
  int amount_of_symbols = symbols.length();
  std::cin >> decision;
  while(!(decision == "N" || decision == "n" || decision == "Y" || decision == "y")) {
    std::cout << "Please input valid response" << std::endl;
    std::cout << "Play Slots? (Y/N) ";
    std::cin >> decision;
  }
  if (decision == "Y" || decision == "y") {
    while(true) {
      character.HP -= 5;
      std::srand(time(0));
      char slot1 = symbols[rand() % amount_of_symbols];
      char slot2 = symbols[rand() % amount_of_symbols];
      char slot3 = symbols[rand() % amount_of_symbols];
      std::cout << std::endl;
      std::cout << slot1 << " | "; 
      std::cout << slot2 << " | " << std::endl << std::endl;
      std::cout << "drumrolls please......" << std::endl << std::endl;
      sleep(1);
      std::cout << slot1 << " | " << slot2 << " | " << slot3 << std::endl << std::endl;
      if (RewardCheck(slot1,slot2,slot3) == 2) {
        std::cout << "Jackpot!!!" << std::endl;
        return 3; 
      }
      else if (RewardCheck(slot1,slot2,slot3) == 1) {
        std::cout << "You win a medium reward" << std::endl;
        return 2;
      }
      else {
        std::cout << "How does it feel like to be a loser?" << std::endl;
        return 0;
      }
      if (decision == "N" || decision == "n") break;
    }    
  }
}











