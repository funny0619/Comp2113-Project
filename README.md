# Comp2113-Project

Team 166

Team Members

0. Qi, Lerong (Ray)
1. Baik, Seo Woon (Sunny)

Game Description - Basic Rules

0. The text-based game will take place in the form of RPG (Role-Play Game).
1. Upon starting the game, the user will be asked to select a character (among the 3-5 characters prepared by the system). Each character has a profile containing different attributes (e.g. health points (HP), strength, a specific skill). Note that all skills are quantified numeric values.
2. Once the user selects the character, all the remaining characters stored in the database immediately becomes the enemies of the user character. The user will be displayed a storyline of the game. In general, the user needs to take necessary steps to travel across the enemy realm and reach the destination.
3. The user will choose the direction keys “W”, “A”, “S”, “D” to navigate in the game. Each time the user input the direction key, there is a random possibility that the user encounters one of the enemy characters.
4. If the user encounters an enemy, he / she has to take a challenge. The challenges include various mini-games that the user has to play with the enemy. There may be multiple rounds and each time the user win / lose the game, the attributes of both the enemy and the user will be affected based on a specific algorithm.
5. Depending on the user’s direction input, it may take 5, 6, or 7 steps for the user to complete the game. If the user loses all the health points (HP) before he / she reaches the destination, he / she will be defeated.

Features and Functions (and how they satisfy the coding requirements 1-5)

0. Generation of random game sets or events
>Use seed to randomly generate terrain, mapping of game 
>Randomly place the enemy characters inside the terrain
>Although the impact on the profile attributes depend on the character, there is room for restricted randomisation for the impact when the user lose/win one game
>Randomisation inside mini-games
1. Data structures for storing game status 
>Each character has a list of three attributes: HP, Strength, Unique skill. They will all be stored under a structure named “Character”.
>Character status (e.g. HP, strength, skills, etc. will be stored throughout the game).
>Game state can also saved and loaded if quit in the middle
2. Dynamic memory management
>The memory (e.g. dynamic array space) of occupied by each user will be released after the completion of a game
>User character will be stored in a dynamic variable which its value is only available after the user declares the character
3. File input/output
>The story content will be saved in a seperate text file, and loaded when the game starts (We might prepare more than one story line and the user gets to choose one if time allows)
4. Program codes in multiple files
>Different minigames will have their own program file
