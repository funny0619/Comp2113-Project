Team 166 (The Gambling Trail)

Team Members

0. Qi, Lerong (Ray) UID:3035554672
1. Baik, Seo Woon (Sunny) UID:3035557246

Game Description - Basic Rules

0. The text-based game will take place in the form of RPG (Role-Play Game). At the main menu, the user is invited to write a seed for the game, and the map layout will be randomly generated based on the seed.
1. Upon starting the game, the user will be asked to select a character (among the 5 characters prepared by the system). Each character has a profile containing different attributes (health points (HP), strength, dexterity, and luck). Note that all skills are quantified numeric values.
2. Once the user selects the character, the user will be asked to take the necessary steps to travel across the enemy realm and reach the destination. 
3. The user will choose the direction keys “W”(up), “A”(left), “S”(down), “D”(right) to navigate in the game. On the map, "5" represents the location of the player and "1"s represent the path that the user is allowed to go. "0"s are walls so the player cannot go there.
4. The enemies are represented by "9"s on the map. They are randomly spawned along the main path and the player has to defeat them. "8"s represent the minigames and they are spawned outside the main path. We designed four minigames (described in the following section) and one of them will be randomly generated once the player reaches 8. The player will get a reward regarding their character attributes if they win the minigames.
5. The user has to play the minigames to develop new skills or level up in preparation to fight harder enemies. The challenges include various mini-games that the user has to play with the enemy. There may be multiple rounds and each time the user win / lose the game, the attributes of both the enemy and the user will be affected based on a specific algorithm.
6. Enemies in the path cannot be avoided, and the user has to fight them. If the user has not solved any challenges, it will be significantly harder to beat the enemies. Combat damage, combat sequence is determined by the attributes of the user and the enemy.

7.Strength increases your attack damage. Dexterity increases flee and dodge chance. Luck increases your critical hit chance. Game ends anytime HP value becomes smaller than 0

Included minigames:

Memorize Bananza - The enemy will test your memorization skills. It will give you a sequence of symbols, and you must input the symbols in the exact same order. 5 attempts are given.

Hi Lo - Guess if the next card in deck is higher or lower than the opponent's card. You can choose to quit in the middle or keep playing for higher rewards. But if you lose, you lose all bonuses.

Slot - You sacrifice 5 HP to play slots. If there are more than 2 symbols matching, player gets a reward

Flip the Ladder - Player can choose out of 3 themes: MTR stations, Tech Companies, Cities. Player has to guess the word that has been chosen randomly out of those three themes

Any non-standard C/C++ libraries and what features/functions in your game are supported by these libraries:

#include <random> - the library is used to utilize "std::uniform_int_distribution<int> distribution(1,100)". The uniform distribution, we found was a better to generate randomness for our combat system. 
The functions Attack(),EnemyAttack(),Flee(),Dodge(), all use this library to calculate the chances of fleeing,dodging,critical hit chance.

#include <vector> - this library is used to create Vector containers. 
The functions SortEnemyTier(), InitializeStruct(), PrintCharacters(),CreateGameInstance(). We use a struct of type Character, defined by us, to store enemies and characters. All the data of enemies and characters are store in a vector container using the vector library. The functions takes data from a vector container of struct type Character
  
#include <unistd.h> - this header defines miscellaneous symbolic constants and types, and declares miscellaneous functions.the library is used to utilize "sleep()". The functions Combat(),Slots(),Memorizing(), all use this library to pause the game loop for a certain amount of seconds to cause dramatic effect.

#include <iomanip> - is a library that is used to manipulate the output. This library is utilized for "std::setw()". PrintMap() uses this to format the output of our "map" array  when outputted.
  
Features and Functions (and how they satisfy the coding requirements 1-5)

1. Generation of random game sets or events

Use seed to randomly generate terrain, mapping of game 
Randomly place the enemy characters inside the terrain
Randomisation inside mini-games. 

2. Data structures for storing game status 

Each character has a list of attributes: HP, Strength, Dexterity, Luck, Index, Difficulty. They will all be stored under a structure named “Character”.
Vector containers store difficulty of enemies, multitude of "Character" structures for avaialabe enemies.
Arrays are used store information that needs to be selected or outputted.

3. Dynamic memory management

Dynamic arrays are used in the minigame, Memorizne Bananza, to accomodate unknown amount of user input.
Vectors are used to store structs of Characters. The amount of Characters or enemies can be changed by adding new enemies or characters in the text file, no code needs to be changed. So it is dynamic

4. File input/output

The data of avaialbe players and avaialbe enemies are stored in seperate files called Enemies.txt and Players.txt. The function IntilializeStruct() reads in data from the file and stores in a vector of structs of type Character

5. Program codes in multiple files

Different minigames will have their own program file. Combat systems are in different files. Availabe character actions are in seperate files. A Makefile is provided for correct complilation. 

Compilation Instructions:
Tested on academy server, works on x2go, but does not work properly on Putty. Please use x2go when testing on academy server for proper compilation. It is important when testing x2go is used NOT Putty or SSH client. Use x2go for correct compilation 

Best when terminal window covers at least half the screen.

go to the directory where all the source files are with terminal. 

type the following into the terminal:

make -f makefile

then run the program Gambling_Trail:
./Gambling_Trail

Input seed and follow the instructions!


