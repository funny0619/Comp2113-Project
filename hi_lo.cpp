#include <iostream>
#include <string>
#include <ctime>
#include "functions.h"

#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

/*
Function TenConvert input: a string value representing card number

Function output: a new string that replaces "T" to "10"

What the Function does: I have stored all the different card values in a string like so "A23456789TJQK"
but T should be changed to 10 for better readability
*/
std::string TenConvert(std::string a) {
  if (a == "T") a = "10";
  return a;
}

/*
Function AddSuit input: a number that represents card index from a range of 0 to 51

Function output: a string that represents the SUITE of the card in unicode 

What the Function does: The function adds te suits of the card inputted
*/
std::string AddSuit(int number) {
  if (0 <= number && number <= 12) return SPADE;
  else if (13 <= number && number <= 25) return HEART;
  else if (26 <= number && number <= 38) return CLUB;
  else if (39 <= number && number <= 51) return DIAMOND;
}


/*
Function HiLo input: A struct of type Character

Function output: an integer representing big,small,win,lose
0 is lose
1 is small prize
2 is medium prize
3 is big prize

What the Function does: The function first asks if player wants to play a game of Hi Lo. after showing the player
what card the player got, the player has to guess if the card the player got is higher or lower than the dealer's card

if player gusses correctly, the player can choose to keep playing, or stop and take the winnings. But if player chose to keep
playing and lost, player gets nothing.

If player chooses to stop playing, the amount of wins is counted and rewards is given accordingly.

1 to 2 wins is small prize 
3 to 5 wins is medium prize 
6 onwards wins is big prize prize 
*/

int HiLo(Character & character) {
  std::string cards = "A23456789TJQK";
  int win_occurence = 0;
  std::srand(time(0)*4);
  std::string decision;
  std::string game_decision;
  std::string continue_decision;
  std::cout << "Care for a game of Hi Lo? You need to bet 5HP, but the odds are in your favor (Y/N)  ";
  std::cin >> decision;
  while(!(decision == "N" || decision == "n" || decision == "Y" || decision == "y")) {
    std::cout << "Please input valid response" << std::endl;
    std::cout << "Play Hi Lo? (Y/N) ";
    std::cin >> decision;
  }
  std::cout << "The rules of the game are very simple. You look at your card and guess if your card is Hi or Lo compared to mine. Simple right? " << std::endl;
  if (decision == "Y" || decision == "y") {
    while(true) {
      character.HP -= 5;
      int playerCardNumber = std::rand() % 52;
      int enemyCardNumber = std::rand() % 52;
      std::string dealerCard = TenConvert(std::string(1,cards[(enemyCardNumber % 13)])) + AddSuit(enemyCardNumber);
      std::string playerCard = TenConvert(std::string(1,cards[(playerCardNumber % 13)])) + AddSuit(playerCardNumber);
      std::cout << "This is your card: " << playerCard << std::endl;
      std::cout << std::endl; 
      std::cout << "the dealer has been dealt a card, are you ready to make your decision? is YOUR card Hi or Lo? K is the highest, A is the lowest (H or L) ";
      std::cin >> game_decision;
      while(!(game_decision == "H" || game_decision == "h" || game_decision == "L" || game_decision == "l")) {
        std::cout << "Please input valid response" << std::endl;
        std::cout << "Hi or Lo? (H/L) ";
        std::cin >> game_decision;
        std::cout << std::endl;
      }
      std::cout << std::endl;
      if (game_decision == "H" || game_decision == "h") {
        if(playerCardNumber % 13 > enemyCardNumber % 13) {
          ++win_occurence;
          std::cout << "you have guessed correctly... this time. Dealer had " << dealerCard << std::endl;
          std::cout << "Do you want to keep going? You can earn bigger rewards for more wins, but if you lose you lose ALL your progress (Y/N) ";
          std::cin >> continue_decision;
          std::cout << std::endl;
          while(!(continue_decision == "N" || continue_decision == "n" || continue_decision == "Y" || continue_decision == "y")) {
            std::cout << "Please input valid response" << std::endl;
            std::cout << "Keep playing? (Y/N) ";
            std::cin >> continue_decision;
            std::cout << std::endl;
          }
          if (continue_decision == "Y" || continue_decision == "y") {
            std::cout << "The house always welcomes you" << std::endl;
          }
          else if (continue_decision == "N" || continue_decision == "n") {
            std::cout << "A coward eh? you stop the game with " << win_occurence << " wins ";
            break;
          }
        }
        else if(playerCardNumber % 13 < enemyCardNumber % 13) {
          if (win_occurence > 0) {
            std::cout << "You had " << win_occurence << " wins, but your greedines cost you everything. No refunds! :)" << std::endl;
            std::cout << std::endl;
            win_occurence = 0;
            break;
          }
          std::cout << "Wrong choice kid, you lose all your winnings. Dealer had " << dealerCard << std::endl;
          std::cout << std::endl;
          break;
        }
        else if(playerCardNumber % 13 == enemyCardNumber % 13) {
          std::cout << "You're saved for now, but this does not count as a win. Dealer had " << dealerCard << std::endl;
          std::cout << "Do you want to keep going? You can earn bigger rewards for more wins, but if you lose you lose ALL your progress (Y/N) ";
          std::cin >> continue_decision;
          std::cout << std::endl;
          while(!(continue_decision == "N" || continue_decision == "n" || continue_decision == "Y" || continue_decision == "y")) {
            std::cout << "Please input valid response" << std::endl;
            std::cout << "Keep playing? (Y/N) ";
            std::cin >> continue_decision;
            std::cout << std::endl;
          }
          if (continue_decision == "Y" || continue_decision == "y") {
            std::cout << "The house always welcomes you" << std::endl;
          }
          else if (continue_decision == "N" || continue_decision == "n") {
            std::cout << "A COWARD eh? you stop the game with " << win_occurence << " wins ";
            break;
          } 
        }
      }
      else if (game_decision == "L" || game_decision == "l") {
        if(playerCardNumber % 13 < enemyCardNumber % 13) {
          ++win_occurence;
          std::cout << "you have guessed correctly... this time. Dealer had " << dealerCard << std::endl; 
          std::cout << "Do you want to cash out now or be a man and keep going? You can earn bigger rewards for more wins (Y/N)";
          std::cin >> continue_decision;
          std::cout << std::endl;
          while(!(continue_decision == "N" || continue_decision == "n" || continue_decision == "Y" || continue_decision == "y")) {
            std::cout << "Please input valid response" << std::endl;
            std::cout << "Keep playing? (Y/N) ";
            std::cin >> continue_decision;
            std::cout << std::endl;
          }
          if (continue_decision == "Y" || continue_decision == "y") {
            std::cout << "The house always welcomes you" << std::endl;
          }
          else if (continue_decision == "N" || continue_decision == "n") {
            std::cout << "A COWARD eh? you stop the game with " << win_occurence << " wins ";
            break;
          }
        }
        else if(playerCardNumber % 13 > enemyCardNumber % 13) {
          if (win_occurence > 0) {
            std::cout << "You had " << win_occurence << " wins, but your greedines cost you everything. Now you have 0 wins. No refunds! :)" << std::endl;
            std::cout << "Dealer had " << dealerCard << std::endl;
            std::cout << std::endl;
            win_occurence = 0;
            break;
          }
          std::cout << "Wrong choice kid, you lose everything. Dealer had " << dealerCard << std::endl;
          std::cout << std::endl;
          break;
        }
        else if(playerCardNumber % 13 == enemyCardNumber % 13) {
          std::cout << "Your saved for now, but this does not count as a win. Dealer had " << dealerCard << std::endl;
          std::cout << "Do you want to cash out now or be a man and keep going? You can earn bigger rewards for more wins (Y/N)";
          std::cin >> continue_decision;
          std::cout << std::endl;
          while(!(continue_decision == "N" || continue_decision == "n" || continue_decision == "Y" || continue_decision == "y")) {
            std::cout << "Please input valid response" << std::endl;
            std::cout << "Keep playing? (Y/N) ";
            std::cin >> continue_decision;
            std::cout << std::endl;
          }
          if (continue_decision == "Y" || continue_decision == "y") {
            std::cout << "The house always welcomes you" << std::endl;
          }
          else if (continue_decision == "N" || continue_decision == "n") {
            std::cout << "A coward eh? you stop the game with " << win_occurence << " wins ";
            break;
          } 
        }
      }
    }
  }
  if(win_occurence > 5) {
    std::cout << "You have earned the biggest prize" << std::endl;
    return 3;
  }
  else if(win_occurence >= 3 && win_occurence <= 5) {
    std::cout << "You have earned the medium prize" << std::endl;
    return 2;
  }
  else if(win_occurence == 1 || win_occurence == 2) {
    std::cout << "You have earned the small prize" << std::endl;
    return 1;
  }
  else if(win_occurence == 0) {
    return 0;
  }
}
