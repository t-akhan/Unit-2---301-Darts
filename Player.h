#include <iostream>
#include <cstdlib>   // random numbers header file//
#include <ctime>	// used to get date and time information
#include <string>
using namespace std;

class Player
{
public:
	string name;
	int bullsEyeSuccess;//success rate to hit bullseye
	int singleSuccess;//success rate to hit single dart
	int throws; //store total throws of the dart
	int bullsHit;//store number of bulls hit
	int score;
	int target = 0;//desired target to hit
	int suitableSingle = 1;//1 dart throw which will lead to score = 50

	int GameLoop();
	void calculate_average();
};

