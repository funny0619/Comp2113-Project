#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <random>
#include "functions.h"

/*
Function MinGameWon input: a character with type struct Character and integer reward tier

Function output: void. It is used to change character attribute values based on reward tier. 
and show how well the player is doing

What the Function does : the function determines how much HP,Dexterity,Strength, or Luck should be given based on 
the reward tier returned by the other minigames. Each attribute has a base step value
The function also determines if player lost.
*/
void MiniGameWon(Character & character, int reward_tier) {
  int decision;
  int hp_prize = reward_tier * 25;
  int dexterity_prize = reward_tier * 25;
  int strength_prize = reward_tier * 25;
  int luck_prize = reward_tier * 2;
  if (reward_tier > 0 && reward_tier <= 3){
    std::cout << "You have proven yourself worthy, pick your prize (1.HP 2.Strength 3.Dexterity 4.Luck) ";
    std::cin >> decision;
    if(decision == 1) {
      character.HP += hp_prize;
      std::cout << "your HP increases by " << hp_prize << " you now have " << character.HP << "HP" << std::endl;
      std::cout << std::endl;
    }
    else if(decision == 2) {
      character.Strength += strength_prize;
      std::cout << "your Strength increases by " << strength_prize << " you now have " << character.Strength << " Strength" << std::endl;
      std::cout << std::endl;
    }
    else if(decision == 3) {
      character.Dexterity += dexterity_prize;
      std::cout << "your Dexterity increases by " << dexterity_prize << " you now have " << character.Dexterity << " Dexterity" << std::endl;
      std::cout << std::endl;
    }
    else if(decision == 4) {
      character.Luck += luck_prize;
      std::cout << "your Luck increases by " << luck_prize << " you now have " << character.Luck << " Luck" << std::endl;
      std::cout << std::endl;
    }
  }
  else if(reward_tier == 0){
    std::cout << "You failed miserbably, you get nothing" << std::endl;
    std::cout << std::endl;
  }
}

/*
Function Win input: Nothing

Function output: void. A message output to indicate character has won the game!

What the Function does: Relays a story/message to end the game and tell the player he/she has won 
*/
void Win(){
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Thus concludes your journey through hell, was selling your soul worth it? It's ok we will see you soon ;)" << std::endl;
}

/*
Function InitializeStruct input: a vector container that stores multiple structs of type Character 
and file name that has the data of characters

Function output: void.

What the Function does: The function reads from the file indicated in input, and goes line by line storing
the values in apporporiate variables of each struct. The data is stored in file_name is a specific manner
that allows this function go through the whole file and store all the neccessary structs from the data.
*/
void InitializeStruct(std::vector<Character> & characters, std::string file_name) {
  std::ifstream fin;
  fin.open(file_name);
  std::string line;
  int counter = 0;
  int character_counter = 0;
  while(getline(fin, line)) {
    if(counter == 0) {
      characters.push_back(Character());
      line = line.substr(6);
      characters[character_counter].Name = line;
      ++counter;
    }
    else if(counter == 1){
      line = line.substr(4);
      characters[character_counter].HP = std::stod(line);
      ++counter;
    }
    else if(counter == 2){
      line = line.substr(10);
      characters[character_counter].Strength = std::stod(line);
      ++counter;
    }
    else if(counter == 3){
      line = line.substr(12);
      characters[character_counter].Dexterity = std::stod(line);
      ++counter;
    }
    else if(counter == 4){
      line = line.substr(12);
      characters[character_counter].Difficulty = std::stod(line);
      ++counter;
    }
    else if(counter == 5){
      line = line.substr(6);
      characters[character_counter].Luck = std::stod(line);
      ++counter;
    }
    else if(counter == 6){
      line = line.substr(7);
      characters[character_counter].Index = std::stod(line);
      ++counter;
    }
    else if(counter == 7){
      counter = 0;
      ++character_counter;
    }
  }

  fin.close();
}
/*
Function Attack input: strength of character doing the attacking, base_attack across all characters, and character doing the attacking

Function output: the function returns a double value that represents the amount of damage dealt

What the Function does: based on the strength, the character in the input deals more damage. Also, the character in
input also possesses a luck value that determines the chance of a critical hit. Each point of luck increases the
chance of a critical hit by 2%.
*/
double Attack(double strength, double base_attack, Character character) {
  std::mt19937 gen(time(0)); //Standard mersenne_twister_engine seeded with time(0)
  std::uniform_int_distribution<> dis(1, 100);//Produces random integer values i, uniformly distributed on the closed interval [a, b]
  int percentage = dis(gen);
  int threshold = 10; //Chance of critical attack
  threshold = threshold + character.Luck * 2;
  double damage;
  if (percentage > threshold){
    damage = strength/100 * base_attack;
    std::cout << character.Name << " has dealt " << damage << " damage "<<std::endl;
  }
  else{
    damage = strength/100 * base_attack * 2;
    std::cout << character.Name << " has dealt critical damage for " << damage << std::endl;
  }
  return damage;
}
/*
Function EnemyAttack input: strength of character doing the attacking, base_attack across all characters, and character doing the attacking

Function output: the function returns a double value that represents the amount of damage dealt

What the Function does: based on the strength, the character in the input deals more damage. Also, the character in
input also possesses a luck value that determines the chance of a critical hit. Each point of luck increases the
chance of a critical hit by 2%.

Attack() and EnemyAttack() are Two Identical attack functions. Two were made to ensure enemy and player 
dont always crit at the same time because of the same seed of time(0)
*/
double EnemyAttack(double strength, double base_attack,Character character) {
  std::mt19937 gen(time(0)*2); //Standard mersenne_twister_engine seeded with time(0)*2
  std::uniform_int_distribution<> dis(1, 100);//Produces random integer values i, uniformly distributed on the closed interval [a, b]
  int percentage = dis(gen);
  int threshold = 10; //Chance of critical attack
  double damage;
  if (percentage > threshold){
    damage = strength/100 * base_attack;
    std::cout << character.Name << " has dealt " << damage << " damage "<<std::endl;
  }
  else{
    damage = strength/100 * base_attack * 2;
    std::cout << character.Name << " has dealt critical damage for " << damage << std::endl;
  }
  return damage;
}
/*
Function TakeDamage input: damage dealth, and character taking the damage

Function output: void

What the Function does: based on the input of damage dealt, the function decreases the health value stored in 
the inputted character struct.
*/
void TakeDamage(double damage, Character & character) {
  character.HP = character.HP - damage;
}
/*
Function Dodge input: dexterity of character doing the attacking, dexterity of character receiving the attack,
and character doing the attacking

Function output: the function returns a bool value that represents true or false of dodge status

What the Function does: function calculates whether or not player has succesfully dodged based on how large the 
difference between the attacking and dodging character's dexterity is. There is a base 20% chance of dodging for each character
every 10 dexterity difference increases dodge chance by 1%
*/
bool Dodge(int player_dexterity, int enemy_dexterity, Character character) {
  std::mt19937 gen(time(0)); //Standard mersenne_twister_engine seeded with time(0)
  std::uniform_int_distribution<> dis(1, 100);//Produces random integer values i, uniformly distributed on the closed interval [a, b]
  int percentage = dis(gen);
  int threshold = 20;//Chance of dodge
  int difference = (player_dexterity - enemy_dexterity) / 10;
  threshold = threshold + difference;
  if (threshold < 0) threshold = 0;
  if (threshold > 100) threshold = 100;
  std::cout << character.Name << "'s chance to dodge is " << threshold << "%" << std::endl;
  if (percentage > threshold){
    return false;
  }
  return true;
}
/*
Function Die input: None

Function output: void A message output to indicate character has lost the game!

What the Function does: Relays a story/message to end the game and tell the player he/she has lost 
*/
void Die() {
  std::cout << "Your poor life choices have once again brought you to hell. There is no third chance. You fall back into hell to face your punishment... for eternity" << std::endl;
}
/*
Function Flee input: dexterity of character doing the attacking, dexterity of character receiving the attack,
and character doing the attacking

Function output: the function returns a bool value that represents true or false of flee status

What the Function does: function calculates whether or not player has succesfully fled based on how large the 
difference between the attacking and fleeing character's dexterity is. There is a base 50% chance of fleeing for each character
every 10 dexterity difference increases flee chance by 1%
*/
bool Flee(int player_dexterity, int enemy_dexterity, Character character) {
  std::mt19937 gen(time(0)); //Standard mersenne_twister_engine seeded with time(0)
  std::uniform_int_distribution<> dis(1, 100);//Produces random integer values i, uniformly distributed on the closed interval [a, b]
  int percentage = dis(gen);
  int threshold = 50;//Chance of flee
  int difference = (player_dexterity - enemy_dexterity) / 10;
  threshold = threshold + difference;
  if (threshold < 0) threshold = 0;
  if (threshold > 100) threshold = 100;
  std::cout << character.Name << "'s chance to flee is " << threshold << "%" << std::endl;
  if (percentage > threshold){
    return false;
  }
  return true;
}
