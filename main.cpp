#include <iostream>
#include <cstdlib>// random numbers header file
#include <ctime>// used to get date and time information
#include <string>
#include "Player.h"
#include "Dartboard.h"
#include<set>
using namespace std;

int main()
{
	//create Player objects and initialise variables
	Player joe; joe.name = "Joe"; joe.bullsEyeSuccess = 71;
	Player sid; sid.name = "Sid"; sid.bullsEyeSuccess = 73;
	Player userChoice;
	Dartboard dartboard;

	//function prototypes
	int GameLoop(Player&, Player&, Dartboard&, int& add_matches);
	void pick_successRate(int&, int&);
	void who_goesFirst(Player&, Player&);
	int throw_single(int, int, int);
	int throw_bull(int);
	void turn_overview(Player& player);
	void swap(float* xp, float* yp);
	int bubbleSort(float* arr, int n);
	void printArray(int arr[], int size);

	srand(time(0));	//initialise random num generator using time

	userChoice.pick_successRate(joe.singleSuccess, sid.singleSuccess);
	userChoice.who_goesFirst(joe, sid);

	//Main game loop responsible for the simulations
	int matches = 0;
	int& matches_ref = matches;

	//Increase simulations to 500 later on
	for (matches_ref = matches; matches_ref < 26;)
	{
		GameLoop(joe, sid, dartboard, matches_ref);
	}

	int n = sizeof(joe.winThrows) / sizeof(joe.winThrows[0]);
	bubbleSort(joe.winThrows, n);

	int dict[25] = { 0 };//Keeps track of values we have calculated percentage for
	int dictIndex = 0;//Keeps track of unique number in the winThrows array

	for (int i = 0; i < 25; i++)//change 25 to const var
	{
		float percent = 0;
		float count = 0;
		bool exists = false;//Keeps track of value if it already exists withiin the dict array

		for (int k = 0; k < dictIndex; k++)
		{
			if (dict[k] == joe.winThrows[i])//Will break out of for loop if the value exists
			{
				exists = true;
				break;
			}
		}

		//Continues on for the next iteration of the above for loop
		if (exists == true)
		{
			continue;
		}

		//If a duplicate value exists, count keeps track of the amount of said value
		for (int j : joe.winThrows)
		{
			if (j == joe.winThrows[i] && joe.winThrows[i] > 0)
			{
				count++;
			}
		}

		//Increments within the array which indicates that value now exists, so that you can avoid this
		if (count > 0)
		{
			dict[dictIndex] = joe.winThrows[i];
			dictIndex++;

			//cout << "Test 1: " << joe.winThrows[i] << "\n\n";

			percent = (1 * count / 25) * 100;

			if (percent > 0)
			{
				cout << percent << "% of these were won by " << joe.winThrows[i] << " throws of the dart.\n\n";
			}
		}
	}
}

int GameLoop(Player& joe, Player& sid, Dartboard& dartboard, int& add_matches)
{
	//int whoWon();
	joe.score = 301; sid.score = 301;
	joe.throws = 0; sid.throws = 0;

	while ((joe.score != 0) || (sid.score != 0))//while neither player has reduced score to 0
	{
		//PLAYER 1
		if (joe.goesFirst == true)
		{
			for (int i = 0; i < 1; i++)//Throw 1 dart per turn
			{
				joe.throws++;//add one to the number of darts thrown by the player

				//IS THE SCORE APPROACHING 50 FOR A BULLSEYE? E.G WITHIN THE "20 RANGE"
				if (joe.score > 50 && joe.score < 71)
				{
					//Suitable number is found to subtract from score only ONCE - until, score = EXACTLY 50
					while (joe.score != 50)
					{
						//Subtraction, to eventually reduce Score to 50
						joe.score = joe.score - joe.suitableSingle;

						//At first attempt, we haven't found the suitable dart to reduce the score to 50
						if (joe.score > 50)
						{
							joe.score = joe.score + joe.suitableSingle;
							joe.suitableSingle++;
						}
						else if (joe.score == 50)
						{
							//The target is specfically selected, than from the typical random function
							joe.target = joe.suitableSingle;
							cout << "Joe's suitable single is:" << joe.suitableSingle << "\n" <<
								"After successfully calculating single, score is now: " << joe.score << "\n\n";
						}
					}
				}

				if (joe.score == 50 || joe.score > 70)
				{
					if (joe.score > 70)
					{
						joe.target = rand() % 21;
						joe.target = joe.singleSelect[joe.target];
					}
					else if (joe.score == 50)
					{
						joe.target = 50;
					}

					joe.suitableSingle = 1;//Reset value incase dart throw has missed
					int returnedScore = dartboard.throw_single(joe.target, joe.singleSuccess, joe.bullsEyeSuccess);

					joe.score = joe.score - returnedScore;//Takes away from 301 score after each dart is thrown

					if (joe.score < 50 && joe.score > 0)
					{
						//Add back value of unsuitable dart e.g IF the dart is below 50 - this is invalid
						joe.score = joe.score + returnedScore;
						cout << "Joe went below 50! Your score has been reset to value before that turn.";
					}
					//Means the returned value was 50 - the player hit the bullseye
					else if (joe.score == 0)
					{
						if (joe.bullsHit < 26)//change to 25?
						{
							joe.winThrows[joe.bullsHit] = joe.throws;
							//FIRST VALUE
							cout << joe.winThrows[joe.bullsHit] << "*****************************************************************************\n";
						}
						
						joe.bullsHit++;

						joe.turn_overview(joe);
						add_matches++;
						return joe.score;
						cout << "RETURN TEST";
					}
					cout << "SCORE REMAINING: " << joe.score << "\n\n";

					joe.turn_overview(joe);

					//USE SETTERS/GETTERS
					joe.target = 0;
					returnedScore = 0;
					cout << joe.name << "'s turn Overview" "\n" << "----------------------------------------------------------------------" << "\n\n";
				}
			}

			//Checks if Joe went first, so that Sid can go next
			if (joe.goesFirst == true)
			{
				sid.goesFirst = true;
			}
		}

		//PLAYER 2
		if (sid.goesFirst == true)
		{
			for (int i = 0; i < 1; i++)//Throw 1 dart per turn
			{
				sid.throws++;//add one to the number of darts thrown by the player

				//IS THE SCORE APPROACHING 50 FOR A BULLSEYE? E.G WITHIN THE "20 RANGE"
				if (sid.score > 50 && sid.score < 71)
				{
					//Suitable number is found to subtract from score only ONCE - until, score = EXACTLY 50
					while (sid.score != 50)
					{
						//Subtraction, to eventually reduce Score to 50
						sid.score = sid.score - sid.suitableSingle;

						//At first attempt, we haven't found the suitable dart to reduce the score to 50
						if (sid.score > 50)
						{
							sid.score = sid.score + sid.suitableSingle;
							sid.suitableSingle++;
						}
						else if (sid.score == 50)
						{
							//The target is specfically selected, than from the typical random function
							sid.target = sid.suitableSingle;
							cout << "Sid's suitable single is:" << sid.suitableSingle << "\n" <<
								"After successfully calculating single, score is now: " << sid.score << "\n\n";
						}
					}
				}

				if (sid.score == 50 || sid.score > 70)
				{
					if (sid.score > 70)
					{
						sid.target = rand() % 21;
						sid.target = sid.singleSelect[sid.target];
					}
					else if (sid.score == 50)
					{
						sid.target = 50;
					}

					sid.suitableSingle = 1;//Reset value incase dart throw has missed
					int returnedScore = dartboard.throw_single(sid.target, sid.singleSuccess, sid.bullsEyeSuccess);

					sid.score = sid.score - returnedScore;//Takes away from 301 score after each dart is thrown

					if (sid.score < 50 && sid.score > 0)
					{
						//Add back value of unsuitable dart e.g IF the dart is below 50 - this is invalid
						sid.score = sid.score + returnedScore;
						cout << "Sid went below 50! Your score has been reset to value before that turn.";
					}
					//Means the returned value was 50 - the player hit the bullseye
					else if (sid.score == 0)
					{
						sid.bullsHit++;
						
						sid.turn_overview(sid);
						add_matches++;
						return sid.score;
						cout << "RETURN TEST";
						//START FROM HERE
					}
					cout << "SCORE REMAINING: " << sid.score << "\n\n";

					sid.turn_overview(sid);

					//USE SETTERS/GETTERS
					sid.target = 0;
					returnedScore = 0;
					cout << sid.name << "'s turn Overview" << "\n" << "----------------------------------------------------------------------" << "\n\n";
				}
			}
		}
		//Checks if Sid went first, so that Joe can go next
		if (sid.goesFirst == true)
		{
			joe.goesFirst = true;
		}
	}

	if (joe.bullsHit >= sid.bullsHit)
	{	//joe wins 
		cout << "Joe wins" << endl;
		//joe.calculate_average();
	}
	else if (joe.bullsHit <= sid.bullsHit)
	{
		//sid wins
		cout << "Sid wins" << endl;
		//sid.calculate_average();
	}
	else
	{
		cout << "Overall draw";
	}
}