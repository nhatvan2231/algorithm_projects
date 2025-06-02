#include "quick_sort.hpp"


// RNG
template <class T> int QuickSort<T>::random_number(int min, int max){
		std::uniform_int_distribution<int> dist(min,max);
		return dist(mt);
}

// Calculate the Euclidean distance
template <class T> T QuickSort<T>::distance(int index){
	return std::sqrt(std::pow(X[index<<1] - Z[0],2) + std::pow(X[(index<<1)+1] - Z[1],2));
}

// Swap elements in array
template <class T> void QuickSort<T>::swap_element(int i, int j){
		// swap elementin X array
		T tmpx = X[i<<1];
		T tmpy = X[(i<<1)+1];
		X[i<<1] = X[j<<1];
		X[(i<<1)+1] = X[(j<<1)+1];
		X[j<<1] = tmpx;
		X[(j<<1)+1] = tmpy;

		// swap element in D array
		T tmpd = D[i];
		D[i] = D[j];
		D[j] = tmpd;
}

// Normal quick sort partition
template <class T> int QuickSort<T>::partition(int p,int r){
	int i = p - 1;
	// Move distance that is smaller than the pivot to low side
	// Move distance that is smaller than the pivot to high side
	for (int j = p; j < r; j++){
		if (D[j] - D[r] <= 0.001) {
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


// Randomized quick sort partition
template <class T> int QuickSort<T>::randomized_partition(int p,int r){
	// Generate a random pivot
	int i = random_number(p,r);

	// 2 elements exchange [Xx Xy]
	// Exchange pivot with X[i]
	// Exchange X[i] and X[r]
	swap_element(i,r);
	return partition(p,r);
}

// Randomized quick sort
template <class T> void QuickSort<T>::randomized_sort(int p, int r){
	if (p < r){
		int q = randomized_partition(p,r);
		//int q = hoare_partition(p,r);
		randomized_sort(p, q-1);
		randomized_sort(q+1,r);
	}
}

// Randomized quick sort2
template <class T> void QuickSort<T>::sort(int p, int r){
	// Calculate the distances and store in the array D
	for (int i=0; i<N; i++){
		D[i] = distance(i);
	}
	randomized_sort(p,r);
}


// Constructor
template <class T> QuickSort<T>::QuickSort(int input_size, T *A, T *B, bool time){
	// Initialize number of element of X
	N = input_size;

	// Copy Z values
	Z = new T[2];
	std::copy(A, A+2, Z);

	// Copy X values
	X = new T[N*2];
	std::copy(B, B+(input_size*2), X);

	// Initialize D array
	D = new T[N];

	// Begin sorting
	if (time){
		// runtime
		std::chrono::time_point start = std::chrono::high_resolution_clock::now();
		sort(0, N-1);
		std::chrono::time_point end = std::chrono::high_resolution_clock::now();
		runtime = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	} else
		sort(0, N-1);
}

// Destructor
template <class T> QuickSort<T>::~QuickSort(){
	// Deallocate;
	delete [] D;
	delete [] Z;
	delete [] X;
}

template <class T> T* QuickSort<T>::get_result(){
	std::cout<<"Quick sort runtime (microseconds): \t"<<runtime.count()<<std::endl;
	return X;
}

// Save result to a file
template <class T> void QuickSort<T>::save_result(char * path){
	std::ofstream outfile;
	outfile.open(path);

	// Write runtime in microseconds to file
	outfile<<runtime.count()<<"us"<<std::endl;

	// Write Z value to file
	outfile	<<	std::fixed \
				<<	std::setprecision(2) \
				<<	Z[0]	<<	"\t" \
				<<	Z[1]	<<	std::endl;

	// Write number of element to file
	outfile	<<N \
				<<std::endl;

	// Write sorted array
	for (int i=0; i<N; i++){
		outfile	<<	std::fixed \
					<<	std::setprecision(2) \
					<<	X[2*i]	<<	"\t" \
					<<	X[2*i+1]	<<	"\t" \
					<<	std::endl;
	}
	outfile.close();
}

