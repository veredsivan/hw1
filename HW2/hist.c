#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
#define MIN_VALUE 0
#define MAX_VALUE 100
#define DEFAULT_BINS 10
static FILE* f;


/** create histogram **/
void histogram(FILE* f, int n_bins)
{
    int grade;
    int return_value;
    int valid_grades = 0;
    int line = 1;
    while (TRUE) //checks how many grades are valid
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
        else if ((grade < MIN_VALUE) || (grade > MAX_VALUE))
        {
            fprintf(stderr, "Error: in line %d:grade not valid", line);
        }
        else
        {
            valid_grades++;
        }
        line++;
    }
    fseek(f, 0, SEEK_SET); //return cursor to head of file before scanning
    int* grades = (int*)calloc(valid_grades, sizeof(int)); 
    //grades[] stores all the valid grades
    if (grades == NULL)
    {
        fprintf(stderr, "Error: calloc failed\n");
        exit(1);
    }
    int legal_count = 0; 

    for (int i = 0; i < line; i++)
    {
        fscanf(f, "%d", &grade);
        if ((grade < MIN_VALUE) || (grade > MAX_VALUE)) 
        //if grade is illegal - skip the iteration
            continue;
        grades[legal_count] = grade;
        legal_count++;
    }
    //low and high defines the boundaries of each pace
    int low = 0;
    int high = (MAX_VALUE / n_bins) - 1;
    while (low < MAX_VALUE) //counts incidence of each bin
    {
        int count = 0;
        for (int i = 0; i < valid_grades; i++)
        {
            if ((grades[i] >= low) && (grades[i] <= high))
                count++;
        }
        fprintf(stdout, "%d-%d\t%d\n", low, high, count);
        low += (MAX_VALUE / n_bins);
        if (low == MAX_VALUE - (MAX_VALUE / n_bins)) //last bin is the largest
        {
            high = MAX_VALUE;
        }
        else
        {
         high += (MAX_VALUE / n_bins);
        }
    }
    free(grades);
}

int main(int argc, char** argv)
{

    f = stdin;
    int n_bins = DEFAULT_BINS;
    //checks the arguments of program
    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-"))
            f = stdin;
        else if (!strcmp(argv[i], "-n_bins"))
        {
            if (i < argc - 1)
            {
                n_bins = atoi(argv[i + 1]);
                i++;
            }
            else
                n_bins = DEFAULT_BINS;
        }
        else
            f = fopen(argv[i], "r");
    }
    histogram(f, n_bins);
    fclose(f);
}
