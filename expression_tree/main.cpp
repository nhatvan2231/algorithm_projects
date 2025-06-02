#include <fstream>
#include <string>
#include "tree_expression.hpp"

using namespace std;


int main(int argc, char **argv){
	// Takes in a file
	string PATH;
	if (argc > 2 || argc < 2){
		printf("Invalid format!\n");
		printf("Usage: %s <path_to_file>\n", argv[0]);
	}
	PATH = argv[1];

	// Open the data file
	std::ifstream infile;
	infile.open(PATH);
	// Check if file is accessable
	if (!infile){
		printf("Unable to open file\n");
		exit(1);
	}

	// Create a tree expression object
	TreeExpr tree;

	// postfix expression
	string line;
	while (getline(infile, line)){
			printf("\n\n----------New Expression-----------\n");
			printf("Postfix:\n\t%s\n",line.c_str());
			// Build binary expression tree and display
			if(!tree.postfix_to_tree(line)) continue;
			// Compute the infix expression
			printf("\nInfix:\n\t");
			tree.infix();
			// Compute the prefix expression and expression evaluation
			printf("Prefix:\n\t");
			tree.prefix();
	}
	// close file
	infile.close();
}
