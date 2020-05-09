Team 166 (The Legend of Data)

Team Members

0. Qi, Lerong (Ray)
1. Baik, Seo Woon (Sunny)

Game Description - Basic Rules

0. The text-based game will take place in the form of RPG (Role-Play Game). At the main menu, the user is invited to write a seed for the game, and the map layout will be randomly generated based on the seed.
1. Upon starting the game, the user will be asked to select a character (among the 5 characters prepared by the system). Each character has a profile containing different attributes (health points (HP), strength, dexterity, and luck). Note that all skills are quantified numeric values.
2. Once the user selects the character, the user will be asked to take the necessary steps to travel across the enemy realm and reach the destination. 
3. The user will choose the direction keys “W”(up), “A”(left), “S”(down), “D”(right) to navigate in the game. On the map, "5" represents the location of the player and "1"s represent the path that the user is allowed to go. "0"s are walls so the player cannot go there.
4. The enemies are represented by "9"s on the map. They are randomly spawned along the main path and the player has to defeat them. "8"s represent the minigames and they are spawned outside the main path. We designed four minigames (described in the following section) and one of them will be randomly generated once the player reaches 8. The player will get a reward regarding their character attributes if they win the minigames.
5. The user has to play the minigames to develop new skills or level up in preparation to fight harder enemies. The challenges include various mini-games that the user has to play with the enemy. There may be multiple rounds and each time the user win / lose the game, the attributes of both the enemy and the user will be affected based on a specific algorithm.

Included minigames:

Match Frenzy!: You are given a few seconds to see the layout of the board, then it is hidden throughout the game. You find pairs after the tiles are hidden (Like Mahjong Solitaire)

Memorize Bananza!: The enemy will test your memorization skills. It will give you a sequence of symbols, and you must input the symbols in the exact same order.

Hi Lo: Guess if the next card in deck is higher or lower than the opponent's card. You can choose to quit in the middle or keep playing for higher rewards. But if you lose, you lose all bonuses.

Slots: You sacrifice HP to play slots. Rewards are random!

(Potential Additions if have time)

5. Enemies in the path cannot be avoided, and the user has to fight them. If the user has not solved any challenges, it will be significantly harder to beat the enemies. Combat damage, combat sequence is determined by the attributes of the user and the enemy.
6. Depending on the user’s direction input, it may take 5, 6, or 7 steps for the user to complete the game. If the user loses all the health points (HP) before he / she reaches the destination, he / she will be defeated.

Features and Functions (and how they satisfy the coding requirements 1-5)

1. Generation of random game sets or events

Use seed to randomly generate terrain, mapping of game 
Randomly place the enemy characters inside the terrain
Although the impact on the profile attributes depend on the character, there is room for restricted randomisation for the impact when the user lose/win one game
Randomisation inside mini-games

2. Data structures for storing game status 

Each character has a list of three attributes: HP, Strength, Unique skill. They will all be stored under a structure named “Character”.
Character status (e.g. HP, strength, skills, etc. will be stored throughout the game).
Game state can also saved and loaded if quit in the middle

3. Dynamic memory management

The memory (e.g. dynamic array space) of occupied by each user will be released after the completion of a game
User character will be stored in a dynamic variable which its value is only available after the user declares the character
Amount of User input during minigames is not known beforehand, so we can create dynamic variables to dynamically allocate storage of user input during runtime

4. File input/output

The story content will be saved in a seperate text file, and loaded when the game starts (We might prepare more than one story line and the user gets to choose one if time allows)

5. Program codes in multiple files

Different minigames will have their own program file
