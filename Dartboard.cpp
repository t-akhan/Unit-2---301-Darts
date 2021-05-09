#include "Dartboard.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//target = desired value to hit, playerSingle = success rate to hit single, playerBull = success rate to hit bullseye
int Dartboard::throw_single(int playerTarget, int playerSingle, int playerBull)
{
	//return result of throwing for single target with accuracy 88% (or 80% for the outer bullseye)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
					{0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

	r = rand() % 100 + 1;

	if (playerTarget == 50)
	{	//inner bullseye has success rate of "bullsEyeSuccess"
		if (r <= playerBull)
		{
			cout << "You hit the bull!" << "\n";

			return 50;
		}
		else
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
			leftOrRight = rand() % 2 + 1;

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

/*int Dartboard:: throw_bull(int percentage)
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