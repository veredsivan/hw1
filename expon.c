// 123456789
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	int A;
	if (scanf("%d", &A) == EOF);
	for (int N=1; N <= A; N++) {
		int num = pow(N,N);
		
		if (num%A == 0) {
			printf("%d", N);
			break;
			}
		}

	

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
