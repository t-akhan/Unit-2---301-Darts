#include "Player.h"
#include "Dartboard.h"
#include <iostream>

int Player::GameSim(Player& player, Player& player2, Dartboard& dartboard, int& add_matches)
{
	//PLAYER 1
	if (player.goesFirst == true)
	{
		for (int i = 0; i < 1; i++)//Throw 1 dart per turn
		{
			player.throws++;//add one to the number of darts thrown by the player

			//IS THE SCORE APPROACHING 50 FOR A BULLSEYE? E.G WITHIN THE "20 RANGE"
			if (player.score > 50 && player.score < 71)
			{
				//Suitable number is found to subtract from score only ONCE - until, score = EXACTLY 50
				while (player.score != 50)
				{
					//Subtraction, to eventually reduce Score to 50
					player.score = player.score - player.suitableSingle;

					//At first attempt, we haven't found the suitable dart to reduce the score to 50
					if (player.score > 50)
					{
						player.score = player.score + player.suitableSingle;
						player.suitableSingle++;
					}
					else if (player.score == 50)
					{
						//The target is specfically selected, than from the typical random function
						player.target = player.suitableSingle;
					}
				}
			}

			if (player.score == 50 || player.score > 70)
			{
				if (player.score > 70)
				{
					player.target = rand() % 21;
					player.target = player.singleSelect[player.target];
				}
				else if (player.score == 50)
				{
					player.target = 50;
				}

				player.suitableSingle = 1;//Reset value incase dart throw has missed
				int returnedScore = dartboard.throw_single(player.target, player.singleSuccess, player.bullsEyeSuccess);

				player.score = player.score - returnedScore;//Takes away from 301 score after each dart is thrown

				if (player.score < 50 && player.score > 0)
				{
					//Add back value of unsuitable dart e.g IF the dart is below 50 - this is invalid
					player.score = player.score + returnedScore;
					cout << player.name << " went below 50! Your score has been reset to value before that turn.";
				}
				//Means the returned value was 50 - the player hit the bullseye
				else if (player.score == 0)
				{
					if (player.bullsHit < 25)
					{
						player.winThrows[player.bullsHit] = player.throws;
					}

					player.bullsHit++;

					player.turn_overview(player);
					add_matches++;
					return player.score;
				}

				player.turn_overview(player);

				//USE SETTERS/GETTERS
				player.target = 0;
				returnedScore = 0;
			}
		}

		//Checks if player1 went first, so that player2 can go next
		if (player.goesFirst == true)
		{
			player2.goesFirst = true;
		}
	}
}

void Player::calculate_average()
{
	double ave = 0;
	ave = ((double)throws / bullsHit);//calculate the average, i.e. the total number of darts thrown divided by the number of bulls hit
	cout << "it took " << name << " an average of " << ave << " throws of the dart to hit the bullseye\n";//return the average
}

void Player::pick_successRate(int& joe_accu, int& sid_accu)
{
	cout << "Select the success rate of " << "Joe" << "'s, between 1% - 100%: " << "\n";
	cin >> joe_accu;

	if (joe_accu >= 1 && joe_accu <= 100)
	{
		cout << "Success rate of: " << joe_accu << " has been selected.\n\n";
	}
	else
	{
		joe_accu = 80;
		cout << "Success rate of: " << joe_accu << " has been selected.\n\n";
	}

	cout << "Select the success rate of " << "Sid" << "'s, between 1% - 100%: " << "\n";
	cin >> sid_accu;

	if (sid_accu >= 1 && sid_accu <= 100)
	{
		cout << "Success rate of: " << sid_accu << " has been selected.\n\n";
	}
	else
	{
		sid_accu = 80;
		cout << "Success rate of: " << sid_accu << " has been selected.\n\n";
	}
}

void Player::who_goesFirst(Player& joe_ref, Player& sid_ref)
{
	cout << "Please select if Joe or Sid will first:\n"
		<< "1 = Joe\n" << "0 = Sid\n\n";

	//Variables that determines which player is initially selected
	int playerSelect; cin >> playerSelect;

	if (playerSelect == 1)
	{
		joe_ref.goesFirst = true;
		cout << "Joe has been selected" << "\n\n";
	}
	else if (playerSelect == 0)
	{
		sid_ref.goesFirst = true;
		cout << "Sid has been selected" << "\n\n";
	}
	else
	{
		cout << "Option is invalid, Joe has been selected.";
	}
}

void Player::turn_overview(Player& player)
{
	player.totalThrows++;

	cout << "Number of throws for match: " << player.throws << "\n";
	cout << "Total throws count: " << player.totalThrows << "\n";
	cout << "Total Bullseye count: " << player.bullsHit << "\n";
	cout << "----------------------------------------------------------------------\n\n";

	if(player.score == 0)
	{
		cout << player.name << " wins\n";
	}
}

void Player::calculate_wins(Player& player)
{
	//int n = sizeof(player.winThrows) / sizeof(player.winThrows[0]);
	//dartboard.bubbleSort(player.winThrows, n);

	cout << "Across " << player.numOfSims - 1 << " matches, " << player.name << " won:\n\n";

	int dict[25] = { 0 };//Keeps track of values we have calculated percentage for
	int dictIndex = 0;//Keeps track of unique number in the winThrows array

	for (int i = 0; i < 25; i++)//change 25 to const var
	{
		float percent = 0;
		float count = 0;
		bool exists = false;//Keeps track of value if it already exists withiin the dict array

		for (int k = 0; k < dictIndex; k++)
		{
			if (dict[k] == player.winThrows[i])//Will break out of for loop if the value exists
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
		for (int j : player.winThrows)
		{
			if (j == player.winThrows[i] && player.winThrows[i] > 0)
			{
				count++;
			}
		}

		//Increments within the array which indicates that value now exists, so that you can avoid this
		if (count > 0)
		{
			
			dict[dictIndex] = player.winThrows[i];
			dictIndex++;

			percent = (1 * count / 25) * 100;

			if (percent > 0)
			{
				cout << percent << "% of matches by " << player.winThrows[i] << " throws of the dart.\n\n";
			}
		}
	}
}