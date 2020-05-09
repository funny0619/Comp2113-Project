#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include "functions.h"

const int ROW = 10;
const int COL = 10;
int counter;
int store_cor[ROW*COL][2];

struct Point {
  int x;
  int y;
};

std::vector<int> tier_1_enemy;//stores index of enemies of difficulty 1
std::vector<int> tier_2_enemy;
std::vector<int> tier_3_enemy;
std::vector<int> tier_4_enemy;


struct Point entrance;
struct Point exit_point; 
struct Point character_point;
Character player;
/*
Function SortEnemyTier input: vectors container containg the structs of all the enemies avaialable in the game

Function output: void

What the Function does: The function sorts each enemy based on its Difficulty attribute into respective containers.
This sorting allows for generation of easy enemies first, and the hardest enemy last. So the player has time to level up
before fighting the hardest boss
*/
void SortEnemyTier(std::vector<Character> characters,int difficulty) {
  if (difficulty == 1) {
    for(int i=0; i<characters.size(); ++i) {
      if(characters[i].Difficulty == difficulty) {
        tier_1_enemy.push_back(i);
      }
    }
  }
  else if (difficulty == 2) {
    for(int i=0; i<characters.size(); ++i) {
      if(characters[i].Difficulty == difficulty) {
        tier_2_enemy.push_back(i);
      }
    }
  }
  else if (difficulty == 3) {
    for(int i=0; i<characters.size(); ++i) {
      if(characters[i].Difficulty == difficulty) {
        tier_3_enemy.push_back(i);
      }
    }
  }
  else if (difficulty == 4) {
    for(int i=0; i<characters.size(); ++i) {
      if(characters[i].Difficulty == difficulty) {
        tier_4_enemy.push_back(i);
      }
    }
  }
}
/*
Function PrintMap input: Map array, amount of row in array, amount of columns in array, and Character player

Function output: void

What the Function does: The function prints out the map status, along with all the relevant attributes of the current
player.
*/
void PrintMap(int array[][COL], int row, int col, Character character) {
  bool last_row = false;
  for(int i=0;i<row;++i) {
    for(int j=0;j<col;++j) {
      std::cout << std::setw(5)<< array[i][j];
      if(i == 0 && j == col - 1) std::cout << " HP: " << character.HP;
      if(i == 1 && j == col - 1) std::cout << " Strength: " << character.Strength;
      if(i == 2 && j == col - 1) std::cout << " Dexterity: " << character.Dexterity;
      if(i == 3 && j == col - 1) std::cout << " Luck: " << character.Luck;
      if(i == row - 1 && j == col - 1) last_row = true;
    }
    if(!last_row)
      std::cout << std::endl;
    else
      std::cout << " Movement: ";
  }
}

/*
Function MapGeneration input: Map array, amount of row in array, amount of columns in array.

Function output: void

What the Function does: 
The function asks for seed, and the functions picks an appropriate seed from seed box.
The function first randomly determines an entrance at the bottom of the array.
In order to make the game more interesting, the array is split into two halves, split by the y axis.
if entrance was generated on the right, exit generates on the left
if entrance was generated on the left, exit generates on the right
Entrance is at the bottom, exit is at the top of the array
after exit point and entrance point is set, the character's coordinate is set to be equal to the Entrance's
*/
void MapGeneration(int array[][COL], int row, int col) {
  int width = row;
  int half_width = width/2;
  int seed_box[10] = {4,14,15,17,22,23,25,35,37,39}; 
  int seed;
  std::cout << "Input random seed: "; 
  std::cin >> seed;
  seed = seed_box[seed%10];
  srand(seed);
  entrance.y = std::rand() % width;
  //This part of the code makes sure entrance are spawned in different halfs of the y axis.
  if (entrance.y < half_width) 
    exit_point.y = half_width + rand() % half_width;
  else
    exit_point.y = std::rand() % half_width;
  array[row-1][entrance.y] = 1;
  entrance.x = row - 1;
  array[0][exit_point.y] = -2;
  exit_point.x = 0;
  character_point.x = entrance.x;
  character_point.y = entrance.y;
}
/*
Function EntranceExitPathMaker input: Map array

Function output: void

What the Function does: 
The first part checks if the entrance is on the right or left side of the map
if entrance is on the right the function only generates path towards the left side of the map
if entrance is on the left the function only generates path towards the right side of the map

The second part generates a random number determining whether to move left/right or up, as the function traverses the array,
it sets a "1" on the coordinate to indicate the path.
During this part, the chance of moving up initially is higher so the path is more interesting

The third part stops random movement if path has traveresed over the condition set, or if the Y coordinate matches with the exit
The condition set is also random, it could be any where between "function has traversed over half of Rows" to "Functions have traversed all the rows"
Once the condition is met, path goes straight to exit, no more random movements

Then at the exit, a 9 is placed to indicate the boss. You have to beat the boss to win the game
*/
void EntranceExitPathMaker(int array[][COL]) {
  int x = entrance.x;
  int y = entrance.y;
  store_cor[counter][0] = x;   
  store_cor[counter][1] = y; 
  int direction;
  int condition; //This sets when path goes straight for the exit
  if (entrance.y < ROW/2) {
    while(x!=0 || y!=exit_point.y) {
      condition = std::rand() % 4 + 1;
      if (x < condition || y == exit_point.y) {
        while (y!=exit_point.y) {
          ++y;
          ++counter;
          array[x][y] = 1; 
          store_cor[counter][0] = x;   
          store_cor[counter][1] = y;    
        }
        while (x!=0) {
          --x;
          ++counter;
          array[x][y] = 1;
          store_cor[counter][0] = x;   
          store_cor[counter][1] = y;   
        }
        break;
      }
      direction = std::rand() % 3;
      if(direction == 0 || direction == 2) {
        --x;
        ++counter;
        array[x][y] = 1; //up
        store_cor[counter][0] = x;   
        store_cor[counter][1] = y;   
      }
      else {
        ++y;
        ++counter;
        array[x][y] = 1;//right
        store_cor[counter][0] = x;   
        store_cor[counter][1] = y;   
      }
    }
  }
  else if(entrance.y > ROW/2 - 1) {
    condition = std::rand() % 4 + 1;
    while(x!=0 || y!=exit_point.y) {
      if (x < condition || y == exit_point.y) {
        while (y!=exit_point.y) {
          --y;
          ++counter;
          array[x][y] = 1;
          store_cor[counter][0] = x;   
          store_cor[counter][1] = y;   
        }
        while (x!=0) {
          --x;
          ++counter;
          array[x][y] = 1;
          store_cor[counter][0] = x;   
          store_cor[counter][1] = y;   
        }
        break;
      }
      direction = std::rand() % 3;
      if(direction == 0 || direction == 2) {
        --x;
        ++counter;
        array[x][y] = 1; //up
        store_cor[counter][0] = x;   
        store_cor[counter][1] = y;   
      }
      else {
        --y;
        ++counter;
        array[x][y] = 1;//left 
        store_cor[counter][0] = x;   
        store_cor[counter][1] = y;   
      }
    }
  }
  array[exit_point.x][exit_point.y] = 9;
}

/*
Function MainGameLoop input: Map array, amount of row in array, amount of columns in array and the Character struct player

Function output: void

What the Function does:
 
First the function intitializes a vector container of structs that holds all the avaiable enemies. Then invokes
SortEnemyTier to sort the enemies based on difficulty.
Which 4 enemies are going to displayed is determined
Then the game loop starts. 
The game loop checks for  "w","a","s","d" as inputs to move the character repesented by the number "5"
Character cannot move towards an array coordinate that has the value 0.
array coordinate that has the value of 1 represents "the path" and the player can move on it.

when the player goes towards "8", which represents casinos/minigames, the game will randomly choose a minigame out 
of 4 (HiLo,Memorize Bananza,Slots,and Flip the Ladder).

when the palyer goes towards "9",which represents enemies, the game will update amount of enemy fought, so the next enemy
the player fights will be harder. The function Combat() will be called to determine if Player won or lost the fight.
if won, player will take the enemy's position

If player HP becomes equal to or smaller than 0, game loop stops and the function Die() is called.
If player reaches the exit, game loops stops and the function Win() is called.
*/
void MainGameLoop(int array[][COL],int row,int col, Character & player) {
  char movement;
  PrintMap(array,row,col,player);
  std::vector<Character> enemies;
  InitializeStruct(enemies,"Enemies.txt");
  SortEnemyTier(enemies,1);
  SortEnemyTier(enemies,2);
  SortEnemyTier(enemies,3);
  SortEnemyTier(enemies,4);
  int enemy1 = tier_1_enemy[std::rand() % tier_1_enemy.size()];
  int enemy2 = tier_2_enemy[std::rand() % tier_2_enemy.size()];
  int enemy3 = tier_3_enemy[std::rand() % tier_3_enemy.size()];
  int enemy4 = tier_4_enemy[std::rand() % tier_4_enemy.size()];
  Character enemy;
  int reward;
  int game_choice;
  int enemy_occurence = 0;
  while(true) {
    std::cin >> movement;
    std::cout << std::endl;
    if(movement == 'w') {
      if(array[character_point.x - 1][character_point.y] == 1){
        array[character_point.x][character_point.y] = 1;
        character_point.x -= 1;
        array[character_point.x][character_point.y] = 5;
      }
      else if(array[character_point.x - 1][character_point.y] == 8) {
        game_choice = std::rand() % 4;
        if(game_choice == 0) {
          reward = Memorizing();
          MiniGameWon(player,reward);
        }
        else if(game_choice == 1) {
          reward = SlotInterface(player);
          MiniGameWon(player,reward);
        }
        else if(game_choice == 2) {
          reward = Ladder();
          MiniGameWon(player,reward);
        }
        else if(game_choice == 3) {
          reward = HiLo(player);
          MiniGameWon(player,reward);
        }
      } 
      else if(array[character_point.x - 1][character_point.y] == 9){
        if(enemy_occurence == 3) {
          CreateGameInstance(enemy,enemies,enemy4);
        }
        else if(enemy_occurence == 0) {
          CreateGameInstance(enemy,enemies,enemy1);
        }
        else if(enemy_occurence == 1) {
          CreateGameInstance(enemy,enemies,enemy2);
        }        
        else if(enemy_occurence == 2) {
          CreateGameInstance(enemy,enemies,enemy3);
        }
       if(Combat(player,enemy)) {
          ++enemy_occurence;
          array[character_point.x][character_point.y] = 1; 
          character_point.x -= 1;
          array[character_point.x][character_point.y] = 5;
        }
      }
      if(player.HP <= 0) break;
    } 
    if(movement == 'a') {
      if(array[character_point.x][character_point.y - 1] == 1){
        array[character_point.x][character_point.y] = 1;
        character_point.y -= 1;
        array[character_point.x][character_point.y] = 5;
      }
      else if(array[character_point.x][character_point.y - 1] == 8){
        game_choice = std::rand() % 4;
        if(game_choice == 0) {
          reward = Memorizing();
          MiniGameWon(player,reward);
        }
        else if(game_choice == 1) {
          reward = SlotInterface(player);
          MiniGameWon(player,reward);
        }
        else if(game_choice == 2) {
          reward = Ladder();
          MiniGameWon(player,reward);
        }
        else if(game_choice == 3) {
          reward = HiLo(player);
          MiniGameWon(player,reward);
        }
      }
      else if(array[character_point.x][character_point.y - 1] == 9){
        if(enemy_occurence == 3) {
          CreateGameInstance(enemy,enemies,enemy4);
        }
        else if(enemy_occurence == 0) {
          CreateGameInstance(enemy,enemies,enemy1);
        }
        else if(enemy_occurence == 1) {
          CreateGameInstance(enemy,enemies,enemy2);
        }        
        else if(enemy_occurence == 2) {
          CreateGameInstance(enemy,enemies,enemy3);
        }
        if(Combat(player,enemy)) {
          ++enemy_occurence;
          array[character_point.x][character_point.y] = 1; 
          character_point.y -= 1;
          array[character_point.x][character_point.y] = 5;
        }
      }
      if(player.HP <= 0) break;
    } 
    if(movement == 's') {
      if(array[character_point.x + 1][character_point.y] == 1) {
        array[character_point.x][character_point.y] = 1;
        character_point.x += 1;
        array[character_point.x][character_point.y] = 5;
      }
      else if(array[character_point.x + 1][character_point.y] == 8) {
        game_choice = std::rand() % 4;
        if(game_choice == 0) {
          reward = Memorizing();
          MiniGameWon(player,reward);
        }
        else if(game_choice == 1) {
          reward = SlotInterface(player);
          MiniGameWon(player,reward);
        }
        else if(game_choice == 2) {
          reward = Ladder();
          MiniGameWon(player,reward);
        }
        else if(game_choice == 3) {
          reward = HiLo(player);
          MiniGameWon(player,reward);
        }
      }
      else if(array[character_point.x + 1][character_point.y] == 9){
        if(enemy_occurence == 3) {
          CreateGameInstance(enemy,enemies,enemy4);
        }
        else if(enemy_occurence == 0) {
          CreateGameInstance(enemy,enemies,enemy1);
        }
        else if(enemy_occurence == 1) {
          CreateGameInstance(enemy,enemies,enemy2);
        }        
        else if(enemy_occurence == 2) {
          CreateGameInstance(enemy,enemies,enemy3);
        }
        CreateGameInstance(enemy,enemies,1);
        if(Combat(player,enemy)) {
          ++enemy_occurence;
          array[character_point.x][character_point.y] = 1; 
          character_point.x += 1;
          array[character_point.x][character_point.y] = 5;
        }
      }
      if(player.HP <= 0) break;
    } 
    if(movement == 'd') {
      if(array[character_point.x][character_point.y + 1] == 1) {
        array[character_point.x][character_point.y] = 1;
        character_point.y += 1;
        array[character_point.x][character_point.y] = 5;
      }
      else if(array[character_point.x][character_point.y + 1] == 8) {
        game_choice = std::rand() % 4;
        if(game_choice == 0) {
          reward = Memorizing();
          MiniGameWon(player,reward);
        }
        else if(game_choice == 1) {
          reward = SlotInterface(player);
          MiniGameWon(player,reward);
        }
        else if(game_choice == 2) {
          reward = Ladder();
          MiniGameWon(player,reward);
        }
        else if(game_choice == 3) {
          reward = HiLo(player);
          MiniGameWon(player,reward);
        }
      }
      else if(array[character_point.x][character_point.y + 1] == 9){
        if(enemy_occurence == 3) {
          CreateGameInstance(enemy,enemies,enemy4);
        }
        else if(enemy_occurence == 0) {
          CreateGameInstance(enemy,enemies,enemy1);
        }
        else if(enemy_occurence == 1) {
          CreateGameInstance(enemy,enemies,enemy2);
        }        
        else if(enemy_occurence == 2) {
          CreateGameInstance(enemy,enemies,enemy3);
        }
        if(Combat(player,enemy)) {
          ++enemy_occurence;
          array[character_point.x][character_point.y] = 1; 
          character_point.y += 1;
          array[character_point.x][character_point.y] = 5;
        }
      }
      if(player.HP <= 0) break;
    } 
    if(character_point.x == exit_point.x && character_point.y == exit_point.y) {
      array[character_point.x][character_point.y] = 1;
      array[exit_point.x][exit_point.y] = 5;
      PrintMap(array,row,col,player);
      Win();
      break;
    }
    if(movement == 'e') break;
    PrintMap(array,row,col,player);
  }

}

/*
  Function setPathM input: the map stored in an array, the row and column value of the minigame location
  Function output: void
  What the function does: The function sets the path between the minigames and the main route, making them display "1"
  It first uses two loops to find the column value of the original route in that row;
  It then searches the left and right of the column to locate the minigame.
  Once found the minigame, set the values between the minigame and the original route in the row to "1"
*/

void SetPathM(int array[][COL],int row,int col) {
  int origin_col; 

  for (int i=col+1; i<COL; ++i) {
    if (array[row][i] == 1) {
      origin_col = i;
    }
  }
  for (int i=0; i<col; ++i) {
    if (array[row][i] == 1) {
      origin_col = i;
    }
  }

  if (origin_col > col) {
    for (int i=col+1; i<origin_col; ++i) {
      if (array[row][i] == 0) {
        array[row][i] = 1;
      }
    }
  } else {
    for (int i=origin_col+1; i<col; ++i) {
      if (array[row][i] == 0) {
        array[row][i] = 1;
      }
    }
  }
}

/*
  Function SpawnEnemiesGames input: the map stored in an array
  Function output: void
  What the function does: The function randomly spawns the locations of the enemies and minigames on the map.
  It first spawns enemies along the route ("1"s). The maximum number is 3 (excluding the last one).
  It then spawns the minigames outside the original route ("0"s). The maximum number is 3.
*/

void SpawnEnemiesGames(int array[][COL]) {
  int enemy_count = 0;
  int mini_games_count = 0;

  while(enemy_count < 3) {
    for (int i=1; i<ROW; ++i) {
      for (int j=0; j<COL; ++j) {
        if ((array[i][j]==1) && (std::rand()%5==1) && (enemy_count<3)) {
          array[i][j] = 9;
          ++enemy_count;
          break;
        }
      }
    }
  }

  while(mini_games_count < 3) {
    for (int i=ROW-2; i>0; --i) {
      for (int j=0; j<COL; ++j) {
        if ((array[i][j]==0) && (std::rand()%5==1) && (mini_games_count<3)) {
          array[i][j] = 8;
          ++mini_games_count;
          SetPathM(array, i, j);
          break;
        }
      }
    }
  }
}

void GameManual() {
  std::cout << "                        Welcome to THE GAMBLING TRAIL. "<< std::endl; 
  std::cout << "You lived your life as a decadent gambler, spending many nights away from your family" << std::endl;
  std::cout << "Your spouse pleads you stop gambling, but of course as an inccorgible bastard you do not listen" << std::endl;
  std::cout << "A game of high stakes poker goes too far and you are executed by the mafia" << std::endl;
  std::cout << "As your descent to hell begins, you see your spouse praying to the gods for your return" << std::endl;
  std::cout << "Seeing your weeping wife, you plead Satan for a chance to get out." << std::endl;
  std::cout << "Satan grants you a chance, but with a caveat. You must win the games in the casino of hell and fight your way through" << std::endl;
  std::cout << "Your character is represented by the number '5' " << std::endl;
  std::cout << "Casinos are represented by the number '8' " << std::endl;
  std::cout << "Enemies are represented by the number '9' " << std::endl;
  std::cout << "Strength increases your attack damage. Dexterity increases flee and dodge chance." << std::endl;
  std::cout << "Luck increases your critical hit chance. Dont let HP get to 0" << std::endl;
  std::cout << "(w a s d) to move. Defeat the last boss to win the game. Do not die" << std::endl;
  std::cout << std::endl;
}

int main() {
  int map[ROW][COL] = {};
  MapGeneration(map,ROW,COL);
  map[entrance.x][entrance.y] = 5; 
  EntranceExitPathMaker(map);
  SpawnEnemiesGames(map);
  int choice;
  std::vector<Character> players;
  Character player;
  Character enemy;
  InitializeStruct(players,"Players.txt");
  GameManual();
  PrintCharacters(players);
  std::cout << "Choose Your Player!" << std::endl;
  std::cin >> choice;
  std::cout << std::endl;
  choice = choice - 1;
  CreateGameInstance(player,players,choice);
  MainGameLoop(map,ROW,COL,player);
  if(player.HP <= 0) {
    Die();
  }
  return 0;
}
