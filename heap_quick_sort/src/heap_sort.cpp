#include "heap_sort.hpp"

template <class T> HeapSort<T>::HeapSort(int input_size, T *A, T *B, bool time){
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
		sort();
		std::chrono::time_point end = std::chrono::high_resolution_clock::now();
		runtime = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	} else
		sort();
}

// Calculate parent
template <class T> int HeapSort<T>::parent(int index){
	return index>>1;
}

// Calculate left child
template <class T> int HeapSort<T>::left_child(int index){
	return (index<<1) + 1;
}

// Calculate right child
template <class T> int HeapSort<T>::right_child(int index){
	return (index+1)<<1;
}

// Calculate the Euclidean distance
template <class T> T HeapSort<T>::distance(int index){
	return std::sqrt(std::pow(X[index<<1] - Z[0],2) + std::pow(X[(index<<1)+1] - Z[1],2));
}

// Swap elements in array
template <class T> void HeapSort<T>::swap_element(int i, int j){
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

// Max heapify
template <class T> void HeapSort<T>::max_heapify(int index){
	// Get the index of the left and right childrens
	int l = left_child(index);
	int r = right_child(index);

	// initualize largest node
	int largest = index;

	// Compare left child
	if (l < heap_size && ((D[l] - D[largest]) > 0.001)){
		largest = l;
	}
	// Compare right child
	if (r < heap_size && ((D[r] - D[largest]) > 0.001)){
		largest = r;
	}

	// check if the largest change
	if (largest != index){
		swap_element(index, largest);
		max_heapify(largest);
	}
}

// Build max heap
template <class T> void HeapSort<T>::build_max_heap(){
	for (int i=(N-1)>>1; i >=0; i--){
		max_heapify(i);
	}
}

template <class T> void HeapSort<T>::sort(){

	// Calculate the distances and store in the array D
	for (int i=0; i<N; i++){
		D[i] = distance(i);
	}

	// Initialize heap size count instead of by index
	heap_size = N;
	build_max_heap();
	for (int i=N-1; i>=1; i--){
		swap_element(i, 0);
		// Detach the last node
		heap_size -= 1;
		max_heapify(0);
	}
}


// Destructor
template <class T> HeapSort<T>::~HeapSort(){
	// Deallocate
	delete [] D;
	delete [] Z;
	delete [] X;
}

// Print runtime and return sorted array
template <class T> T* HeapSort<T>::get_result(){
	std::cout<<"HeapSort runtime (microseconds):\t"<<runtime.count()<<std::endl;
	return X;
}

// Save result to a file
template <class T> void HeapSort<T>::save_result(char * path){
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
