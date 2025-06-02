// TODO:
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
#ifndef OPTIMAL_BINARY_SEARCH_TREE_H
#define OPTIMAL_BINARY_SEARCH_TREE_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdio.h>
#include <chrono>
#include <cmath>
#include <vector>
#include "quick_sort.hpp"

class OptimalBST {
	public:
		OptimalBST(int, std::vector<char>, std::vector<float>, std::string);
	private:
		// input filename for saving
		std::string filename;

		// number of keys, keys and probability tables
		int N;
		std::vector<char> keys;
		std::vector<float> probs;

		// 2D tables
		std::vector<std::vector<char>> root_key;
		std::vector<std::vector<int>> root_id;
		std::vector<std::vector<float>> e;
		std::vector<std::vector<float>> w;

		// tree
		std::vector<char> tree;
		int tree_curr_id = 0;

		void optimize();
		void diagonal_init();
		void print_tree();
		void print_table();
		void print_e();
		void print_w();
		void print_root();
		void postorder_traversal(int, int);
		void inorder_traversal(int, int);
};
#endif
