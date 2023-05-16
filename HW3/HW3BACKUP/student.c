#include "student.h"
#include <string.h>

void* student_clone(elem_t elem)
{
	struct student* s;
	struct student* clone;
	s = (struct student*)elem;
	clone = malloc(sizeof(struct student));
	if (!clone)
		return NULL;
	//copy values
	clone->name = strdup(s->name);
	clone->age = s->age;
	clone->id = s->id;
	return (void*)clone;
}

void student_destroy(elem_t elem)
{
	struct student* student = (struct student*)elem;
	if (!elem || !(student->name))
		return;
	free(student->name);
	free(student);
}

void student_print(elem_t elem)
{
	if (!elem) {
		return;
	}
	struct student* student = (struct student*)elem;
	printf("student name: %s, age: %d, id: %d.\n", student->name, student->age, student->id);
}