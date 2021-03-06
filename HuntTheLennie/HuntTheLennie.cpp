/*
This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

For a copy of the GNU General Public License please see <http://www.gnu.org/licenses/>.

This product includes software written by Alex Gray (alexgray2017@gmail.com)
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>

using namespace std;

class Point {
public:

	bool operator==(const Point& other) const { //Used to compare two points together

		int x = other.GetXCoord();
		int y = other.GetYCoord();

		if (x == xCoord && y == yCoord) {
			return true;
		}
		else {
			return false;
		}

	}


	// Please add constructors and other functions here.

	Point() { // Default constructor
		xCoord = 0;
		yCoord = 0;
	}

	Point(int x, int y) { // Overloaded constructor
		xCoord = x;
		yCoord = y;
	}

	void SetXCoord(int xC) {
		xCoord = xC;
		return;
	}

	void SetYCoord(int yC) {
		yCoord = yC;
		return;
	}

	int GetXCoord() const {
		return xCoord;
	}

	int GetYCoord() const {
		return yCoord;
	}

private:
	int xCoord;
	int yCoord;

};

class Screen {
public:

	Screen() { //Default constructor
		display[7][7]; //Creates a 2D array of zeros
	}

	void SetPointOnScreen(Point p, string type) {

		if (type == "empty") { //Set the location to an empty space (0)
			display[p.GetXCoord()][p.GetYCoord()] = 0;
		}
		else if (type == "player") { //Set the location to a player (1)
			display[p.GetXCoord()][p.GetYCoord()] = 1;
		}
		else if (type == "lennie") { //Set the location to a lennie (2)
			display[p.GetXCoord()][p.GetYCoord()] = 2;
		}
		else if (type == "pit") { //Set the location to a pit (3)
			display[p.GetXCoord()][p.GetYCoord()] = 3;
		}
		else if (type == "bird") { //Set the location to a bird (4)
			display[p.GetXCoord()][p.GetYCoord()] = 4;
		}
	}

	void PrintScreen() {
		char sidePiece = 186;
		char topPiece = 205;
		char fourWayPiece = 206;

		char topLeftCorner = 201;
		char topRightCorner = 187;
		char bottomLeftCorner = 200;
		char bottomRightCorner = 188;

		char leftThreePiece = 204;
		char rightThreePiece = 185;
		char topThreePiece = 203;
		char bottomThreePiece = 202;

		char playerIcon = 219;
		char playerIconLeft = 222;
		char playerIconRight = 221;

		system("CLS");
		cout << endl;
		cout << " " << topLeftCorner << topPiece << topPiece << topPiece << topThreePiece << topPiece << topPiece << topPiece << topThreePiece << topPiece << topPiece << topPiece << topThreePiece << topPiece << topPiece << topPiece << topThreePiece << topPiece;
		cout << topPiece << topPiece << topThreePiece << topPiece << topPiece << topPiece << topThreePiece << topPiece << topPiece << topPiece << topRightCorner;
		cout << endl;
		for (int x = 0; x < 7; x++) {
			for (int y = -1; y < 7; y++) {
				//Display an empty square if the square is empty, or if its not a player. Since the player can only see themselves
				if (y == -1) { //Gives it that nice gap from the edge of the screen
					cout << " ";
				}
				else if (display[x][y] == 0) {
					cout << sidePiece << "   ";
				}
				else if (display[x][y] == 2) {
					cout << sidePiece << "   ";
				}
				else if (display[x][y] == 3) {
					cout << sidePiece << "   ";
				}
				else if (display[x][y] == 4) {
					cout << sidePiece << "   ";
				}
				//Display the player icon. (P)
				else if (display[x][y] == 1) {
					cout << sidePiece << " " << playerIcon << " ";
				}
				else { //Error
					cout << "X ";
				}

			}
			cout << sidePiece;
			cout << endl;
			if (x != 6) {
				cout << " " << leftThreePiece << topPiece << topPiece << topPiece << fourWayPiece << topPiece << topPiece << topPiece << fourWayPiece << topPiece << topPiece << topPiece << fourWayPiece << topPiece << topPiece << topPiece << fourWayPiece << topPiece;
				cout << topPiece << topPiece << fourWayPiece << topPiece << topPiece << topPiece << fourWayPiece << topPiece << topPiece << topPiece << rightThreePiece;
				cout << endl;
			}
			else {
				cout << " " << bottomLeftCorner << topPiece << topPiece << topPiece << bottomThreePiece << topPiece << topPiece << topPiece << bottomThreePiece << topPiece << topPiece << topPiece << bottomThreePiece << topPiece << topPiece << topPiece << bottomThreePiece << topPiece;
				cout << topPiece << topPiece << bottomThreePiece << topPiece << topPiece << topPiece << bottomThreePiece << topPiece << topPiece << topPiece << bottomRightCorner;
				cout << endl;
			}
		}
	}

private:
	int display[7][7] = { { 0 },{ 0 } };

};

bool ranIntoLennie = false;
bool ranIntoBall = false;
bool ranIntoBird = false;

bool yoyoUp = false;
bool yoyoRight = false;
bool yoyoDown = false;
bool yoyoLeft = false;

string version = "1.1";

void ShowConsoleCursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);

}

Point CreateRandomPoint() {
	int rngOne = rand() % 7; //Random number between 0 and 7
	int rngTwo = rand() % 7; //Random number between 0 and 7

	Point newPoint = Point(rngOne, rngTwo);
	return newPoint;

}

void IsNear(Point player, Point lennie, Point pitOne, Point pitTwo, Point birdOne, Point birdTwo) {

	int playerX = player.GetXCoord();
	int playerY = player.GetYCoord();
	if (((playerX - 1) == lennie.GetXCoord() && playerY == lennie.GetYCoord()) || ((playerX + 1) == lennie.GetXCoord() && playerY == lennie.GetYCoord()) || ((playerY - 1) == lennie.GetYCoord() && playerX == lennie.GetXCoord()) || ((playerY + 1) == lennie.GetYCoord() && playerX == lennie.GetXCoord())) { //Lennie is near the player
		cout << " Lennie can be heard nearby banging his head on a wall." << endl;
	}

	if (((playerX - 1) == pitOne.GetXCoord() && playerY == pitOne.GetYCoord()) || ((playerX + 1) == pitOne.GetXCoord() && playerY == pitOne.GetYCoord()) || ((playerY - 1) == pitOne.GetYCoord() && playerX == pitOne.GetXCoord()) || ((playerY + 1) == pitOne.GetYCoord() && playerX == pitOne.GetXCoord())) { //pit one is near the player
		cout << " You sense an endless pit nearby." << endl;
	}

	if (((playerX - 1) == pitTwo.GetXCoord() && playerY == pitTwo.GetYCoord()) || ((playerX + 1) == pitTwo.GetXCoord() && playerY == pitTwo.GetYCoord()) || ((playerY - 1) == pitTwo.GetYCoord() && playerX == pitTwo.GetXCoord()) || ((playerY + 1) == pitTwo.GetYCoord() && playerX == pitTwo.GetXCoord())) { //pit two is near the player
		cout << " You sense an endless pit nearby." << endl;
	}

	if (((playerX - 1) == birdOne.GetXCoord() && playerY == birdOne.GetYCoord()) || ((playerX + 1) == birdOne.GetXCoord() && playerY == birdOne.GetYCoord()) || ((playerY - 1) == birdOne.GetYCoord() && playerX == birdOne.GetXCoord()) || ((playerY + 1) == birdOne.GetYCoord() && playerX == birdOne.GetXCoord())) { //bird one is near the player
		cout << " A screech from a nearby phoenix can be heard." << endl;
	}

	if (((playerX - 1) == birdTwo.GetXCoord() && playerY == birdTwo.GetYCoord()) || ((playerX + 1) == birdTwo.GetXCoord() && playerY == birdTwo.GetYCoord()) || ((playerY - 1) == birdTwo.GetYCoord() && playerX == birdTwo.GetXCoord()) || ((playerY + 1) == birdTwo.GetYCoord() && playerX == birdTwo.GetXCoord())) { //bird two is near the player
		cout << " A screech from a nearby phoenix can be heard." << endl;
	}

}

void CreatePoints(Point &player, Point &lennie, Point &pitOne, Point &pitTwo, Point &birdOne, Point &birdTwo) {

	do { player = CreateRandomPoint(); } while (lennie == player || lennie == pitOne || lennie == pitTwo || lennie == birdOne || lennie == birdTwo);

	Point playerUp = Point(player.GetXCoord() - 1, player.GetYCoord());
	Point playerDown = Point(player.GetXCoord() + 1, player.GetYCoord());
	Point playerLeft = Point(player.GetXCoord(), player.GetYCoord() - 1);
	Point playerRight = Point(player.GetXCoord(), player.GetYCoord() + 1);

	do { lennie = CreateRandomPoint(); } while (lennie == player || lennie == pitOne || lennie == pitTwo || lennie == birdOne || lennie == birdTwo || lennie == playerUp || lennie == playerDown || lennie == playerRight || lennie == playerLeft);

	do { pitOne = CreateRandomPoint(); } while (pitOne == player || pitOne == lennie || pitOne == pitTwo || pitOne == birdOne || pitOne == birdTwo);

	do { pitTwo = CreateRandomPoint(); } while (pitTwo == player || pitTwo == lennie || pitTwo == pitOne || pitTwo == birdOne || pitTwo == birdTwo);

	do { birdOne = CreateRandomPoint(); } while (birdOne == player || birdOne == lennie || birdOne == pitOne || birdOne == pitTwo || birdOne == birdTwo);

	do { birdTwo = CreateRandomPoint(); } while (birdTwo == player || birdTwo == lennie || birdTwo == pitOne || birdTwo == pitTwo || birdTwo == birdOne);

	return;

}

void SetupGame(Screen &gameBoard, Point playerLoc, Point lennieLoc, Point pitOneLoc, Point pitTwoLoc, Point birdOneLoc, Point birdTwoLoc) {
	cout << "Welcome to Hunt the Lennie! v" << version << endl;
	cout << "Created By Alex Gray - 2018." << endl;
	cout << "Based on the popular 'Hunt the Wumpus'." << endl;
	cout << endl;

	cout << "Instructions: " << endl;
	cout << "The Lennie will randomly spawn in the map." << endl;
	cout << "Each time you shoot your yo-yo and miss he will move to a new location." << endl;
	cout << "Your goal is to catch the lennie by getting up close and throwing your yo-yo in his direction." << endl;
	cout << "If you run into Lennie, or into a ball pit, you lose the game." << endl;
	cout << "If you run into a phoenix you will be moved to a new random location." << endl;
	cout << "When you are adjacent to something of importance, you will get a message letting you know." << endl;
	cout << endl;

	cout << "Controls: " << endl;
	cout << "Move Player: 'WASD' Keys" << endl;
	cout << "Shoot Yo-yo: Arrow Keys" << endl;
	cout << endl;

	cout << "Press enter to begin!";

	while (GetAsyncKeyState(VK_RETURN) == false && GetAsyncKeyState(VK_SPACE) == false) {
	}

	system("CLS");

	gameBoard.SetPointOnScreen(playerLoc, "player");
	gameBoard.SetPointOnScreen(lennieLoc, "lennie");
	gameBoard.SetPointOnScreen(pitOneLoc, "pit");
	gameBoard.SetPointOnScreen(pitTwoLoc, "pit");
	gameBoard.SetPointOnScreen(birdOneLoc, "bird");
	gameBoard.SetPointOnScreen(birdTwoLoc, "bird");
}

bool NearByWall(Point player, string direction) { //Used to determine if the player is near a wall
	int x = player.GetXCoord();
	int y = player.GetYCoord();

	if (direction == "up") {
		if ((x - 1) == -1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (direction == "down") {
		if ((x + 1) == 7) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (direction == "left") {
		if ((y - 1) == -1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (direction == "right") {
		if ((y + 1) == 7) {
			return true;
		}
		else {
			return false;
		}
	}

}

bool CheckShot(Point player, Point lennie, string direction) { //Checks if the yoyo shot hits the lennie or not.
	int playerX = player.GetXCoord();
	int playerY = player.GetYCoord();

	int lennieX = lennie.GetXCoord();
	int lennieY = lennie.GetYCoord();

	if (direction == "up") {
		if ((playerX - 1) == lennieX && playerY == lennieY) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (direction == "down") {
		if ((playerX + 1) == lennieX && playerY == lennieY) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (direction == "left") {
		if ((playerY - 1) == lennieY && playerX == lennieX) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (direction == "right") {
		if ((playerY + 1) == lennieY && playerX == lennieX) {
			return true;
		}
		else {
			return false;
		}
	}

}

void MoveLennie(Point &player, Point &lennie, Point &pitOne, Point &pitTwo, Point &birdOne, Point &birdTwo, Screen &gameBoard) { //Moves the location of the lennie to a new random location. This happens when you miss your shot with the yoyo

	Point playerUp = Point(player.GetXCoord() - 1, player.GetYCoord());
	Point playerDown = Point(player.GetXCoord() + 1, player.GetYCoord());
	Point playerLeft = Point(player.GetXCoord(), player.GetYCoord() - 1);
	Point playerRight = Point(player.GetXCoord(), player.GetYCoord() + 1);

	gameBoard.SetPointOnScreen(lennie, "empty");
	do { lennie = CreateRandomPoint(); } while (lennie == player || lennie == pitOne || lennie == pitTwo || lennie == birdOne || lennie == birdTwo || lennie == playerUp || lennie == playerDown || lennie == playerRight || lennie == playerLeft);
	gameBoard.SetPointOnScreen(lennie, "lennie");
	return;
}

string CheckMove(Point player, Point lennie, Point pitOne, Point pitTwo, Point birdOne, Point birdTwo, string direction) { //Checks the movement the player is going to make. If they are going to move into a pit, bird or lennie it will do the action needed

	int playerX = player.GetXCoord();
	int playerY = player.GetYCoord();

	if (direction == "up") {
		if ((playerX - 1) == lennie.GetXCoord() && playerY == lennie.GetYCoord()) { //The player is trying to move into the lennie
			return "lennie";
		}
		else if (((playerX - 1) == pitOne.GetXCoord() && playerY == pitOne.GetYCoord()) || ((playerX - 1) == pitTwo.GetXCoord() && playerY == pitTwo.GetYCoord())) { //The player is trying to move into a pit
			return "pit";
		}
		else if (((playerX - 1) == birdOne.GetXCoord() && playerY == birdOne.GetYCoord()) || ((playerX - 1) == birdTwo.GetXCoord() && playerY == birdTwo.GetYCoord())) { //The player is trying to move into a bird
			return "bird";
		}
		else {
			return "";
		}
	}
	else if (direction == "down") {
		if ((playerX + 1) == lennie.GetXCoord() && playerY == lennie.GetYCoord()) { //The player is trying to move into the lennie
			return "lennie";
		}
		else if (((playerX + 1) == pitOne.GetXCoord() && playerY == pitOne.GetYCoord()) || ((playerX + 1) == pitTwo.GetXCoord() && playerY == pitTwo.GetYCoord())) { //The player is trying to move into a pit
			return "pit";
		}
		else if (((playerX + 1) == birdOne.GetXCoord() && playerY == birdOne.GetYCoord()) || ((playerX + 1) == birdTwo.GetXCoord() && playerY == birdTwo.GetYCoord())) { //The player is trying to move into a bird
			return "bird";
		}
		else {
			return "";
		}
	}
	else if (direction == "left") {
		if ((playerY - 1) == lennie.GetYCoord() && playerX == lennie.GetXCoord()) { //The player is trying to move into the lennie
			return "lennie";
		}
		else if (((playerY - 1) == pitOne.GetYCoord() && playerX == pitOne.GetXCoord()) || ((playerY - 1) == pitTwo.GetYCoord() && playerX == pitTwo.GetXCoord())) { //The player is trying to move into a pit
			return "pit";
		}
		else if (((playerY - 1) == birdOne.GetYCoord() && playerX == birdOne.GetXCoord()) || ((playerY - 1) == birdTwo.GetYCoord() && playerX == birdTwo.GetXCoord())) { //The player is trying to move into a bird
			return "bird";
		}
		else {
			return "";
		}
	}
	else if (direction == "right") {
		if ((playerY + 1) == lennie.GetYCoord() && playerX == lennie.GetXCoord()) { //The player is trying to move into the lennie
			return "lennie";
		}
		else if (((playerY + 1) == pitOne.GetYCoord() && playerX == pitOne.GetXCoord()) || ((playerY + 1) == pitTwo.GetYCoord() && playerX == pitTwo.GetXCoord())) { //The player is trying to move into a pit
			return "pit";
		}
		else if (((playerY + 1) == birdOne.GetYCoord() && playerX == birdOne.GetXCoord()) || ((playerY + 1) == birdTwo.GetYCoord() && playerX == birdTwo.GetXCoord())) { //The player is trying to move into a bird
			return "bird";
		}
		else {
			return "";
		}
	}


}

void MovePlayer(Point &player, Point &lennie, Point &pitOne, Point &pitTwo, Point &birdOne, Point &birdTwo, Screen &gameBoard) { //Moves the location of the player. Happens when the player runs into a bird.
	gameBoard.SetPointOnScreen(player, "empty");
	do { player = CreateRandomPoint(); } while (lennie == player || lennie == pitOne || lennie == pitTwo || lennie == birdOne || lennie == birdTwo);
	gameBoard.SetPointOnScreen(player, "player");
	cout << "You have been moved by the phoenix!" << endl;
	return;
}

void OptionProcessor(int option, Point &playerLoc, Point &lennieLoc, Point &pitOneLoc, Point &pitTwoLoc, Point &birdOneLoc, Point &birdTwoLoc, Screen &gameBoard, bool &gameActive, bool &winGame) { //A switch statement is used to prossess the input that was given from the player
	int currentX = playerLoc.GetXCoord();
	int currentY = playerLoc.GetYCoord();
	switch (option) {
	case 0:
		if (NearByWall(playerLoc, "up") == false) {
			string move = CheckMove(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, "up"); //Getting the value of what the player is moving into.
			if (move == "lennie") {
				ranIntoLennie = true;
				winGame = false; //Sets the game win state to false
				gameActive = false; //Ends the game loop
			}
			else if (move == "pit") {
				ranIntoBall = true;
				winGame = false; //Sets the game win state to false
				gameActive = false; //Ends the game loop
			}
			else if (move == "bird") {
				ranIntoBird = true;
				MovePlayer(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard);
			}
			else {
				gameBoard.SetPointOnScreen(playerLoc, "empty");
				playerLoc.SetXCoord(currentX - 1);
				gameBoard.SetPointOnScreen(playerLoc, "player");
			}
		}
		break;

	case 1:
		if (NearByWall(playerLoc, "right") == false) {
			string move = CheckMove(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, "right"); //Getting the value of what the player is moving into.
			if (move == "lennie") {
				ranIntoLennie = true;
				winGame = false; //Sets the game win state to false
				gameActive = false; //Ends the game loop
			}
			else if (move == "pit") {
				ranIntoBall = true;
				winGame = false; //Sets the game win state to false
				gameActive = false; //Ends the game loop
			}
			else if (move == "bird") {
				ranIntoBird = true;
				MovePlayer(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard);
			}
			else {
				gameBoard.SetPointOnScreen(playerLoc, "empty");
				playerLoc.SetYCoord(currentY + 1);
				gameBoard.SetPointOnScreen(playerLoc, "player");
			}
		}
		break;

	case 2:
		if (NearByWall(playerLoc, "down") == false) {
			string move = CheckMove(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, "down"); //Getting the value of what the player is moving into.
			if (move == "lennie") {
				ranIntoLennie = true;
				winGame = false; //Sets the game win state to false
				gameActive = false; //Ends the game loop
			}
			else if (move == "pit") {
				ranIntoBall = true;
				winGame = false; //Sets the game win state to false
				gameActive = false; //Ends the game loop
			}
			else if (move == "bird") {
				ranIntoBird = true;
				MovePlayer(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard);
			}
			else {
				gameBoard.SetPointOnScreen(playerLoc, "empty");
				playerLoc.SetXCoord(currentX + 1);
				gameBoard.SetPointOnScreen(playerLoc, "player");
			}
		}
		break;

	case 3:
		if (NearByWall(playerLoc, "left") == false) {
			string move = CheckMove(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, "left"); //Getting the value of what the player is moving into.
			if (move == "lennie") {
				ranIntoLennie = true;
				winGame = false; //Sets the game win state to false
				gameActive = false; //Ends the game loop
			}
			else if (move == "pit") {
				ranIntoBall = true;
				winGame = false; //Sets the game win state to false
				gameActive = false; //Ends the game loop
			}
			else if (move == "bird") {
				ranIntoBird = true;
				MovePlayer(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard);
			}
			else {
				gameBoard.SetPointOnScreen(playerLoc, "empty");
				playerLoc.SetYCoord(currentY - 1);
				gameBoard.SetPointOnScreen(playerLoc, "player");
			}
		}
		break;

	case 4:
		yoyoUp = true;
		if (CheckShot(playerLoc, lennieLoc, "up") == true) {
			winGame = true; //Sets the game win state to true
			gameActive = false; //Ends the game loop
		}
		else {
			MoveLennie(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard);
		}
		break;

	case 5:
		yoyoRight = true;
		if (CheckShot(playerLoc, lennieLoc, "right") == true) {
			winGame = true; //Sets the game win state to true
			gameActive = false; //Ends the game loop
		}
		else {
			MoveLennie(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard);
		}
		break;

	case 6:
		yoyoDown = true;
		if (CheckShot(playerLoc, lennieLoc, "down") == true) {
			winGame = true; //Sets the game win state to true
			gameActive = false; //Ends the game loop
		}
		else {
			MoveLennie(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard);
		}
		break;

	case 7:
		yoyoLeft = true;
		if (CheckShot(playerLoc, lennieLoc, "left") == true) {
			winGame = true; //Sets the game win state to true
			gameActive = false; //Ends the game loop
		}
		else {
			MoveLennie(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard);
		}
		break;

	default:
		cout << "Error: Direction not found. OptionProcessor()." << endl;
		cout << "Shutting down in 5 seconds." << endl;
		Sleep(5000);
		exit(1);
		break;
	}

}

int main() {
	srand(time(NULL)); //Seeds the rng
	ShowConsoleCursor(); //Blocks the console cursor
	//Game setup
	Screen gameBoard = Screen(); //Create game board.

	//Create Random Points for location of characters. Will be ran through a function to check for duplicate coords.
	Point playerLoc = CreateRandomPoint();
	Point lennieLoc = CreateRandomPoint();
	Point pitOneLoc = CreateRandomPoint();
	Point pitTwoLoc = CreateRandomPoint();
	Point birdOneLoc = CreateRandomPoint();
	Point birdTwoLoc = CreateRandomPoint();
	CreatePoints(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc); //Checks for duplicate points

	SetupGame(gameBoard, playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc);

	//End Game setup

	bool gameActive = true;
	bool winGame = false;
	int option = -1;
	gameBoard.PrintScreen();
	IsNear(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc);

	while (gameActive == true) { //Main game loop. Exits once the game has been won or lost
		bool keyPress = false;
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			exit(1);
		}

		if ((GetKeyState('W') & 0x8000) && keyPress == false) { //Move up
			option = 0;
			keyPress = true;
		}

		if ((GetKeyState('D') & 0x8000) && keyPress == false) { //Move right
			option = 1;
			keyPress = true;
		}

		if ((GetKeyState('S') & 0x8000) && keyPress == false) { //Move down
			option = 2;
			keyPress = true;
		}

		if ((GetKeyState('A') & 0x8000) && keyPress == false) { //Move left
			option = 3;
			keyPress = true;
		}

		if ((GetKeyState(VK_UP) & 0x8000) && keyPress == false) { //Throw up
			option = 4;
			keyPress = true;
		}

		if ((GetKeyState(VK_RIGHT) & 0x8000) && keyPress == false) { //Throw right
			option = 5;
			keyPress = true;
		}

		if ((GetKeyState(VK_DOWN) & 0x8000) && keyPress == false) { //Throw down
			option = 6;
			keyPress = true;
		}

		if ((GetKeyState(VK_LEFT) & 0x8000) && keyPress == false) { //Throw left
			option = 7;
			keyPress = true;
		}

		if (keyPress == true) {
			ShowConsoleCursor();
			OptionProcessor(option, playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc, gameBoard, gameActive, winGame);
			keyPress = false;
			gameBoard.PrintScreen();

			if (ranIntoBird == true) {
				cout << " You moved into a phoenix! You have moved locations!" << endl;
				cout << endl;
				ranIntoBird = false;
			}
			else if (yoyoUp == true) {
				cout << " You shoot your Yo-yo upwards." << endl;
				Sleep(500);
				cout << " Your shot did not hit Lennie." << endl;
				cout << " Lennie has changed locations!" << endl;
				cout << endl;
				yoyoUp = false;
			}
			else if (yoyoRight == true) {
				cout << " You shoot your Yo-yo to the right." << endl;
				Sleep(500);
				cout << " Your shot did not hit Lennie." << endl;
				cout << " Lennie has changed locations!" << endl;
				cout << endl;
				yoyoRight = false;
			}
			else if (yoyoDown == true) {
				cout << " You shoot your Yo-yo downwards." << endl;
				Sleep(500);
				cout << " Your shot did not hit Lennie." << endl;
				cout << " Lennie has changed locations!" << endl;
				cout << endl;
				yoyoDown = false;
			}
			else if (yoyoLeft == true) {
				cout << " You shoot your Yo-yo to the left." << endl;
				Sleep(500);
				cout << " Your shot did not hit Lennie." << endl;
				cout << " Lennie has changed locations!" << endl;
				cout << endl;
				yoyoLeft = false;
			}

			IsNear(playerLoc, lennieLoc, pitOneLoc, pitTwoLoc, birdOneLoc, birdTwoLoc);
			Sleep(300);
		}

	}

	//Once the game has ended, decide if you won or not
	system("CLS");
	string value = "";
	if (winGame == true) {
		cout << "Your yo-yo hit Lennie!" << endl;
		cout << "Congratulations! You win!" << endl;
		cout << "Thank you for playing Hunt The Lennie v" << version << "!" << endl;
		cout << "Created By Alex Gray - 2018" << endl;
		cout << "Press 'ESC' to exit." << endl;
		while (GetAsyncKeyState(VK_ESCAPE) == false) {

		}
		exit(1);
	}
	else {
		if (ranIntoLennie == true) {
			cout << "Game over! You ran into Lennie!" << endl;
		}
		else {
			cout << "Game over! You ran into a Ball Pit!" << endl;
		}
		cout << "Better luck next time!" << endl;
		cout << "Thank you for playing Hunt The Lennie v" << version << "!" << endl;
		cout << "Created By Alex Gray - 2018" << endl;
		cout << "Press 'ESC' to exit." << endl;
		while (GetAsyncKeyState(VK_ESCAPE) == false) {

		}
		exit(1);
	}

	return 0;
}
