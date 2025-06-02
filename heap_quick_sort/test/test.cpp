#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

int main(){
	random_device rd;
	default_random_engine mt{rd()};
	//std::uniform_real_distribution<float> dist(-10000,10000);
	std::uniform_int_distribution<int> dist(0,10);
	int xi = dist(mt);
	int yi = dist(mt);
	int N = 10;
	int X[N*2];
	for (int i=0; i<N*2; i++){
		X[i] = dist(mt);
	}
	std::ofstream outfile;
	outfile.open("../test3.txt");
	outfile<<xi<<"\t"<<yi<<endl;
	outfile<<N<<endl;
	for (int i=0; i<N; i++){
		outfile<<std::fixed<<std::setprecision(2)<<X[2*i]<<"\t"<<X[2*i+1]<<endl;
	}
	outfile.close();

}
