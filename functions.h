#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#ifndef CHARACTER
#define CHARACTER

struct Character
{
  std::string Name;
  double HP;
  double Strength;
  int Dexterity;
  int Difficulty;
  int Luck;
  int Index;
};

#endif/*CHARACTER*/


//character
void MiniGameWon(Character & character, int reward_tier);
void Win();
void InitializeStruct(std::vector<Character> & characters, std::string file_name);
void Die();

//combat
void CombatInterface();
bool Dodge(int player_dexterity, int enemy_dexterity, Character character);
bool Flee(int player_dexterity, int enemy_dexterity, Character character);
double EnemyAttack(double strength, double base_attack,Character character);
double Attack(double strength, double base_attack,Character character);
void TakeDamage(double damage, Character & character);
int EnemyAi(Character character, int moveChoice);
void CreateGameInstance(Character & character, std::vector<Character> characters, int choice);
bool Combat(Character & player, Character enemy);
void PrintCharacters(std::vector<Character> characters);

//minigames
int SlotInterface(Character & character);
int RewardCheck(char slot1, char slot2, char slot3);
int Ladder();
int Memorizing();
std::string TenConvert(std::string a);
std::string AddSuit(int number);
int HiLo(Character & character);
