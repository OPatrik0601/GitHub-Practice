#include <stdio.h>
#include <conio.h>
#include <time.h>

int main() {
	long int currNumber = 5;
	int counter = 2;
	printf("1 2 ");
	time_t time_start = clock();
	while(!kbhit()) {
		int found = 0;
		long int i=2;
		do {
			if(currNumber%i == 0)
				found = 1;
			i++;
		} while(found == 0 && currNumber/2 >= i);
		
		if(found == 0) {
			printf("%ld ", currNumber);
			counter++;
		}
			
		currNumber++;
	}
	double time_end = ((double)clock()-time_start)/CLOCKS_PER_SEC;
	printf("\n=========================\nFound numbers: %i\nElapsed time: %lf\n", counter, time_end);
	return 0;
}