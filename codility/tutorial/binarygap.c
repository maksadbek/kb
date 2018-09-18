#include <stdlib.h>
#include <stdio.h>

int solution(int N) {
	int max = 0;
	int skippedHead = 0;

	while(N > 0) {
		if((N & 1) == 0) {
			if(skippedHead == 1) {
				count++;
			}
		} else {
			if(!skippedHead) {
				skippedHead = 1;
			} else {
				if(count > max) {
					max = count;
				}
				count = 0;
			}
		}

		N = N >> 1;
	}

	return max;
}

int main() {
	int n = 0;
	scanf("%d", &n);

	int gap = solution(n);

	printf("binary gap: %d", gap);

	exit(0);
}
