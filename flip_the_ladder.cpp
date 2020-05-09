#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include "functions.h"

/*
  Function Ladder does not take inputs.
  Function output: (An integer: 0 is lose; 1 is small prize; 2 is medium prize; 3 is big prize; 5 is quit game)
  What the function does: The function generates the game to let the user guess the word from a selected category.
  It first asks for the user's consent for taking the challenge.
  Then it requests for the user's input to choose a theme: Techcompany, city, or mtr station names.
  Then the user is required to guess the word. The user can make 5 errors max.
  A medium prize is given if the user succesfully guessed the word within 5 errors.
  No punishment if the user losses the game.
*/

int Ladder() {
  std::string company_names[] = {"Apple", "Google", "Microsoft", "Intel", "Baidu", "Tesla", "Samsung", "Huawei", 
  "Facebook", "Twitter", "Sony", "Dell", "Xiaomi", "Amazon", "Tencent", "Alibaba", "IBM", "Paypal", "Netflix", "Adobe"};
  std::string city_names[] = {"HongKong", "London", "NewYork", "Tokyo", "Shanghai", "Beijing", "Seoul", "Singapore", "Paris", 
  "Sydney", "Vancouver", "Shenzhen", "Boston", "SanFrancisco", "Melbourne", "Dubai", "Moscow", "Barcelona", "LosAngeles"};
  std::string mtr_names[] = {"Admiralty", "Central", "CausewayBay", "Mongkok", "Shatin", "Airport", "KaiTak", "KowloonTong", 
  "TsimShaTsui", "PrinceEdward", "OceanPark", "TsingYi", "PrinceEdward", "Whampoa", "HungHom", "Olympic", "NorthPoint", "KwunTong", 
  "LokFu", "KennedyTown"};

  std::string decision;
  std::string theme_choice;
  std::string rand_word;
  std::string user_guess;

  int attempts = 5;
  int word_length = 0;
  char guess_char;
  bool guessed = false;
  bool correct = false;

  std::srand(time(0)*12);

  std::cout << "Oh no! You fall into a trap! You are now standing on a ladder. You need to guess the word in my mind to climb up. Below the ladder is hell. If you guess the wrong letter 5 times, you will fall down the ladder! Are you ready to take this challenge? (Y/N) ";
  std::cin >> decision;
  while(!(decision == "N" || decision == "n" || decision == "Y" || decision == "y")) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Please input valid response" << std::endl;
    std::cout << "Are you ready to take this challenege? (Y/N) ";
    std::cin >> decision;
  }
  if (decision == "N" || decision == "n") {
    return 5;
  }

  std::cout << "Now, choose the theme of the words: Tech Companies (T), City Names (C), or MTR Station Names (M)? ";
  std::cin >> theme_choice;
  while (theme_choice != "t" && theme_choice != "T" && theme_choice != "c" && theme_choice != "C" && theme_choice != "m" && theme_choice != "M") {
    std::cout << "Please input valid response! (T/C/M) ";
    std::cin >> theme_choice;
  }

  //if the user chooses the company theme
  if (theme_choice == "t" || theme_choice == "T") {
    rand_word = company_names[rand()%20];
    word_length = rand_word.length();
    for (int i = 0; i<word_length; ++i) {
      user_guess[i] = '_';
    }

    while (guessed == false && attempts > 0) {
      for (int i = 0; i<word_length; ++i) {
        std::cout << user_guess[i];
      }
      std::cout <<  std::endl << "Make a guess: ";
      std::cin >> guess_char;
      for (int i=0; i<word_length; ++i) {
        if (toupper(guess_char) == toupper(rand_word[i])){
          user_guess[i] = rand_word[i];
          std::cout << "Correct Guess!" << std::endl;
          correct = true;
        }
      }
      if (correct == false) {
        --attempts;
        std::cout << "Wrong guess! Try again. You have " << attempts << " attempts left!" << std::endl;
      }
      if (attempts < 1) {
        std::cout << "Attempts used up! You fall off the ladder! (The answer is " << rand_word << ")" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return 0;
      }
      guessed = true;
      for (int i=0; i<word_length; ++i) {
        if (user_guess[i] != rand_word[i]) {
          guessed = false;
        }
      }
      correct = false;
    }

  } 

  // if the user chooses city names
  else if (theme_choice == "c" || theme_choice == "C") {
    rand_word = city_names[rand()%20];
    word_length = rand_word.length();
    for (int i = 0; i<word_length; ++i) {
      user_guess[i] = '_';
    }

    while (guessed == false && attempts > 0) {
      for (int i = 0; i<word_length; ++i) {
        std::cout << user_guess[i];
      }
      std::cout << std::endl << "Make a guess: ";
      std::cin >> guess_char;
      for (int i=0; i<word_length; ++i) {
        if (toupper(guess_char) == toupper(rand_word[i])){
          user_guess[i] = rand_word[i];
          std::cout << "Correct Guess!" << std::endl;
          correct = true;
        }
      }
      if (correct == false) {
        --attempts;
        std::cout << "Wrong guess! Try again. You have " << attempts << " attempts left!" << std::endl;
      }
      if (attempts < 1) {
        std::cout << "Attempts used up! You fall off the ladder! (The answer is " << rand_word << ")" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return 0;
      }
      guessed = true;
      for (int i=0; i<word_length; ++i) {
        if (user_guess[i] != rand_word[i]) {
          guessed = false;
        }
      }
      correct = false;
    }

  } 

  //if the user chooses mtr station names
  else if (theme_choice == "m" || theme_choice == "M") {
    rand_word = mtr_names[rand()%20];
    word_length = rand_word.length();
    for (int i = 0; i<word_length; ++i) {
      user_guess[i] = '_';
    }

    while (guessed == false && attempts > 0) {
      for (int i = 0; i<word_length; ++i) {
        std::cout << user_guess[i];
      }
      std::cout << std::endl << "Make a guess: ";
      std::cin >> guess_char;
      for (int i=0; i<word_length; ++i) {
        if (toupper(guess_char) == toupper(rand_word[i])){
          user_guess[i] = rand_word[i];
          std::cout << "Correct Guess!" << std::endl;
          correct = true;
        }
      }
      if (correct == false) {
        --attempts;
        std::cout << "Wrong guess! Try again. You have " << attempts << " attempts left!" << std::endl;
      }
      if (attempts < 1) {
        std::cout << "Attempts used up! You fall off the ladder! (The answer is " << rand_word << ")" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return 0;
      }
      guessed = true;
      for (int i=0; i<word_length; ++i) {
        if (user_guess[i] != rand_word[i]) {
          guessed = false;
        }
      }
      correct = false;
    }

  }

  if (guessed == true) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Congratulations! You are safe now!" << std::endl;
    return 2;
  }
}	