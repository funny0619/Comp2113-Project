#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <vector>
#include "character.cpp"
#include "functions.h"

/*
Function PrintCharacters input: a vector container of structs of type Character

Function output: void

What the Function does: The function traverses the vector container and prints out all the player characters avaialable
Each attribute is given 15 spaces, if attributes output length is smaller than 15, we use spaces to fill in the gap.
So the output of character display is orderly
*/
void PrintCharacters(std::vector<Character> characters) {
  int standard = 15;
  int spaces;
  int length;
  std::string output;
  for(int i=0; i<characters.size(); ++i) {
    std::string playerNumber = std::to_string(i+1) + ". ";
    output = playerNumber + characters[i].Name;
    length = output.length();
    spaces = standard - length;
    for(int j=0; j<spaces; ++j) {
      output += " ";
    }
    output += "|";
    std::cout << output;
  }
  std::cout << std::endl;
  for(int i=0; i<characters.size(); ++i) {
    int HPInt = characters[i].HP;
    std::string HP = std::to_string(HPInt);
    output = "HP: " + HP;
    length = output.length();
    spaces = standard - length;
    for(int j=0; j<spaces; ++j) {
      output += " ";
    }
    output += "|";
    std::cout << output;
  }
  std::cout << std::endl;
  for(int i=0; i<characters.size(); ++i) {
    int StrengthInt = characters[i].Strength;
    std::string Strength = std::to_string(StrengthInt);
    output = "Strength: " + Strength;
    length = output.length();
    spaces = standard - length;
    for(int j=0; j<spaces; ++j) {
      output += " ";
    }
    output += "|";
    std::cout << output;
  }
  std::cout << std::endl;
  for(int i=0; i<characters.size(); ++i) {
    std::string Dexterity = std::to_string(characters[i].Dexterity);
    output = "Dexterity: " + Dexterity;
    length = output.length();
    spaces = standard - length;
    for(int j=0; j<spaces; ++j) {
      output += " ";
    }
    output += "|";
    std::cout << output;
  }
  std::cout << std::endl;
  for(int i=0; i<characters.size(); ++i) {
    int LuckInt = characters[i].Luck;
    std::string Luck = std::to_string(LuckInt);
    output = "Luck: " + Luck;
    length = output.length();
    spaces = standard - length;
    for(int j=0; j<spaces; ++j) {
      output += " ";
    }
    output += "|";
    std::cout << output;
  }
  std::cout << std::endl;
}
/*
Function EnemyAi input: a struct of type Character, and move choice of the player
1 is attack
2 is dodge
3 is flee

Function output: integer representing enemy choice
0 means attack
1 means dodge
enemy cannot flee

What the Function does: 
with the seed time(0)*3, the function randomly generated a number between 1 and 100, to represent percentage

if player has lower dexterity than the enemy, enemy immediatley attacks if enemy strength is higher than 100.
if player has lower dexterity than the enemy, enemy has 80% chance of attacking 20% of dodging if strength is lower than 20%

if player has chosen to attack and enemy has dexterity higher than 100 but lower than 200, enemy has 70% chance of attacking 30% chance of dodging
if player has chosen to attack and enemy has dexterity higher than 200, enemy has 50% chance of attacking 50% chance of dodging
if player has chosen to attack and enemy has dexterity lower than 100, enemy has 80% chance of attacking 50% chance of dodging

generally enemies with higher dexterity has a higher chance to choose to dodge, because their dodge chance is also higher

if player has chosen to dodge enemy has 80% chance of attacking and 20% chance of dodging. 
Since player dodged enemy should use the opportunity to attack

if player has chosen to flee, enemy will 100% attack
*/
int EnemyAi(Character character, int move_choice){
  std::mt19937 gen(time(0)*3); //Standard mersenne_twister_engine seeded with time(0)*3
  std::uniform_int_distribution<> dis(1, 100);//Produces random integer values i, uniformly distributed on the closed interval [a, b]
  int percentage = dis(gen);
  int threshold; // threshold for various outcomes
  if (move_choice == 0) { //this means enemy has higher dexterity than the player
    if(character.Strength >= 100){
      return 0;
    }
    else {
      threshold = 80;//determines the chance of attacking
      if (percentage > threshold)
        return 1;
      else
        return 0;
    }
  }
  else if (move_choice == 1) {//this means player has chosen to attack
    if(character.Dexterity >= 100){
      threshold = 70;//determines the chance of attacking
      if (percentage > threshold)
        return 1;
      else
        return 0;
    }
    else if(character.Dexterity >= 200){
      threshold = 50;//determines the chance of attacking
      if (percentage > threshold)
        return 1;
      else
        return 0;
    }
    else { //enemy has low dexterity
      threshold = 80;//determines the chance of attacking
      if (percentage > threshold)
        return 1;
      else
        return 0;
    }
  }
  else if (move_choice == 2) {//player has chosen to dodge
    threshold = 80;//determines the chance of attacking
    if (percentage > threshold)
      return 1;
    else
      return 0;
  }
  else {//player has chosen to flee
    return 0;
  }
}
/*
Function CreateGameInstance input: a struct of type Character, a vector container of structs of type Character, 
and players choice of character. or chosen enemy to spawn.

Function output: void

What the Function does: To avoid changing the values in the vector container containg all the player/enemies,
a new struct is initliazed just for the game. values will be changed on the newly intilized struct, not the original 
struct in the vector container
*/
void CreateGameInstance(Character & character, std::vector<Character> characters, int choice) {
  character.Name = characters[choice].Name;
  character.HP = characters[choice].HP;
  character.Strength = characters[choice].Strength;
  character.Dexterity = characters[choice].Dexterity;
  character.Difficulty = characters[choice].Difficulty;
  character.Luck = characters[choice].Luck;
  character.Index = characters[choice].Index;
}
/*
Function Combat input: a struct of type Character of one side, a struct of type Character of the other side 
on the other side of the combat

Function output: bool. true represents battle won, false represents either flee or loss

What the Function does:
The function stores all the attributes of player and enemy used for combat
a game loop starts and if player has higher dexterity, player starts the attack
a game loop starts and if enemy has higher dexterity, enemy starts the attack

if one side chose dodge and the other has chosen to attack dodge chance is caclulated with Dodge()
and damage is calculated with Attack()

if dodge failed the attacked take damage with TakeDamage();

The game loop alternates between player and enemy untill either player flees,wins, or loses.
*/
bool Combat(Character & player, Character enemy) {
  double base_attack = 15;
  double player_hp = player.HP;
  double enemy_hp = enemy.HP;
  int player_dexterity = player.Dexterity;
  int enemy_dexterity = enemy.Dexterity;
  double player_strenth = player.Strength;
  double enemy_strength = enemy.Strength;
  double player_luck = player.Luck;
  double enemy_luck = enemy.Luck;
  int move_choice = 0;
  bool player_dodged = false;
  bool enemy_dodged = false;
  bool enemy_attack = true;
  std::string  decision;
  std::cout << player.Name << " sees " << enemy.Name << " ahead, do you choose to fight?" << std::endl;
  std::cout << enemy.Name << " has " << enemy.HP << "HP (Y or N) ";
  std::cin >> decision;
  std::cout << std::endl;
  if (decision == "Y" || decision == "y"){
    while (true) {
      if(player_dexterity >= enemy_dexterity) {
        std::cout << player.Name << " HP: " << player.HP << "     "<<enemy.Name << " HP: " << enemy.HP << std::endl;
        std::cout << std::endl;
        std::cout << player.Name << " poises for an attack (1.Attack 2.Dodge 3.Flee) ";
        while(true){
          std::cin >> move_choice;
          if(move_choice < 1 || move_choice > 3 || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Choose a valid move you dimiwit (1.Attack 2.Dodge 3.Flee) ";
          }
          else {
            break;
          }
        }
        std::cout << std::endl;
        if(move_choice == 1) {
          std::cout << player.Name <<" chose to attack" << std::endl;
          if(enemy_dodged) {
            if(Dodge(enemy_dexterity,player_dexterity,enemy)) {
              std::cout << enemy.Name <<" successfully dodges" << std::endl;
              std::cout << std::endl;
              enemy_dodged = false;
            }
            else{
              std::cout << enemy.Name <<" slips on mud" << std::endl;
              std::cout << std::endl;
              double damage = Attack(player_strenth,base_attack,player);
              TakeDamage(damage,enemy);
              enemy_dodged = false;
              enemy_hp = enemy.HP;
              if (enemy_hp <= 0) break;
              std::cout << std::endl;
            }
          }
          else {
            double damage = Attack(player_strenth,base_attack,player);
            TakeDamage(damage,enemy);
            enemy_hp = enemy.HP;
            if (enemy_hp <= 0) break;
            std::cout << std::endl;
          }
        }
        else if (move_choice == 2) {
          std::cout << player.Name <<" chose to dodge" << std::endl;
          std::cout << std::endl;
          player_dodged = true;
        }
        else if(move_choice == 3) {
         if(Flee(player_dexterity,enemy_dexterity,player)) {
            std::cout << "Cowardice prevails, " << player.Name << " flees with " << player.HP << "HP left " << std::endl;
            break;
          }
          else {
            std::cout << enemy.Name << " grabs you by the tails, you must face your fear" << std::endl;
            std::cout << std::endl;
          }
        }
        std::cout << enemy.Name <<" gets into attack position" << std::endl;
        std::cout << std::endl;
        sleep(1);
        if(EnemyAi(enemy,move_choice) == 0){
          std::cout << enemy.Name <<" chose to attack" << std::endl;
          if(player_dodged) {
            if(Dodge(player_dexterity,enemy_dexterity,player)) {
              player_dodged = false;
              std::cout << player.Name <<" successfully dodged!" << std::endl;
              std::cout << std::endl;
            }
            else {
              std::cout << player.Name <<" stubmles awkwardly" << std::endl;
              std::cout << std::endl;
              double damage = EnemyAttack(enemy_strength,base_attack,enemy);
              TakeDamage(damage,player);
              player_dodged = false;
              player_hp = player.HP;
              if (player_hp <= 0) break;
              std::cout << std::endl;
            }
          }
          else {
            double damage = EnemyAttack(enemy_strength,base_attack,enemy);
            TakeDamage(damage,player);
            player_hp = player.HP;
            player_dodged = false;
            if (player_hp <= 0) break;
            std::cout << std::endl;
          }
        }
        else {
          enemy_dodged = true;
          player_dodged = false;
          std::cout << enemy.Name <<" chose to dodge" << std::endl;
          std::cout << std::endl;
        }
        std::cout << "------------------------------------------------------------" <<  std::endl;
        std::cout << std::endl;
      }
      else if(player_dexterity < enemy_dexterity) {
        std::cout << player.Name << " HP: " << player.HP << "     "<<enemy.Name << " HP: " << enemy.HP << std::endl;
        std::cout << std::endl;
        std::cout << enemy.Name << " prepares for a lunge" << std::endl;
        std::cout << std::endl;
        sleep(1);
        if(EnemyAi(enemy,move_choice) == 0){
          std::cout << enemy.Name <<" chose to attack" << std::endl;
          if(player_dodged) {
            if(Dodge(player_dexterity,enemy_dexterity,player)) {
              player_dodged = false;
              std::cout << player.Name<< " successfully dodges" << std::endl;
              std::cout << std::endl;
            }
            else {
              std::cout << player.Name << " skipped classes during Dexterity training" << std::endl;
              std::cout << std::endl;
              double damage = EnemyAttack(enemy_strength,base_attack,enemy);
              TakeDamage(damage,player);
              player_dodged = false;
              player_hp = player.HP;
              if (player_hp <= 0) break;
              std::cout << std::endl;
            }
          }
          else {
            double damage = EnemyAttack(enemy_strength,base_attack,enemy);
            TakeDamage(damage,player);
            player_dodged = false;
            player_hp = player.HP;
            if (player_hp <= 0) break;
            std::cout << std::endl;
          }
        }
        else {
          enemy_dodged = true;
          player_dodged = false;
          std::cout << enemy.Name <<" chose to dodge" << std::endl;
          std::cout << std::endl;
        }
        std::cout << player.Name << " poises for an attack (1.Attack 2.Dodge 3.Flee) ";
        while(true){
          std::cin >> move_choice;
          if(move_choice < 1 || move_choice > 3 || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Choose a valid move you dimiwit (1.Attack 2.Dodge 3.Flee) ";
          }
          else {
            break;
          }
        }
        std::cout << std::endl;
        if(move_choice == 1) {
          std::cout << player.Name << " chose to attack" << std::endl;
          if(enemy_dodged) {
            if(Dodge(enemy_dexterity,player_dexterity,player)) {
              std::cout << enemy.Name << " successfully dodges" << std::endl;
              std::cout << std::endl;
              enemy_dodged = false;
            }
            else{
              std::cout << enemy.Name <<"'s pathetic attempt for a dodge backfires" << std::endl;
              double damage = Attack(player_strenth,base_attack,enemy);
              TakeDamage(damage,enemy);
              enemy_dodged = false;
              enemy_hp = enemy.HP;
              if (enemy_hp <= 0) break;
              std::cout << std::endl;
            }
          }
          else {
            double damage = Attack(player_strenth,base_attack,enemy);
            TakeDamage(damage,enemy);
            enemy_hp = enemy.HP;
            enemy_dodged = false;
            if (enemy_hp <= 0) break;
            std::cout << std::endl;
          }
        }
        else if (move_choice == 2) {
          std::cout << player.Name <<" chose to dodge" << std::endl;
          std::cout << std::endl;
          enemy_dodged = false;
          player_dodged = true;
        }
        else if(move_choice == 3) {
          if(Flee(player_dexterity,enemy_dexterity,player)) {
            std::cout << "Cowardice prevails, " << player.Name << " flees with " << player.HP << "HP left " << std::endl;
            break;
          }
          else {
            std::cout << enemy.Name << " grabs you by the tails, you must face your fear" << std::endl;
            std::cout << std::endl;
          }
        }
        std::cout << "------------------------------------------------------------" <<  std::endl;
        std::cout << std::endl;
      }
    }
  }
  if (enemy_hp <= 0) {
    std::cout << enemy.Name <<" is slain, you emerge from the battlefied victorious" << std::endl;
    return true;
  }
  if (decision == "N" || decision == "n") {
    std::cout << player.Name << " has decided now is not the time for bravery" << std::endl;
  }
  return false;
}

