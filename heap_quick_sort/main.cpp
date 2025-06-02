#include <fstream>
#include "heap_sort.hpp"
#include "quick_sort.hpp"

using namespace std;

// Calculate Euclidean distance
float distance(float Xx, float Yy, float Zx, float Zy);

int main(int argc, char **argv){
	int N;					// N number of elements in X
	float Z[2];			// Z and X values
	float* X;			// Z and X values

	// Open the data file
	char * PATH = "test1.txt";
	if (argc > 2){
		printf("Invalid format!\n");
		printf("Usage: %s <path_to_file>\n", argv[0]);
		printf("Default file 'test2.txt'\n");
	}
	if (argc == 2){
		PATH = argv[1];
	}


	std::ifstream infile;
	infile.open(PATH);
	if (!infile){
		printf("Unable to open file\n");
		exit(1);
	}

	// reading the Z values
	infile>>Z[0]>>Z[1];

	// reading N
	infile>>N;

	// creating 2d array for X
	X = new float[N*2];

	// reading the X values
	for (int i=0;i<N; ++i){
		infile>>X[2*i]>>X[2*i+1];
	}
	infile.close();


	// create sort objects
	HeapSort<float> heapsort(N,Z,X, true);
	QuickSort<float> quicksort(N,Z,X, true);

	// get the array and time
	printf("Sorting runtime\n");
	float* H = heapsort.get_result();
	float* Q = quicksort.get_result();

	printf("Validating accuracy...\n");
	bool heap_accurracy = true;
	bool quick_accurracy = true;
	float heap_tail_dist = -9999;
	float quick_tail_dist = -9999;
	for (int i=0;i<N;i++){
		if (!heap_accurracy && !quick_accurracy) break;

		float heap_head_dist = distance(H[i<<1], H[(i<<1)+1], Z[0], Z[1]);
		float quick_head_dist = distance(Q[i<<1], Q[(i<<1)+1], Z[0], Z[1]);

		if(heap_accurracy && (heap_tail_dist - heap_head_dist) <= 0.009){
			heap_tail_dist=heap_head_dist;
		} else{
			heap_accurracy = false;
			printf("Heap Failed: %f\t>\t%f\n",heap_tail_dist, heap_head_dist);
		}

		if(quick_accurracy && (quick_tail_dist - quick_head_dist) <= 0.009){
			quick_tail_dist=quick_head_dist;
		} else{
			quick_accurracy = false;
			printf("Quick Failed: %f\t>\t%f\n",quick_tail_dist, quick_head_dist);
		}
	}
	heap_accurracy? printf("Heap Sort: PASS!!\n") : printf("Heap Sort: Failed?!\n");
	quick_accurracy? printf("Quick Sort: PASS!!\n") : printf("Quick Sort: Failed?!\n");

	// save result
	heapsort.save_result("heapsorted_points.txt");
	quicksort.save_result("quicksorted_points.txt");

	delete [] X;
}

// Calculate Euclidean distance
float distance(float Xx, float Yy, float Zx, float Zy){
	return sqrt(pow(Xx - Zx, 2) + pow(Yy - Zy, 2));
}
