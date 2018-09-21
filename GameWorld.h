#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

/**************************************************************
 *                     Header File                            *
 **************************************************************/

class GameWorld
{
	private:
	char gameMap[5][5]; //Game map
	int x;   //COLS
	int y;   //ROWS
	int pits;
	char HERO; //Player direction variable.
	int playerX; //COLS
	int playerY; //ROWS
	bool won = false;
	bool alive = true;



	public:
	GameWorld(); //Constructor

	//World display.
	void displayEntireWorld();
	void displayVisibleWorld();

	//Creates active world.
	void populateWorld();



	//Character movement functions.
	void moveForward();
	void turnLeft();
	void turnRight();

	//Bool functions.
	void haveIWon(int, int);
	void amIAlive(int, int);

	bool getWon()
	{return won;}
	bool getAlive()
	{return alive;}


};



#endif /* GAMEWORLD_H_ */
