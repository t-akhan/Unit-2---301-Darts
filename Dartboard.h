#pragma once

class Dartboard
{
public:
    void swap(int* xp, int* yp);
    void bubbleSort(int arr[], int n);
	void printArray(int arr[], int size);

	int throw_single(int, int, int);
	int r;
	int leftOrRight;
	int bd[2][21];
protected:
	int throw_bull(int);
};

