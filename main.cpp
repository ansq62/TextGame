#include <iostream>
#include "GameWorld.h"

using namespace std;

void displayGameBegin();
void displayGameEnd();

/****************************************************************
 *This program runs an instance of the class GameWorld.  It runs*
 *a game played by the user where they traverse a 5x5 game map  *
 *to find the pot of gold(G) and avoid the pits(P) and Wumpus(W)*
 ****************************************************************/

int main()
{
	GameWorld game;
	char input; //Player input.

	displayGameBegin();
	game.populateWorld(); //Call to populate the game.
	game.displayVisibleWorld(); //Call to display visible map.

	//Loop runs til player has either won or died.
	while(game.getWon() == false && game.getAlive() == true)
	{

		cout << "***********" << endl;
		cout << "*w*a*d*c*q*" << endl; //Controls
		cout << "***********" << endl;
		cin >> input; //Player input.

		if(input == 'w' || input == 'W')
		{
			game.moveForward();
		}
		else if(input == 'a' || input == 'A')
		{
			game.turnLeft();
		}
		else if(input == 'd' || input == 'D')
		{
			game.turnRight();
		}
		else if(input == 'c' || input == 'C')
		{
			game.displayEntireWorld();
		}
		else if(input == 'q' || input == 'Q')
		{
			char confirm;
			cout << "Are you sure you want to quit?" << endl;
			cout << "*Press q to quit, or any other key to resume.*" << endl;
			cin >> confirm;
			if(confirm == 'Q' || confirm == 'q')
			{
				break; //if q, then quit game.
			}
			else
			{
				game.displayVisibleWorld();
				continue; //continue on to next loop.
			}


		}
		else //Check for any other input.
		{
			cout << "Invalid input! Please try again." << endl;
			game.displayVisibleWorld();
		}

	}

	displayGameEnd();
	return 0;
}


/***************************************************************
 * This function displays starting message and control scheme. *
 ***************************************************************/
void displayGameBegin()
{
	cout << "******************Wumpus World*************************" << endl;
	cout << "*The objective of this game is to move your character *" << endl;
	cout << "*to claim the pot of gold (G)! But careful, don't step*" << endl;
	cout << "*on a pit (P) or a Wumpus (W) or you'll die!          *" << endl;
	cout << "*******************************************************" << endl;

	cout << "*******************Controls***************************" << endl;
	cout << "w -> moves your character forward one space in the direction";
	cout << " they're facing." << endl;
	cout << "a -> turns your character left 90 degrees." << endl;
	cout << "d -> turns your character right 90 degrees." << endl;
	cout << "c -> cheat that allows you to see the whole map." << endl;
	cout << "q -> quits the game." << endl;
}


/***************************************************************
 * This function displays end game message.                    *
 ***************************************************************/
void displayGameEnd()
{
	cout << "*****************************************************" << endl;
	cout << "**************Thank you for playing******************" << endl;
	cout << "*****************************************************";
}


