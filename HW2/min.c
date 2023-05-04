#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
#define MIN_VALUE 0
#define MAX_VALUE 100

void minimum(FILE* f)
{
	int grade;
	int return_value;
	int min = MAX_VALUE;
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
			fprintf(stderr, "Error: input problem\n");
			exit(1);
		}
		else if ((grade < MIN_VALUE) || (grade > MAX_VALUE))
		{
			fprintf(stderr, "Error: in line %d:grade not valid", line);
		}
		else
		{
			count++;
			if (grade < min)
			{
				min = grade;
			}
		}
		line++;
	}
	fprintf(stdout,"%d\n",min);
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
		fprintf(stderr, "File not found\"%s\"\n",argv[1]);
	}
	minimum(f);
	fclose(f);
}
