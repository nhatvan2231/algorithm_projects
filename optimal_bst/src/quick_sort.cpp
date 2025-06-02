#include "quick_sort.hpp"

// Constructor
QuickSort::QuickSort(int n, std::vector<char> k, std::vector<float> p, bool time){
	// Initialize number of element of X
	this->N = n;
	this->keys = k;
	this->probs = p;

	// Begin sorting
	if (time){
		// runtime
		std::chrono::time_point start = std::chrono::high_resolution_clock::now();
		sort(0, N-1);
		std::chrono::time_point end = std::chrono::high_resolution_clock::now();
		runtime = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	} else{
		sort(0, N-1);
		//for (int i = 0; i<N; i++){
		//	std::cout << keys[i] << '\t' << probs[i] << std::endl;
		//}
	}

}

// Destructor
QuickSort::~QuickSort(){
	// Deallocate;
}

// Randomized quick sort2
void QuickSort::sort(int p, int r){
	// Calculate the distances and store in the array D
	randomized_sort(p,r);
}

// Randomized quick sort
void QuickSort::randomized_sort(int p, int r){
	if (p < r){
		int q = randomized_partition(p,r);
		//int q = hoare_partition(p,r);
		randomized_sort(p, q-1);
		randomized_sort(q+1,r);
	}
}

// Randomized quick sort partition
int QuickSort::randomized_partition(int p,int r){
	// Generate a random pivot
	int i = random_number(p,r);

	// 2 elements exchange [Xx Xy]
	// Exchange pivot with X[i]
	// Exchange X[i] and X[r]
	swap_element(i,r);
	return partition(p,r);
}
// Normal quick sort partition
int QuickSort::partition(int p,int r){
	int i = p - 1;
	// Move distance that is smaller than the pivot to low side
	// Move distance that is smaller than the pivot to high side
	for (int j = p; j < r; j++){
		if (keys[j] <= keys[r]) {
			i+=1;
			// 2 elements exchange [Xx Xy]
			// Exchange X[i] and X[j]
			swap_element(i,j);
		}
	}
	// 2 elements exchange [Xx Xy]
	// Exchange pivot with X[i]
	// Exchange X[i] and X[r]

	swap_element(i+1,r);
	return i+1;
}

// RNG
int QuickSort::random_number(int min, int max){
		std::uniform_int_distribution<int> dist(min,max);
		return dist(mt);
}

// Swap elements in array
void QuickSort::swap_element(int i, int j){
		// swap elementin X array
		char tmp_k = keys[i];
		float tmp_p = probs[i];
		keys[i] = keys[j];
		probs[i] = probs[j];
		keys[j] = tmp_k;
		probs[j] = tmp_p;
}

void QuickSort::get_result(std::vector<char>& k, std::vector<float>& p){
	//std::cout<<"Quick sort runtime (microseconds): \t"<<runtime.count()<<std::endl;
	k = this->keys;
	p = this->probs;
}
