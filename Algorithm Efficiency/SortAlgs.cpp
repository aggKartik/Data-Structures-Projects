// SortAlgs.cpp : Defines the entry point for the console application.
/*
*  This program tests efficiency of various sorting algorithms by counting swaps and comparisons 
*  Summary is delivered on console log and a text file (results.txt)
*  Author: Kartik Aggarwal
*  Version: 1.1
*  
*/

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
using namespace std;

int swaps[5] = { 0,0,0,0,0 }; // used globally as advised
int comps[5] = { 0,0,0,0,0 }; // used globally as advised

//Sorting Algorithms
void mergesort(int A[], int, int, int);
void quickSort(int A[], int, int);
void selectionSort(int A[], int);
void insertionSort(int A[], int);
void heapSort(int A[], int length);

//Algorithm helpers
int partition(int A[], int, int);
void heapify(int A[], int, int);
void merge(int A[], int, int, int, int, int);

//Tester Functions
void fewUniqueA(int A[], int B[], int);
void fewUniqueD(int A[], int B[], int);
void randomTester(int A[], int B[], int);
void firstNinetyTester(int A[], int B[], int);

//Helper functions
void displayResults();
void refill(int A[], int B[], int);
void clear();

ofstream file;

/*
* main function tests all sorting algorithms on 100 integer and 1000 integer datasets 
*
*/

int main() {
	//srand(time(NULL));
	file.open("results.txt");
	for (int i = 100; i <= 1000; i += 900) {
		int* A = new int[i];
		int* B = new int[i];



		randomTester(A, B, i);
		cout << "\nRandom " << i << endl;
		file << "\nRandom " << i << endl;
		displayResults();
		clear();
		delete A;
		delete B;
		A = nullptr;
		B = nullptr;
	}

	//First Ninety Sorted Last 10% random
	for (int i = 100; i <= 1000; i += 900) {
		int* A = new int[i];
		int* B = new int[i];

		firstNinetyTester(A, B, i);
		cout << "\nFirst 90% is sorted " << i << endl;
		file << "\nFirst 90% is sorted " << i << endl;
		displayResults();
		clear();
		delete A;
		delete B;
		A = nullptr;
		B = nullptr;
	}


	for (int i = 100; i <= 1000; i += 900) {
		int* A = new int[i];
		int* B = new int[i];

		fewUniqueA(A, B, i);
		cout << "\nFew Unique ascending " << i << endl;
		file << "\nFew Unique ascending " << i << endl;
		displayResults();
		clear();
		delete A;
		delete B;
		A = nullptr;
		B = nullptr;
	}


	for (int i = 100; i <= 1000; i += 900) {
		int* A = new int[i];
		int* B = new int[i];

		fewUniqueD(A, B, i);
		cout << "\nFew Unique Descending " << i << endl;
		file << "\nFew Unique Descending " << i << endl;
		displayResults();
		clear();
		delete A;
		delete B;
		A = nullptr;
		B = nullptr;
	}


	return 0;
}

void heapSort(int *A, int length) {

	for (int i = (length / 2) - 1; i >= 0; i--)
		heapify(A, i, length);

	for (int i = length - 1; i > 0; i--) {
		swap(A[0], A[i]);
		swaps[0]++;
		heapify(A, 0, i - 1);
	}

}

void heapify(int A[], int top, int bottom) {
	int largest = top;
	int l = 2 * top + 1;
	int r = 2 * top + 2;

	comps[0]++;
	if (l <= bottom && A[l] > A[largest])
		largest = l;
	if (r <= bottom && A[r] > A[largest])
		largest = r;
	if (largest != top) {
		swap(A[top], A[largest]);
		swaps[0]++;
		heapify(A, largest, bottom);
	}

}

void mergesort(int A[], int begin, int end, int length) {

	if (begin < end) {
		int middle = (begin + end) / 2;
		mergesort(A, begin, middle, length);
		mergesort(A, middle + 1, end, length);
		merge(A, begin, middle, middle + 1, end, length);
	}
}


void merge(int A[], int lStart, int lEnd, int rStart, int rEnd, int length) {

	int save = lStart;
	int *temp = new int[length];
	int k = lStart;

	while (lStart <= lEnd && rStart <= rEnd) {
		if (A[lStart] <= A[rStart])
			temp[k++] = A[lStart++];
		else
			temp[k++] = A[rStart++];
		comps[3]++;
		swaps[3]++;
	}

	while (lStart <= lEnd) {
		temp[k++] = A[lStart++];
		swaps[3]++;
	}
	while (rStart <= rEnd) { //same as above
		temp[k++] = A[rStart++];
		swaps[3]++;
	}
	for (k = save; k <= rEnd; k++) {
		A[k] = temp[k];
	}

}


void quickSort(int A[], int l, int r) {
	if (l < r) {

		int pivot = partition(A, l, r);
		quickSort(A, l, pivot - 1);
		quickSort(A, pivot + 1, r);

	}
}

int partition(int A[], int l, int r) {

	int pivot = A[l];
	int pIndex = l;

	for (int i = l + 1; i <= r; i++) {

		if (A[i] < pivot) {
			pIndex++;
			swap(A[i], A[pIndex]);
			swaps[2]++;
		}
		comps[2]++;
	}

	swap(A[l], A[pIndex]);
	swaps[2]++;
	return pIndex;
}

void selectionSort(int A[], int length) {

	int minValue;
	int minIndex;
	int loc;

	for (loc = 0; loc < length - 1; loc++) {

		minIndex = loc;
		minValue = A[loc];

		for (int j = loc + 1; j < length; j++) {
			if (A[j] < minValue) {
				minValue = A[j];
				minIndex = j;
			}
			comps[1]++;
		}
		//here is the swap
		A[minIndex] = A[loc];
		A[loc] = minValue;
		swaps[1]++;
	}

}

void insertionSort(int A[], int length) {
	int value;
	int hole;
	for (int i = 1; i < length; i++) {

		hole = i - 1;
		value = A[i];

		while (hole > 0 && A[hole] > value) {
			A[hole + 1] = A[hole];
			hole--;
			swaps[4]++;
			comps[4]++;
		}

		A[hole + 1] = value;
		swaps[4]++;
	}

}

/*
* This function tests an array that has 90% sorted members in an ascending order, with 10% of elements 
*  are random and are randomly placed
* @param int[]A - to be used to preserve data
* @param int[]B - tester array that is emptied and refilled with contents of A
* @param length - length of array received
*
*/
void fewUniqueA(int A[], int B[], int length) {
	int count = 0;
	for (int i = 0; i < length; i++) {
		A[i] = i;
		B[i] = A[i];
	}
	int *temp = new int[length]; //indicator array for hashing
	for (int i = 0; i < (length*.1); i++) {

		int index = rand() % (length - 1);

		if (temp[index] != 1) {
			A[index] = rand();
			B[index] = A[index];
			temp[index] = 1;
		}
		else { //rehash
			while (temp[index] != 1) {
				index = (index + 1) % length;
			}
			A[index] = rand();
			B[index] = A[index];
			temp[index] = 1;

		}



	}


	refill(A, B, length);
}

/*
* This function tests an array that has 90% sorted members in a descending order, with 10% of elements
*  are random and are randomly placed
* @param int[]A - to be used to preserve data
* @param int[]B - tester array that is emptied and refilled with contents of A
* @param length - length of array received
*
*/

void fewUniqueD(int A[], int B[], int length) {
	int count = 0;
	for (int i = 0; i < length; i++) {
		A[i] = (length - 1) - i;
		B[i] = A[i];
	}
	int *temp = new int[length]; //indicator array for hashing
	for (int i = 0; i < (length*.1); i++) {

		int index = rand() % (length - 1);
		if (temp[index] != 1) {
			A[index] = rand();
			B[index] = A[index];
			temp[index] = 1;
		}
		else { //rehash
			while (temp[index] != 1) {
				index = (index + 1) % length;
			}
			A[index] = rand();
			B[index] = A[index];
			temp[index] = 1;

		}

	}
	refill(A, B, length);
}
/*
* helper function that clears comparisons and swaps between tests
*/
void clear() {
	for (int i = 0; i < 5; i++) {
		comps[i] = 0;
		swaps[i] = 0;
	}
}

/*
* helper function that displays results when called
*/
void displayResults() {
	cout << "------------------------------------" << endl;
	cout << "Number of swaps selection sort: " << swaps[1];
	cout << "\t Number of comparisons: " << comps[1] << endl;
	cout << "Number of swaps insertion sort: " << swaps[4];
	cout << "\t Number of comparisons: " << comps[4] << endl;
	cout << "Number of swaps merge sort: " << swaps[3];
	cout << "\t\t Number of comparisons: " << comps[3] << endl;
	cout << "Number of swaps quick sort: " << swaps[2];
	cout << "\t\t Number of comparisons: " << comps[2] << endl;
	cout << "Number of swaps heap sort: " << swaps[0];
	cout << "\t\t Number of comparisons: " << comps[0] << endl;



	file << "------------------------------------" << endl;
	file << "Number of swaps selection sort: " << swaps[1];
	file << "\t Number of comparisons: " << comps[1] << endl;
	file << "Number of swaps insertion sort: " << swaps[4];
	file << "\t Number of comparisons: " << comps[4] << endl;
	file << "Number of swaps merge sort: " << swaps[3];
	file << "\t\t Number of comparisons: " << comps[3] << endl;
	file << "Number of swaps quick sort: " << swaps[2];
	file << "\t\t Number of comparisons: " << comps[2] << endl;
	file << "Number of swaps heap sort: " << swaps[0];
	file << "\t\t Number of comparisons: " << comps[0] << endl;


}

/*
* This function tests an array that has 90% sorted members in anscending order, with 10% of elements
*  are placed at the end and are random numbers
* @param int[]A - to be used to preserve data
* @param int[]B - tester array that is emptied and refilled with contents of A
* @param length - length of array received
*
*/

void firstNinetyTester(int A[], int B[], int length) {
	int i;
	for (i = 0; i < (length * (9 / 10)); i++) {
		A[i] = i;
		B[i] = i;
	}

	for (i; i < length; i++) {
		A[i] = rand();
		B[i] = A[i];
	}

	refill(A, B, length);
}

/*
* This function tests an array that has all random elements
* @param int[]A - to be used to preserve data
* @param int[]B - tester array that is emptied and refilled with contents of A
* @param length - length of array received
*
*/

void randomTester(int A[], int B[], int length) {
	for (int i = 0; i < length; i++) {
		A[i] = rand();
		B[i] = A[i];
	}
	refill(A, B, length);
}

/*
* This function refills B with contents of A so that it may be tested on different sorts
* with the same data formulated for A
* @param int[]A - to be used to preserve data
* @param int[]B - tester array that is emptied and refilled with contents of A
* @param length - length of array received
*
*/

void refill(int A[], int B[], int length) {

	heapSort(B, length);

	for (int i = 0; i < length; i++)
		B[i] = A[i];

	selectionSort(B, length);

	for (int i = 0; i < length; i++)
		B[i] = A[i];

	quickSort(B, 0, length - 1);

	for (int i = 0; i < length; i++)
		B[i] = A[i];

	mergesort(B, 0, length - 1, length);

	for (int i = 0; i < length; i++)
		B[i] = A[i];

	insertionSort(B, length);

}