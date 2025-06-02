/******************************************
 *********** QUICK SORT *******************
*******************************************/
// This class take the input of the Z array,
// X array in 2D, and n number of elements
// with an additional argument time to
// measurement the runtime. It can return
// the sorted array X and save the runtime
// and sorted array X to a file.

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <chrono>
#include <random>
#include <cmath>
#include <vector>

// Take in any numberical datatype T
template <class T> class QuickSort {
	private:
		// quick sort intances
		int N;
		T *Z;
		T *X;
		T *D;

		// store runtime in microseconds
		std::chrono::duration<long, std::micro> runtime;

		// random number generator
		std::random_device rd;
		std::default_random_engine mt{rd()};
		int random_number(int min, int max);

		// Calculate Euclidean distance
		T distance(int index);

		// swap element in a array
		void swap_element(int i, int j);

		// Normal quick sort
		void sort(int p, int r);

		int partition(int p, int r);
		int randomized_partition(int p, int r);
		void randomized_sort(int p, int r);

	public:
		// 1D array randomized quick sort
		//QuickSort(T *A, int size, bool time=false);

		// 2D array randomized quick sort
		QuickSort(int size, T*, T*, bool time=false);
		~QuickSort();

		// Get the sorted array
		T* get_result();

		// Save result to a file
		void save_result(char * file="quicksorted_points.txt");
};

#endif
