#include <iostream>
#include <cstdlib>// random numbers header file
#include <ctime>// used to get date and time information
#include <string>
#include "Player.h"
#include "Dartboard.h"
using namespace std;

int main()
{
	//Create Player objects and initialise key variables to run program
	Player joe; joe.name = "Joe"; joe.bullsEyeSuccess = 71;
	Player sid; sid.name = "Sid"; sid.bullsEyeSuccess = 73;
	Player userChoice;
	Dartboard dartboard;

	//function prototypes
	void GameLoop(Player&, Player&, Dartboard&, int& add_matches);
	int GameSim(Player&, Player&, Dartboard&, int&);
	void pick_successRate(int&, int&);
	void who_goesFirst(Player&, Player&);
	int throw_single(int, int, int);
	int throw_bull(int);
	void turn_overview(Player& player);
	void calculate_wins(Player& player);
	void swap(float* xp, float* yp);
	int bubbleSort(float* arr, int n);

	srand(time(0));	//initialise random num generator using time

	userChoice.pick_successRate(joe.singleSuccess, sid.singleSuccess);
	userChoice.who_goesFirst(joe, sid);

	//Main game loop responsible for the simulations
	int matches = 0;
	int& matches_ref = matches;

	//Increase simulations to 500 later on
	for (matches_ref = matches; matches_ref < userChoice.numOfSims;)
	{
		GameLoop(joe, sid, dartboard, matches_ref);
	}

	bubbleSort(joe.winThrows, joe.sizeOfWins);
	userChoice.calculate_wins(joe);

	bubbleSort(sid.winThrows, sid.sizeOfWins);
	userChoice.calculate_wins(sid);
}

void GameLoop(Player& joe, Player& sid, Dartboard& dartboard, int& add_matches)
{
	joe.score = 301; sid.score = 301;
	joe.throws = 0; sid.throws = 0;

	while ((joe.score != 0) || (sid.score != 0))//while neither player has reduced score to 0
	{
		//Player1
		joe.GameSim(joe, sid, dartboard, add_matches);

		//Player2
		sid.GameSim(sid, joe, dartboard, add_matches);
	}
	cout << "Joe bulls count" << joe.bullsHit << "\n\n";
	cout << "Sid bulls count" << sid.bullsHit << "\n\n";


	if (joe.bullsHit > sid.bullsHit)
	{	//joe wins 
		cout << "Joe wins" << endl;
	}
	else if (joe.bullsHit < sid.bullsHit)
	{
		//sid wins
		cout << "Sid wins" << endl;
	}
	/*else
	{
		cout << "Overall draw";
	}*/
}