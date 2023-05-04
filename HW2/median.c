#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
#define MIN_VALUE 0
#define MAX_VALUE 100


void merge(int a[], int na, int b[], int nb, int c[])
{
    int ia, ib, ic;
    for (ia = ib = ic = 0; (ia < na) && (ib < nb); ic++)
    {
        if (a[ia] < b[ib]) {
            c[ic] = a[ia];
            ia++;
        }
        else {
            c[ic] = b[ib];
            ib++;
        }
    }
    for (; ia < na; ia++, ic++) c[ic] = a[ia];
    for (; ib < nb; ib++, ic++) c[ic] = b[ib];
}

/**merge 2 arrays in order from low to high **/
void internal_msort(int a[], int n, int helper_array[])
{

    int left = n / 2;
    int right = n-left;
    if (n < 2)
        return;
    internal_msort(a, left, helper_array);
    internal_msort(a + left, right, helper_array);
    merge(a, left, a + left, right, helper_array);
    memcpy(a, helper_array, n * sizeof(int));
}

int merge_sort(int a[], int n)
{
    int* tmp_array = calloc(n,sizeof(int));
    if (tmp_array == NULL)
        return FALSE;
    internal_msort(a, n, tmp_array);
    free(tmp_array);
    return TRUE;
}


/** calculate the median of grades in file f **/
void median(FILE* f)
{

    int grade;
    int return_value;
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
        else if ((grade < MIN_VALUE) || (grade > MAX_VALUE))
        {
            fprintf(stderr, "Error: in line %d:grade not valid", line);
        }
        else
        {
            count++;
        }
        line++;
    }
    int* grades = (int*)calloc(count,sizeof(int));
    if (grades==NULL)
    {
        fprintf(stderr, "Error: calloc failed\n");
    }
    fseek(f, 0, SEEK_SET);
    int legal_count = 0;
    for (int i = 0; i < line; i++)
    {
        fscanf(f, "%d", &grade);
        if ((grade < 0) || (grade > 100))
            continue;
        grades[legal_count] = grade;
        legal_count++;
    }
    if (!merge_sort(grades, count))
    {
        fprintf(stderr, "Error: calloc failed\n");
    }
    int meadian_index = (count + 1) / 2;
    int median = grades[meadian_index-1]; //grades index starts from 0
    fprintf(stdout, "%d",median);
    free(grades);
}

int main(int argc, char** argv)
{
    FILE* f;
    if ((argc == 1) || (!strcmp("-", argv[1])))
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
    median(f);
    fclose(f);
}
