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
#include <chrono>
#include <stdio.h>
#include <random>
#include <cmath>
#include <vector>

// Take in any numberical datatype T
class QuickSort {
	private:
		// quick sort intances
		int N;
		std::vector<char> keys;
		std::vector<float> probs;

		// store runtime in microseconds
		std::chrono::duration<long, std::micro> runtime;

		// random number generator
		std::random_device rd;
		std::default_random_engine mt{rd()};
		int random_number(int min, int max);

		// swap element in a array
		void swap_element(int i, int j);

		void sort(int p, int r);

		// randomized quick sort *** Assigment specific ***
		int partition(int p, int r);
		int randomized_partition(int p, int r);
		void randomized_sort(int p, int r);

	public:
		// 1D array randomized quick sort
		QuickSort(int, std::vector<char>, std::vector<float>, bool time=false);

		~QuickSort();

		// Get the sorted array
		void get_result(std::vector<char>&, std::vector<float>&);

};

#endif
