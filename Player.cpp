#include "Player.h"
#include "Dartboard.h"
#include <iostream>

void Player:: calculate_average()
{
	double ave = 0;
	ave = ((double)throws / bullsHit);//calculate the average, i.e. the total number of darts thrown divided by the number of bulls hit
	cout << "it took " << name << " an average of " << ave << " throws of the dart to hit the bullseye" << endl;//return the average
}