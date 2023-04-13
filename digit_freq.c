// 123456789
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	char str[1000];
	int count[10] = {0};
	int i=0;
	if (scanf("%s", str) == EOF) {
		return 0;
		}
		
	while (str[i] != '\0') {
		if (str[i] > 9) {
			continue; 
		}
		count[str[i]]++;
		i++;
	}
	
	for (i=0; i<10; i++) {
		printf("%d ", count[i]);
	}
	

	
		
	
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
