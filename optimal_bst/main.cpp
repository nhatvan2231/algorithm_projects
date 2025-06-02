#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "optimal_binary_search_tree.hpp"
#include "quick_sort.hpp"

using namespace std;


int main(int argc, char **argv){
	// Open the data file
	string PATH;
	if (argc > 2 || argc < 2){
		printf("Invalid format!\n");
		printf("Usage: %s <path_to_file>\n", argv[0]);
	}
	PATH = argv[1];


	std::ifstream infile;
	infile.open(PATH);
	if (!infile){
		printf("Unable to open file\n");
		exit(1);
	}

	int N=0;					// N number of elements
	vector<char> keys;			// keys
	vector<float> probs;			// probs

	// read the key and probabilities values
	// store in a temporary value
	// insert into the vectors and update the number of elements
	char tmp_k;
	float tmp_p;
	while (infile >> tmp_k >> tmp_p){
		keys.insert(keys.end(), tmp_k);
		probs.insert(probs.end(), tmp_p);
		N++;
	}
	infile.close();

	string filename = PATH.substr(PATH.find("/")+1, PATH.size());
	filename = filename.substr(0, filename.find("."));
	// begin optimizing and printing the result
	OptimalBST obst = OptimalBST(N, keys, probs, filename);
}
