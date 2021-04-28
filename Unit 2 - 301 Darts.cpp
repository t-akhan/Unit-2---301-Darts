#include <iostream>
#include <cstdlib>// random numbers header file//
#include <ctime>// used to get date and time information
#include <string>
#include "Player.h"
using namespace std;


//TEST COMMIT
int main()
{
	//create Player objects and initialise variables
	Player joe; joe.name = "Joe"; joe.bullsEyeSuccess = 71; joe.bullsHit = 0; joe.throws = 0; joe.singleSuccess = 80;
	Player sid; sid.name = "Sid"; sid.bullsEyeSuccess = 73; sid.bullsHit = 0; sid.throws = 0; sid.singleSuccess = 80;

	//function prototypes
	//bool throwBull(int);
	int throw_bull(int);
	int throw_single(int, int, int);

	srand(time(0));	//initialise random num generator using time

	//throw_single(50, 40, 70);
		
	while ((joe.score != 0) && (sid.score != 0))//while neither player has reduced score to 0
	{
		for (int i = 0; i < 1; i++)//Throw 1 dart per turn
		{
			//IS THE SCORE APPROACHING 50 FOR A BULLSEYE? E.G WITHIN THE "20 RANGE"
			if (joe.score > 50 && joe.score < 71)
			{
				joe.tempScore = joe.score;

				//Suitable number is found to subtract from score only ONCE - until, score = EXACTLY 50
				while (joe.tempScore != 50)
				{
					//Subtraction, to eventually reduce tempScore to 50
					joe.tempScore = joe.tempScore - joe.suitableSingle;

					//At first attempt, we haven't found the suitable dart to reduce the score to 50
					if (joe.tempScore > 50)//CURRENT PROBLEM
					{
						joe.tempScore = joe.tempScore + joe.suitableSingle;
						joe.suitableSingle++;


						cout << joe.suitableSingle << ", ";
					}
					else if (joe.tempScore == 50)
					{
						//The target is specfically selected, than from the typical random function
						joe.target = joe.suitableSingle;
						cout << "Suitable single is:" << joe.suitableSingle;
					}
				}
			}

			//joe.throws++;//add one to the number of darts thrown by the player

			//?
			

			if (joe.tempScore == 50 || joe.score > 70)
			{
				if (joe.score > 70)
				{
					joe.target = rand() % 20 + 1;
				}
				else if (joe.tempScore == 50)
				{
					joe.target = 50;
				}

				joe.suitableSingle = 1;//Reset value incase dart throw is has missed
				int returnedScore = throw_single(joe.target, joe.singleSuccess, joe.bullsEyeSuccess);

				joe.score = joe.score - returnedScore;//Takes away from 301 score after each dart is thrown
				if (joe.score < 50)
				{
					//Add back value of unsuitable dart e.g IF the dart is below 50 - this is invalid
					joe.score = joe.score + returnedScore;
					cout << "You went below 50! Your score has been reset to value before that turn.";
				}
				//Means the returned value was 50 - the player hit the bullseye
				else if (joe.score == 50)
				{
					joe.score = 0;
					joe.bullsHit++;
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
	cout << joe.name << " won the game!";
	//cout << "GAME HAS ENDED";
	/*if (joe.bullsHit >= sid.bullsHit)
	{	//joe wins 
		cout << "Joe wins" << endl;
		joe.calculate_average();
	}
	else
	{
		//sid wins
		cout << "Sid wins" << endl;
		sid.calculate_average();
	}*/
}

//target = desired value to hit, playerSingle = success rate to hit single, playerBull = success rate to hit bullseye
int throw_single(int playerTarget, int playerSingle, int playerBull)
{
	//  return result of throwing for single target with accuracy 88% (or 80% for the outer bullseye)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
					{0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	
	int r = rand() % 100 + 1;

	if (playerTarget == 50)
	{	//inner bullseye has success rate of "bullsEyeSuccess"
		if (r <= playerBull)
		{
			cout << "You hit the bull " << "\n";

			return 50;
		}
		else//number is temporary for testing (must change)
		{
			playerTarget = 0;
			playerTarget = rand() % 20 + 1;

			cout << "You didn't hit the bull, but hit: " << playerTarget << "\n";

			return playerTarget;
		}
	}
	else
	{	
		//we must be aiming for 1 to 20 single
		if (r <= playerSingle)
		{
			cout << "Successfully hit " << playerTarget << "\n";

			return playerTarget;
		}
		//if target is unsuccessful, determine whether left/right is hit
		else if (r > playerSingle)
		{
			int leftOrRight = rand() % 2 + 1;
			if (leftOrRight == 1)
			{
				cout << "You hit left of " << playerTarget << ": " << bd[0][playerTarget] << "\n\n";
				
				return bd[0][playerTarget];//left side of target
			}
			else if (leftOrRight == 2)
			{
				cout << "You hit right of " << playerTarget << ": " << bd[1][playerTarget] << "\n\n";
				
				return bd[1][playerTarget];//right side of target
			}
		}
	}
}

/*int throw_bull(int percentage) 
{
	//  Throw for the bull with percent accuracy (20<p<85)
	int random = rand() % 100 + 1;

	if (random <= (percentage - 20))
	{
		return 50;
	}
	else
	{
		return rand() % 20 + 1;
	}
}*/