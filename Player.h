#include <iostream>
#include <cstdlib>   // random numbers header file//
#include <ctime>	// used to get date and time information
#include <string>
using namespace std;

class Player
{
public:
	int GameLoop();//Main game loop
	void calculate_average();
	void pick_successRate(int&, int&);
	void who_goesFirst(Player&, Player&);
	
	string name;
	int bullsEyeSuccess;//success rate to hit bullseye
	int singleSuccess = 80;//success rate to hit single dart
	int throws = 0; //store total throws of the dart
	int totalThrows = 0;
	int bullsHit = 0;//store number of bulls hit
	int score;//the score that players must bring down to win
	int target = 0;//desired target to hit
	int suitableSingle = 1;//1 dart throw which will lead to score = 50
	bool goesFirst = false;//Allows user to pick who goes first
};

