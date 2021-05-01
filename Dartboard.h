#pragma once

class Dartboard
{
public:
	int throw_single(int, int, int);

	int r;
	int leftOrRight;
	int bd[2][21];
protected:
	int throw_bull(int);
};

