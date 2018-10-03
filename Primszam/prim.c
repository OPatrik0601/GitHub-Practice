#include <stdio.h>
int main() {
	long int currNumber = 5;
	while(1) {
		int found = 0;
		long int i=2;
		do {
			if(currNumber%i == 0)
				found = 1;
			i++;
		} while(found == 0 && currNumber/2 >= i);
		
		if(found == 0)
			printf("%ld ", currNumber);
			
		currNumber++;
		//printf("%ld %ld\n", currNumber, i);
	}
	return 0;
}