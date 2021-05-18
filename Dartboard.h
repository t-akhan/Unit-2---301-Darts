#pragma once

class Dartboard
{
public:
    void swap(float* xp, float* yp);
    int bubbleSort(float* arr, int n);
	void printArray(int arr[], int size);

	int throw_single(int, int, int);
	int r;
	int leftOrRight;
	int bd[2][21];
protected:
	int throw_bull(int);
};

