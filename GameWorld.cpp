#include "GameWorld.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

/*****************************************************************
 *               Function file for GameWorld.h                   *
 *****************************************************************/


/****************************************************************
 *                     Constructor                              *
 ****************************************************************/

GameWorld::GameWorld()
{
	for(int count = 0; count < 5; count++)
	{
		for(int index = 0; index < 5; index++)
		{
			gameMap[count][index] = ' ';
		}
	}

	x = 0; //Row = y-coordinate.
	y = 0; //Column = x-coordinate.
	pits = 0;
	HERO = 'N'; //defaults facing North.
	playerX = 0; // hero xy-coordinates.
	playerY = 0;
}


/***************************************************************
 *This function displays the entire populated 5x5 game world   *
 ***************************************************************/
void GameWorld::displayEntireWorld()
{
	for(int row = 0; row < 5; row++)
	{
		cout << "|";
		for(int col = 0; col < 5; col++)
		{
			cout << gameMap[row][col] << "|";
		}
		cout << endl;
	}
}



/***************************************************************
 *This function displays only the visible spaces to the player.*
 *The spaces above, beneath, and diagonal to the character are *
 *shown and everything else is displayed as blank space.       *
 ***************************************************************/
void GameWorld::displayVisibleWorld()
{
	for(int row = 0; row < 5; row++)
	{
		cout << "|";
		for(int col = 0; col < 5; col++)
		{
			if(row >= playerY-1 && row <= playerY+1 && col >= playerX-1 && col <= playerX+1)
			{
				cout << gameMap[row][col];
				cout << "|";
			}

			else
				cout << " " << "|";
		}
		cout << endl;
	}
}



/*************************************************************
 * This function populates the game world with one enemy(W), *
 * one pot of gold(G), a random number of pits between 5 and *
 * 10, and a hero(N). These positions are generated randomly.*
 *************************************************************/
void GameWorld::populateWorld()
{
	//counters
	int i = 0;
	int j = 0;
	int k = 0;


	//For enemy.
	unsigned seed = time(0);
	srand(seed);
	x = rand() % 5;
	y = rand() % 5;
	gameMap[y][x] = 'W'; //As much as it pains me to code this as [y][x]
                         //instead of [x][y], it's only proper.

	//For Gold.
	while(i < 1)
	{
		x = rand() % 5;
		y = rand() % 5;
		if(gameMap[y][x] == ' ')
		{
			gameMap[y][x] = 'G';
			i++;
		}
	}

	//For pits.
	pits = (rand() % (10 - 5 + 1)) + 5;
	while(k < pits)
	{
		x = rand() % 5;
		y = rand() % 5;
		if(gameMap[y][x] == ' ')
		{
			gameMap[y][x] = 'P';
			k++;
		}
	}

	//For hero.
	while(j < 1)
	{
		playerX = rand() % 5;
		playerY = rand() % 5;
		if(gameMap[playerY][playerX] == ' ')
		{
			gameMap[playerY][playerX] = 'N';
			j++;
		}
	}

}


/***********************************************************
 *This function moves the hero forward one space in the    *
 *direction they are facing.                               *
 ***********************************************************/

void GameWorld::moveForward()
{
	if(HERO == 'N') //Facing North.
	{

		if(playerY == 0) //Row Boundary check.
		{
			cout << "You've hit a wall!" << endl;
			displayVisibleWorld();
		}
		else if(gameMap[playerY-1][playerX] == ' ') //If space isn't occupied.
		{
			gameMap[playerY][playerX] = ' ';
			gameMap[playerY-1][playerX] = 'N';

			playerY = playerY-1; //New hero position.
			displayVisibleWorld();
		}
		else
		{
			haveIWon(playerY-1, playerX); //If space is gold.
			amIAlive(playerY-1, playerX); //If space is enemy/pit.
		}
	}
	else if(HERO == '<') //Facing West.
	{
		if(playerX == 0) //Column boundary check.
		{
			cout << "You've hit a wall!" << endl;
			displayVisibleWorld();
		}
		else if(gameMap[playerY][playerX-1] == ' ') //If space isn't occupied.
		{
			gameMap[playerY][playerX] = ' ';
			gameMap[playerY][playerX-1] = '<';

			playerX = playerX-1;
			displayVisibleWorld();
		}
		else
		{
			haveIWon(playerY, playerX-1); //If space is gold.
			amIAlive(playerY, playerX-1); //If space is enemy/pit.
		}
	}
	else if(HERO == 'S') //Facing South.
	{
		if(playerY == 4) //Row boundary check.
		{
			cout << "You've hit a wall!" << endl;
			displayVisibleWorld();
		}
		else if(gameMap[playerY+1][playerX] == ' ') //If space isn't occupied.
		{
			gameMap[playerY][playerX] = ' ';
			gameMap[playerY+1][playerX] = 'S';

			playerY = playerY+1;
			displayVisibleWorld();
		}
		else
		{
			haveIWon(playerY+1, playerX); //If space is gold.
			amIAlive(playerY+1, playerX); //If space is enemy/pit.
		}
	}

	else if(HERO == '>') //Facing East.
	{
		if(playerX == 4) //Column boundary check.
		{
			cout << "You've hit a wall!" << endl;
			displayVisibleWorld();
		}
		else if(gameMap[playerY][playerX+1] == ' ') //If space isn't occupied.
		{
			gameMap[playerY][playerX] = ' ';
			gameMap[playerY][playerX+1] = '>';

			playerX = playerX+1;
			displayVisibleWorld();
		}
		else
		{
			haveIWon(playerY, playerX+1); //If space is gold.
			amIAlive(playerY, playerX+1); //If space is enemy/pit.
		}
	}
}

/**********************************************************
 *This function turns the hero character 90 degrees to the*
 *left.  The symbol of the hero changes depending on which*
 *direction they are facing.                              *
 **********************************************************/

void GameWorld::turnLeft()
{
	if(HERO == 'N') //Facing North.
	{
		HERO = '<';
		gameMap[playerY][playerX] = '<';
		displayVisibleWorld();
	}
	else if(HERO == '<') //Facing West.
	{
		HERO = 'S';
		gameMap[playerY][playerX] = 'S';
		displayVisibleWorld();
	}
	else if(HERO == 'S') //Facing South
	{
		HERO = '>';
		gameMap[playerY][playerX] = '>';
		displayVisibleWorld();
	}
	else if(HERO == '>') //Facing East.
	{
		HERO = 'N';
		gameMap[playerY][playerX] = 'N';
		displayVisibleWorld();
	}
	else //Player should never see this, but making sure things are working.
		cout << "--Game Error; Please Restart-- " << endl;
}


/**********************************************************
 *This function turns the hero character 90 degrees to the*
 *right. The symbol of the hero changes depending on which*
 *direction they are facing.                              *
 **********************************************************/

void GameWorld::turnRight()
{
	if(HERO == 'N') //Facing North.
	{
		HERO = '>';
		gameMap[playerY][playerX] = '>';
		displayVisibleWorld();
	}
	else if(HERO == '>') //Facing East.
	{
		HERO = 'S';
		gameMap[playerY][playerX] = 'S';
		displayVisibleWorld();
	}
	else if(HERO == 'S') //Facing South.
	{
		HERO = '<';
		gameMap[playerY][playerX] = '<';
		displayVisibleWorld();
	}
	else if(HERO == '<') //Facing West.
	{
		HERO = 'N';
		gameMap[playerY][playerX] = 'N';
		displayVisibleWorld();
	}
	else //Player should never see this, but making sure things are working.
		cout << "--Game Error; Please Restart-- " << endl;
}

/************************************************************
 *This function determines if the player has won or not.    *
 *Returns true if player has moved hero onto the Gold       *
 *position.                                                 *
 ************************************************************/

void GameWorld::haveIWon(int sizeY, int sizeX)
{
	if(gameMap[sizeY][sizeX] == 'G')
	{
		cout << "*~Congratulations! You won!~* \\^o^/" << endl;
		won = true;
	}

}

/***********************************************************
 *This function determines if the player is alive or not.  *
 *Returns true if player has moved hero onto a pit or an   *
 *enemy.                                                   *
 ***********************************************************/

void GameWorld::amIAlive(int sizeY, int sizeX)
{
	if(gameMap[sizeY][sizeX] == 'W') //Enemy position.
	{
		cout << "You've been killed by a Wumpus! *o*" << endl;
		alive = false;
	}
	else if (gameMap[sizeY][sizeX] == 'P') //Pit position.
	{
		cout << "You fell into a pit and died! x_x" << endl;
		alive = false;
	}

}
