#ifndef _STUDENT_
#define _STUDENT_

#include "stack.h"
#include "stdlib.h"

typedef struct student
{
	char* name;
	int age;
	int id;

}*pstudent_t, student_t;

void* student_clone(elem_t e);

void student_destroy(elem_t e);

void student_print(elem_t e);

#endif /* _STUDENT_ */