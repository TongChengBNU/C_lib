#include <stdio.h>
#include <time.h>

// clock_t is the return type of fuction clock()
clock_t start, stop;
// lapsed time of running program
double duration;

void myFunction();

int main(){
	// functionality: compute the duration
	start = clock();
	myFunction();	
	stop = clock();
	// CLK_TCK: tick number
	duration = ( (double) (stop-start) )/CLK_TCK
	


			




	
	return 0;

}

	
