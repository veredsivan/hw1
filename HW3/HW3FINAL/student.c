#include "student.h"
#include <string.h>

elem_t student_clone(elem_t elem)
{
	struct student* s;
	struct student* clone;
	s = (struct student*)elem;
	clone = malloc(sizeof(struct student));
	if (!clone)
		return NULL;
	//copy values

	clone->name = (char*)malloc(strlen(s->name) + 1);
	if (!clone->name)
		return NULL;
	strcpy(clone->name, s->name);
	clone->age = s->age;
	clone->id = s->id;
	return (void*)clone;
}

void student_destroy(elem_t elem)
{
	student_t* student = (student_t*)elem;
	if (!elem||!(student->name))
		return;
	free(student->name);
	free(student);
}

void student_print(elem_t elem)
{
	if (!elem) {
		return;
	}
	student_t* student = (student_t*)elem;
	printf("student name: %s, age: %d, id: %d.\n", student->name, student->age, student->id);
}