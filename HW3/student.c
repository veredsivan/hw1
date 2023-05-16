#include "student.h"
struct student {
	char* name;
	int age;
	int id;
};

void* clone_student(elem_t elem)
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

void destroy_student(elem_t elem)
{
	if (!elem||!student->name)
		return;
	struct student* student = (struct student*)elem;
	free(student->name);
	free(student);
}

void print_student(elem_t elem)
{
	if (!elem) {
		return;
	}
	struct student* student = (struct student*)elem;
	printf("student name: %s, age: %d, id: %d.\n", student->name, student->age, student->id);
}