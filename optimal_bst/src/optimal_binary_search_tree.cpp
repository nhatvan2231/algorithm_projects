#include "optimal_binary_search_tree.hpp"

OptimalBST::OptimalBST(int n, std::vector<char> k, std::vector<float> p, std::string s){
	this->filename = "results/"+s+"_result.txt";
	// sort the tables in alphabetic order
	QuickSort sort = QuickSort(n, k, p);
	// storing number of elements, keys, and probabilities
	this->N = n;
	sort.get_result(this->keys, this->probs);

	// resise the 1D tables vector
	tree.resize(N); // Binary tree
	root_key.resize(N);	// root table based on key
	root_id.resize(N);	// root table based on index
	e.resize(N+1);			// storing the cost of optimal binary tree
	w.resize(N+1);			// storing accumulative sum of the probabilities
	// resize the 2D tables vector
	// *only 0 to N*
	for (int i=0; i<N; i++){
		root_key[i].resize(N);
		root_id[i].resize(N);
		// initialize elements to not a number
		e[i].resize(N+1,std::nan("0"));
		w[i].resize(N+1,std::nan("0"));
	}
	// initialize elements N+1
	e[e.size()-1].resize(N+1,std::nan("0"));
	w[w.size()-1].resize(N+1,std::nan("0"));

	// Calculate the optimal binary tree
	optimize();

	// Print the keys probability table
	print_table();
	// Print e table
	print_e();
	//print_w();
	// Print root table
	print_root();
	// Print inorder and postorder traversal
	print_tree();
}


void OptimalBST::optimize(){
	diagonal_init();
	// l number of nodes in a tree
	for (int l=1; l<=N; l++){
		// pos is number of possible optimal solutions with l
		int pos = N - l + 1;
		for (int i=0; i < pos; i++){
			// (i,j) is used for indexing
			// j is the size of the tree or l relatively to i
			int j = i + l;
			e[i][j] = std::numeric_limits<float>::max(); // initialize to large number
			w[i][j] = w[i][j-1] + probs[j-1];	// calculate and storing the acumulative sum

			// Calculate the optimal solution
			for (int r=i; r<j; r++){
				float t = e[i][r] + e[r+1][j] + w[i][j];
				// update the expected optimal cost
				if (t < e[i][j]){
					e[i][j] = t;
					root_key[i][j-1] = keys[r];
					root_id[i][j-1] = r;
				}
			}
		}
	}
}

void OptimalBST::diagonal_init(){
	// Initialize diagonal of the matrix to 0
	for (int i=0; i<e.size(); i++){
			e[i][i] = 0;
			w[i][i] = 0;
	}
}

void OptimalBST::inorder_traversal(int l, int u){
	// Build the tree using the root table
	// By using the lower bound l and upper bound as indexing for the root
	// We can recursively build a binary tree
	// Left -> Root -> Right
	// Base case
	if (u < l)
		return;

	// m is the optimize root between l to u choices
	int m = root_id[l][u];
	inorder_traversal(l,m-1); // Left
	tree[tree_curr_id] = keys[m]; // Root
	tree_curr_id++; // next node
	inorder_traversal(m+1,u);	// Right
}

void OptimalBST::postorder_traversal(int l, int u){
	// Build the tree using the root table
	// By using the lower bound l and upper bound as indexing for the root
	// We can recursively build a binary tree
	// Left -> Right -> Root
	// Base condition
	if (u < l)
		return;

	// m is the optimize root between l to u choices
	int m = root_id[l][u];
	postorder_traversal(l,m-1); // Left
	postorder_traversal(m+1,u);	// Right
	tree[tree_curr_id] = keys[m]; // Root
	tree_curr_id++; // next node
}


void OptimalBST::print_tree(){
	std::ofstream outfile;
	// postorder traversal
	tree_curr_id = 0;
	postorder_traversal(0, N-1);
	//outfile.open("results/"+filename+"_tree.txt");
	outfile.open(filename, std::ofstream::app);
	outfile << std::endl << "Binary Tree" << std::endl;
	outfile << "Postorder Traversal:\t";
	for (int i=0; i<N; i++)
		outfile << tree[i] << '\t';
	outfile << std::endl;
	outfile.close();

	// inorder traversal
	tree_curr_id = 0;
	inorder_traversal(0, N-1);
	outfile.open(filename, std::ofstream::app);
	outfile << "Inorder Traversal:\t";
	for (int i=0; i<N; i++)
		outfile << tree[i] << '\t';
	outfile << std::endl;
	outfile.close();
}

void OptimalBST::print_table(){
	std::ofstream outfile;
	outfile.open(filename, std::ofstream::app);
	int n = keys.size();
	outfile << std::endl << "Key\t\t";
	for (int k=0; k<n; k++)
		outfile << keys[k] << '\t';
	outfile << std::endl;
	outfile << "Probability\t";
	for (int k=0; k<n; k++)
		outfile << probs[k] << '\t';
	outfile << std::endl;
	outfile.close();
}

void OptimalBST::print_e(){
	std::ofstream outfile;
	outfile.open(filename, std::ofstream::app);
	int n = e.size();
	outfile <<std::endl <<  "Matrix E" << std::endl;
	outfile << "(i,j)\t\t";
	for (int k=0; k<n; k++)
		outfile << k << '\t';
	outfile << std::endl;
	for (int k=0; k<n+2; k++)
		outfile << '-' << '\t';
	outfile << std::endl;

	for (int i=0; i<n; i++){
		outfile << i << "\t|"<< '\t';
		for (int j=0; j<n; j++)
			outfile << std::fixed << std::setprecision(2) << e[i][j] << '\t';
		outfile << std::endl;
	}
	outfile.close();
}

void OptimalBST::print_w(){
	int n = w.size();
	std::cout <<std::endl <<  "Matrix W" << std::endl;
	std::cout << "(i,j)\t\t";
	for (int k=0; k<n; k++)
		std::cout << k << '\t';
	std::cout << std::endl;
	for (int k=0; k<n+2; k++)
		std::cout << '-' << '\t';
	std::cout << std::endl;

	for (int i=0; i<n; i++){
		std::cout << i << "\t|"<< '\t';
		for (int j=0; j<n; j++)
			std::cout << std::fixed << std::setprecision(2) << w[i][j] << '\t';
		std::cout << std::endl;
	}
}

void OptimalBST::print_root(){
	std::ofstream outfile;
	outfile.open(filename, std::ofstream::app);
	int n = root_key.size();
	outfile << std::endl <<  "Matrix Root" << std::endl;
	outfile << "(i,j)\t\t";
	for (int k=0; k<n; k++)
		outfile << k << '\t';
	outfile << std::endl;
	for (int k=0; k<n+2; k++)
		outfile << '-' << '\t';
	outfile << std::endl;

	for (int i=0; i<n; i++){
		outfile << i << "\t|"<< '\t';
		for (int j=0; j<n; j++)
			outfile << root_key[i][j] << '\t';
		outfile << std::endl;
	}
	outfile.close();
}
