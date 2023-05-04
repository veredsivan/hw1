#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
#define MAX_VALUE 100
#define MIN_VALUE 0

void mean(FILE* f) 
{
	int grade;
	int return_value;
	double sum = 0;
	int count = 0;
	int line = 1;

	while (TRUE)
	{
		return_value = fscanf(f, "%d", &grade);
		if (return_value == EOF)
		{
			break;
		}

		else if (return_value != 1) 
		{
			fprintf(stderr, "Error: more than one grade in line\n");
			exit(1);
		}
		 
		else if ((grade < MIN_VALUE) || (grade >MAX_VALUE)) 
		{
			fprintf(stderr, "Error: in line %d:grade not valid", line);
		}
		else
		{
			count++;
			sum += grade;
		}
		line++;
	}
	//calculate the mean of grades 
	fprintf(stdout, "%.2lf\n", (sum/count));
}

int main(int argc, char** argv)
{
	FILE* f;
	if ((argc == 1) || !strcmp("-", argv[1]))
	{
		f = stdin;
	}
	else
	{
		f = fopen(argv[1], "r");
	}
	if (!f)
	{
		fprintf(stderr, "File not found\"%s\"\n", argv[1]);
	}
	mean(f);
	fclose(f);
}
