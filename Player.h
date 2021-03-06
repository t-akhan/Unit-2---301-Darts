#include <iostream>
#include <cstdlib>   // random numbers header file//
#include <ctime>	// used to get date and time information
#include <string>
#include "Dartboard.h"
using namespace std;

class Player
{
public:
	void GameLoop(Player&, Player&, Dartboard&, int&);//Main game loop
	int GameSim(Player&, Player&, Dartboard&, int&);
	void calculate_average();
	void pick_successRate(int&, int&);
	void who_goesFirst(Player&, Player&);
	void turn_overview(Player&);
	void calculate_wins(Player&);

	
	string name;
	int bullsEyeSuccess;//success rate to hit bullseye
	int singleSuccess = 80;//success rate to hit single dart
	float throws = 0; //store total throws of the dart
	int totalThrows = 0;
	int bullsHit = 0;//store number of bulls hit
	int score;//the score that players must bring down to win
	int target = 0;//desired target to hit
	int numOfSims = 26;
	int singleSelect[21] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 50 };
	float winThrows[25];
	int sizeOfWins = sizeof(winThrows) / sizeof(winThrows[0]);
	int suitableSingle = 1;//1 dart throw which will lead to score = 50
	bool goesFirst = false;//Allows user to pick who goes first
};