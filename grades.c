#include "grades.h"
#include "linked-list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FALSE 1
#define TRUE 0
#define ERROR -1

/* Struct of course and student's grade - 
   an element of L-list */
struct course {
    char *course_name;
    int grade;
};

/* Include student and all his grades data 
   in a L-list */
struct student {
    char *name;
    int student_ID;
    struct list *individual_course; // Must be a pointer for list_init
};

/* Stores course and its grade */
struct grades {
    struct list *individual_student; // Points to specific student struct
};

/* User functions for struct grades, student, and course */

int course_clone(void *element, void **output) {
    struct course *original = (struct course *)element;
    struct course *clone = (struct course *)malloc(sizeof(struct course));
    if (!clone) {
        *output = NULL;
        return FALSE;
    }
    clone->course_name = (char *)malloc(strlen(original->course_name) + 1);
    if (!clone->course_name) {
        free(clone);
        *output = NULL;
        return FALSE;
    }
    clone->grade = original->grade;
    strcpy(clone->course_name, original->course_name);
    *output = clone;
    return TRUE;
}

void course_destroy(void *element) {
    struct course *casted_element = (struct course *)element;
    if (!casted_element) {
        return;
    }
    free(casted_element->course_name);
    free(casted_element);
}

int student_clone(void *element, void **output) {
    struct student *original = (struct student *)element;
    struct student *clone = (struct student *)malloc(sizeof(struct student));
    if (!clone) {
        *output = NULL;
        return FALSE;
    }
    clone->name = (char *)malloc(strlen(original->name) + 1);
    if (!clone->name) {
        free(clone);
        *output = NULL;
        return FALSE;
    }
    clone->individual_course = list_init(course_clone, course_destroy);
    if (!clone->individual_course) {
        free(clone->name);
        free(clone);
        *output = NULL;
        return FALSE;
    }
    clone->student_ID = original->student_ID;
    strcpy(clone->name, original->name);
    *output = clone;
    return TRUE;
}

void student_destroy(void *element) {
    struct student *casted_element = (struct student *)element;
    if (!casted_element) {
        return;
    }
    free(casted_element->name);
    list_destroy(casted_element->individual_course);
    free(casted_element);
}

struct grades *grades_init() {
    struct grades *new_grades = (struct grades *)malloc(sizeof(struct grades));
    if (!new_grades) {
        return NULL;
    }
    new_grades->individual_student = list_init(student_clone, student_destroy);
    if (!new_grades->individual_student) {
        free(new_grades);
        return NULL;
    }
    return new_grades;
}

void grades_destroy(struct grades *grades) {
    if (!grades) {
        return;
    }
    list_destroy(grades->individual_student);
    free(grades);
}

int grades_add_student(struct grades *grades, const char *name, int id) {
    if (!grades) {
        return FALSE;
    }

    // Check if student with the same ID already exists
    struct iterator *it_student = list_begin(grades->individual_student);
    while (it_student) {
        struct student *current_student = (struct student *)list_get(it_student);
        if (current_student->student_ID == id) {
            return FALSE;
        }
        it_student = list_next(it_student);
    }

    struct student *new_student = (struct student *)malloc(sizeof(struct student));
    if (!new_student) {
        return FALSE;
    }
    new_student->name = (char *)malloc(strlen(name) + 1);
    if (!new_student->name) {
        free(new_student);
        return FALSE;
    }
    new_student->individual_course = list_init(course_clone, course_destroy);
    if (!new_student->individual_course) {
        free(new_student->name);
        free(new_student);
        return FALSE;
    }
    new_student->student_ID = id;
    strcpy(new_student->name, name);
    list_push_back(grades->individual_student, new_student);
    return TRUE;
}

int grades_add_grade(struct grades *grades, const char *name, int id, int grade) {
    if (!grades) {
        return ERROR;
    }

    struct iterator *it_student = list_begin(grades->individual_student);
    while (it_student) {
        struct student *current_student = (struct student *)list_get(it_student);
        if (current_student->student_ID == id) {
            struct course new_course;
            new_course.course_name = (char *)malloc(strlen(name) + 1);
            if (!new_course.course_name) {
                return ERROR;
            }
            strcpy(new_course.course_name, name);
            new_course.grade = grade;
            list_push_back(current_student->individual_course, &new_course);
            return TRUE;
        }
        it_student = list_next(it_student);
    }
    return ERROR;
}

float grades_calc_avg(struct grades *grades, int id, char **out) {
    if (!grades || !out) {
        return ERROR;
    }
    int num_courses = 0;
    struct iterator *it_student = list_begin(grades->individual_student);
    struct student *current_student = (struct student *)list_get(it_student);
    while ((current_student!=NULL) &&
         current_student->student_ID !=id ) {
        if (current_student->student_ID == id) {
            break;
            }
        it_student = list_next(it_student);
        current_student = list_get(it_student);
    }
    float total_grade = 0.0;
    struct iterator *it_course = list_begin(current_student->individual_course);
    struct course *current_course = (struct course *)list_get(it_course);
    while (current_course) {
        total_grade += current_course->grade;
        it_course = list_next(it_course);
        current_course = list_get(it_course);
    }
    float avg_grade = total_grade / num_courses;
    char* student_calc_name = 
        (char *)malloc(strlen(current_student->name) + 1);
    if (student_calc_name == NULL) {
        *out=NULL;
        return ERROR;
    }
    strcpy(student_calc_name, current_student->name);
    *out = student_calc_name;
    return avg_grade;
return ERROR;
}

int grades_print_student(struct grades *grades, int id) {
    if (!grades) {
        return ERROR;
    }

    struct iterator *it_student = list_begin(grades->individual_student);
    while (it_student) {
        struct student *current_student = (struct student *)list_get(it_student);
        if (current_student->student_ID == id) {
            printf("%s ", current_student->name);
            printf("%d:\n", current_student->student_ID);
            struct iterator *it_course = list_begin(current_student->individual_course);
            while (it_course) {
                struct course *current_course = (struct course *)list_get(it_course);
                printf("Course name: %s, Grade: %d\n", current_course->course_name, current_course->grade);
                it_course = list_next(it_course);
            }
            return TRUE;
        }
        it_student = list_next(it_student);
    }
    return ERROR;
}
int grades_print_all(struct grades *grades)
{
	if (!grades) return FALSE;
	struct iterator* it_student = list_begin(grades->individual_student);
	struct student* my_student = (struct student*)list_get(it_student);
	while (my_student != NULL)
	{
		grades_print_student(grades, my_student->student_ID);
		//printf("\n");
		it_student = list_next(it_student);
		my_student = (struct student*)list_get(it_student);
	}
	return TRUE;
}
