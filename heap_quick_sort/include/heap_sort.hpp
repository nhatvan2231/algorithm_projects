/******************************************
 *********** HEAP SORT *******************
*******************************************/
// This class take the input of the Z array,
// X array in 2D, and n number of elements
// with an additional argument time to
// measurement the runtime. It can return
// the sorted array X and save the runtime
// and sorted array X to a file.
//
#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <chrono>
#include <cmath>

template <class T> class HeapSort {
	private:
		// Heap sort intances
		int N; // n number of elements
		T *Z; // store the Z values
		T *X; // store the X values
		T *D; // store the Euclidean distance
		int heap_size; // Keep track of heap size after build max heap

		// store runtime in micrseconds
		std::chrono::duration<long, std::micro> runtime;

		// Calculate Euclidean distance
		T distance(int index);

		// swap element in a array
		void swap_element(int i, int j);

		// Calculate the childrens and parent of node i
		int parent(int index);
		int left_child(int index);
		int right_child(int index);

		// Build the heap
		void build_max_heap();

		// 2D heap sort max heapify *** Assignment specific ***
		void max_heapify(int index);
		void sort();

	public:
		// Constructor storing array A and B to Z and X and size to n
		// Record the running time if time is true
		HeapSort(int size, T *A, T *B, bool time = false);

		// Destructor delete array Z and X
		~HeapSort();

		// Return the sorted array
		T* get_result();

		// Save sorted array to file with runtime on the first line
		void save_result(char * path="heapsorted_points.txt");
};
#endif
