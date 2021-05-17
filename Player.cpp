#include "Player.h"
#include "Dartboard.h"
#include <iostream>

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

/*int valueCounter(Player player, int i)
{
	for (int j : player.winThrows)
	{
		int count = i;

		if (j == player.winThrows[count])
		{
			count++;
		}
	}
}*/