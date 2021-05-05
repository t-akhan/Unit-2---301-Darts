#include <iostream>
#include <cstdlib>// random numbers header file
#include <ctime>// used to get date and time information
#include <string>
#include "Player.h"
#include "Dartboard.h"
using namespace std;

int main()
{
	//Dartboard dartboard;

	//function prototypes
	int GameLoop();
	void pick_successRate(int&, int&);
	void who_goesFirst(Player&, Player&);
	int throw_single(int, int, int);
	int throw_bull(int);

	srand(time(0));	//initialise random num generator using time

	//Main game loop responsible for the simulation
	GameLoop();
}

int GameLoop()
{
	//create Player objects and initialise variables
	Player joe; joe.name = "Joe"; joe.bullsEyeSuccess = 71; joe.bullsHit = 0; joe.throws = 0; joe.score = 301;
	Player sid; sid.name = "Sid"; sid.bullsEyeSuccess = 73; sid.bullsHit = 0; sid.throws = 0; sid.score = 301;
	Player userChoice;
	Dartboard dartboard;

	userChoice.pick_successRate(joe.singleSuccess, sid.singleSuccess);
	userChoice.who_goesFirst(joe, sid);

	//int whoWon();

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

				//joe.throws++;//add one to the number of darts thrown by the player

				if (joe.score == 50 || joe.score > 70)
				{
					if (joe.score > 70)
					{
						joe.target = rand() % 20 + 1;
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
						cout << "You went below 50! Your score has been reset to value before that turn.";
					}
					//Means the returned value was 50 - the player hit the bullseye
					else if (joe.score == 0)
					{
						joe.bullsHit++;
						cout << "Bullseye count: " << joe.bullsHit << "\n";
						cout << "Number of throws: " << joe.throws << "\n";
						cout << "----------------------------------------------------------------------" << "\n\n";
						if (joe.bullsHit >= sid.bullsHit)
						{	//joe wins 
							cout << "Joe wins" << endl;
							joe.calculate_average();
						}
						else if (joe.bullsHit <= sid.bullsHit)
						{
							//sid wins
							cout << "Sid wins" << endl;
							sid.calculate_average();
						}
						return joe.score;
					}
					cout << "SCORE REMAINING: " << joe.score << "\n\n";

					/*if (throwBull(joe.bullsEyeSuccess))//if throwBull function returns true
					{
						cout << joe.name << " has hit the bullseye" << endl;
						joe.bullsHit++;//add one to the number of bullseyes thrown by the player
					}*/

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
						sid.target = rand() % 20 + 1;
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
						cout << "You went below 50! Your score has been reset to value before that turn.";
					}
					//Means the returned value was 50 - the player hit the bullseye
					else if (sid.score == 0)
					{
						sid.bullsHit++;
						cout << "Bullseye count: " << sid.bullsHit << "\n";
						cout << "Number of throws: " << sid.throws << "\n";
						cout << "----------------------------------------------------------------------" << "\n\n";
						if (joe.bullsHit >= sid.bullsHit)
						{	//joe wins 
							cout << "Joe wins" << endl;
							joe.calculate_average();
						}
						else if (joe.bullsHit <= sid.bullsHit)
						{
							//sid wins
							cout << "Sid wins" << endl;
							sid.calculate_average();
						}
						return sid.score;
					}
					cout << "SCORE REMAINING: " << sid.score << "\n\n";

					/*if (throwBull(joe.bullsEyeSuccess))//if throwBull function returns true
					{
						cout << joe.name << " has hit the bullseye" << endl;
						joe.bullsHit++;//add one to the number of bullseyes thrown by the player
					}*/

					//USE SETTERS/GETTERS
					sid.target = 0;
					returnedScore = 0;
					cout << sid.name << "'s turn Overview" << "\n" << "----------------------------------------------------------------------" << "\n\n";
				}
			}
			//ORIGINAL SID THROW FOR LOOP
			/*for (int i = 0; i < 1; i++)//Sid throws 1 darts
			{
				sid.throws++;//add one to the number of darts thrown by the player

				if (throwBull(sid.bullsEyeSuccess))
				{
					cout << sid.name << " has hit the bullseye" << endl;
					sid.bullsHit++;//add one to the number of bullseyes thrown by the player
				}
			}*/
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
		joe.calculate_average();
	}
	else if (joe.bullsHit <= sid.bullsHit)
	{
		//sid wins
		cout << "Sid wins" << endl;
		sid.calculate_average();
	}
}