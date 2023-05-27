#include "grades.h"
#include "linked-list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FALSE 1
#define TRUE 0
#define ERROR -1
#define FAIL -1
/* struct of course and student's grade - 
	an element of L-list */
struct course { 
	char *course_name;
	size_t grade;
};
/* include student and all his grades data 
	in a L-list*/	
struct student {
	char *name;
	size_t student_ID;
	struct list *individual_course; //must be a pointer for list_init
};
/* stores course and its grade */
struct grades { 
	struct list *individual_student; //points to specific student struct
};

/* user functions for struct grades, student and course */ 

int course_clone(void *element, void **output) 
{

	struct course* new_course=(struct course*)malloc(sizeof(struct course));
    if(new_course==NULL)
    {
    	*output=NULL;
        return FAIL;
    }

    struct course* my_course=(struct course*)element;

     new_course->course_name=(char*)malloc(strlen(my_course->course_name)+ 1);
     if(new_course->course_name==NULL)
     {
    	 *output=NULL;
         return FAIL;
     }
     new_course->grade=my_course->grade;
     new_course->course_name=my_course->course_name;
     //return (void*)new_course;
     *output=new_course;
     return TRUE;


	/*
	struct course* original = (struct course*) element;
	struct course* clone = (struct course*) *output;
	clone =(struct course*)malloc(sizeof(struct course));
	if (!clone) 
			return FALSE;
	clone->course_name =(char*)malloc(strlen((original->course_name) + 1));
	if (!clone->course_name )
		return FALSE;
	clone->grade = original->grade;
	return TRUE;
	*/
}


void course_destroy(void *element)
{
	struct course* casted_element = (struct course*)element;
	if (!casted_element)
		return;
	free(casted_element->course_name);
	free(casted_element);
}



int student_clone(void *element, void **output)
{
	/*
	struct student* new_student=(struct student*)malloc(sizeof(struct student));
     if(new_student==NULL)
     {
    	 *output=NULL;
         return FAIL;
     }

     struct student* my_student=(struct student*)element;
     new_student->individual_course=list_init(course_clone,course_destroy);
     new_student->name=(char*)malloc(strlen(my_student->name)+ 1);
     if(new_student->name==NULL)
     {
    	 *output=NULL;
         return FAIL;
     }
     new_student->student_ID=my_student->student_ID;
     new_student->name=my_student->name;
     
     *output=new_student;
     return TRUE;

	*/
	struct student* original = (struct student*) element;
	struct student* clone = (struct student*) *output;
	clone =(struct student*)malloc(sizeof(struct student));
	if (clone == NULL) 
	{
		*output = NULL;
		return FALSE;
	}
	clone->name =(char*)malloc(strlen((original->name) + 1));
	if (clone->name == NULL ) 
	{
		*output = NULL;
		return FALSE;
	}
	clone->individual_course = list_init(course_clone, course_destroy);
	clone->student_ID= original->student_ID;
	clone->individual_course= original->individual_course;
	*output = clone;
	return TRUE;
}	


void student_destroy(void *element)
{	
	struct student* casted_element = (struct student*)element;
	if (!casted_element)
		return;
	free(casted_element->name);
	list_destroy(casted_element->individual_course);
	free(casted_element);
}


/** struct grades functions **/
 
 struct grades* grades_init()
 {
 	/*
 	struct grades* my_grades=(struct grades*)malloc(sizeof(struct grades));
    if(my_grades==NULL)
    {
        return NULL;
    }
    my_grades->individual_student=list_init(student_clone,student_destroy);
    return my_grades;
	*/

 	
	
	struct grades* new_grades = (struct grades*)malloc(sizeof(struct grades));
	if (!(new_grades))
		return NULL;
	new_grades->individual_student = list_init(student_clone, student_destroy); 
	if (!(new_grades->individual_student))
		return NULL;
	return new_grades;
	
 }
 
void grades_destroy(struct grades *grades) 
{
	if (grades==NULL)
		return;
	list_destroy(grades->individual_student);
	free (grades);
	
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id)
{
	/*
	if (grades==NULL)
    {
        return FAIL;
    }

    struct iterator* it=list_begin(grades->individual_student);
    struct student* cur_student=list_get(it);
    
    while(cur_student!=NULL)
    {
        if(cur_student->student_ID==id)
        {
            return FAIL;
        }

        it=list_next(it);
        cur_student=list_get(it);
    }
   struct student* new_student=(struct student*)malloc(sizeof(struct student));
   new_student->name=(char*)malloc(strlen(name)+1);
   strcpy(new_student->name,name);
   new_student->student_ID=id;
   
   return list_push_back(grades->individual_student,new_student);
 */

	
	if (!grades) 
		return FALSE;
	// check for already exist student 
	struct iterator* it_student = list_begin(grades->individual_student);
	struct student* my_student =(struct student*)list_get(it_student);
	while(my_student!=NULL) 
		//continue scanning if yet found the relevant ID or NULL
	{
		if(my_student->student_ID == id) 
		{
			return FALSE;
		}
		it_student = list_next(it_student);
		my_student = list_get(it_student);
	}
	struct student* copy_student=(struct student*)malloc(sizeof(struct student));
	copy_student->name=(char*)malloc(strlen(name)+1);
	strcpy(copy_student->name,name);
	copy_student->student_ID=id;	
	list_push_front(grades->individual_student, copy_student);
	//student_destroy(copy_student);
	return TRUE;
	
}

/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade)
 {
 /*

 	if(grades==NULL||grade>100||grade<0)
    {
        return FAIL;
    }

    struct iterator* it=list_begin(grades->individual_student);
   	struct student* cur_student=list_get(it);

    while(cur_student!=NULL && cur_student->student_ID!=id)
    {
    	it=list_next(it);
    	cur_student=list_get(it);
    }
    if(cur_student==NULL)
    {
        return FAIL;
    }
    it=list_begin(cur_student->individual_course);
    struct course* cur_course=list_get(it);
    while(cur_course!=NULL)
    {
        if(cur_course->course_name==name)
        {
            return FAIL;
        }
        it=list_next(it);
        cur_course=list_get(it);
    }

     struct course* new_course=(struct course*)malloc(sizeof(struct course));
        new_course->course_name=(char*)malloc(strlen(name)+1);
        strcpy(new_course->course_name,name);
        new_course->grade=grade;

        return list_push_back(cur_student->individual_course,new_course);

*/




	if (!grades) 
	{
		return FALSE;
	}
	if((grade<0) || (grade>100)) 
	{
		return FALSE;
	}
		
	struct iterator* it_student = list_begin(grades->individual_student);
	struct student* my_student =list_get(it_student);
	while((my_student->student_ID != id) && (my_student != NULL)) 
		//continue scanning if yet found the relevant ID or NULL
	{
		it_student = list_next(it_student);
		my_student = list_get(it_student);
	}
	if(!my_student) {
		return FALSE;
	}
	struct iterator* it_course = list_begin(my_student->individual_course);
	struct course* my_course= (struct course*)list_get(it_course);
	
	while(!my_course) //~~~~~~~~~~~~~~~~~~~~ strcmp
	{
		if (strcmp(my_course->course_name,name))
		{
			
			//course_destroy(copy_course); //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			return FALSE;
		}
		
		it_course= list_prev(it_course);
		my_course = list_get(it_course);
	}
	struct course* copy_course=(struct course*)malloc(sizeof(struct course));
	copy_course->course_name=(char*)malloc(strlen(my_course->course_name)+1);
	strcpy(copy_course->course_name,name);
	copy_course->grade=grade;
	return (list_push_front(my_student->individual_course, copy_course));

}
	
	

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out)
{
/*
	if(grades==NULL)
	{
		*out=NULL;
		return FAIL;
	}
	 int counter=0;
	 float sum=0.00;
	 struct iterator* it=list_begin(grades->individual_student);
	 struct student* cur_student=list_get(it);

    while(cur_student!=NULL && cur_student->student_ID!=id)
    {
        //cur_student=list_next(cur_student);
    	it=list_next(it);
    	cur_student=list_get(it);
    }
    if(cur_student==NULL)
    {
        *out=NULL;
        return FAIL;
    }

    char* name=(char*)malloc(strlen(cur_student->name)+1);
    if(name==NULL)
    {
        *out=NULL;
        return FAIL;
    }
    strcpy(name,cur_student->name);
    *out=name;
    it=list_begin(cur_student->individual_course);
    struct course* cur_course=list_get(it);
    
    while(cur_course!=NULL)
    {
      counter++;
      sum+=cur_course->grade;
      it=list_next(it);
      cur_course=list_get(it);
    }
    if(counter==0)
    {
    	return 0.00;
    }
    return sum/counter;

*/




	float sum = 0;
	if (!grades) 
	{
		out = NULL;
		return ERROR;
	}
		
	struct iterator* it_student = list_begin(grades->individual_student);
	struct student* my_student =(struct student*)list_get(it_student);
	while((my_student->student_ID != id) && (my_student != NULL)) 
		//continue scanning if yet found the relevant ID or NULL
	{
		it_student = list_next(it_student);
		my_student = list_get(it_student);
		if(!my_student) 
		{
			*out = NULL;
			return ERROR;
		}
		
	}
    char* copy_name=(char*)malloc(strlen(my_student->name)+1);
	if (!copy_name)
	{
		*out = NULL;
		return ERROR;
	}
	strcpy(copy_name, my_student->name);
	*out = copy_name;
	//free(copy_name); //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	struct iterator* it_course = list_begin(my_student->individual_course);
	struct course* my_course= (struct course*)list_get(it_course);

	while(!my_course) 
		//continue scanning if yet found the relevant ID or NULL
	{
		float my_grade = (float)(my_course->grade);
		if((my_grade<0) || (my_grade>100)) {
			out = NULL;
			return ERROR;
		}
		sum += my_grade;
		it_course= list_next(it_course);
		my_course = list_get(it_course);
	}
	size_t num_courses = list_size(my_student->individual_course);
	if (num_courses==0)
		return 0;
	return (sum/num_courses);
}
/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id)

{
/*

	if(grades==NULL)
    {
        return FAIL;
    }

    struct iterator* it=list_begin(grades->individual_student);
    struct student* cur_student=list_get(it);

    while(cur_student!=NULL && cur_student->student_ID!=id)
    {
        it=list_next(it);
    	cur_student=list_get(it);
    }
    if(cur_student==NULL)
    {
        return FAIL;
    }
   
    printf("%s %ld:", cur_student->name, cur_student->student_ID);
    it=list_begin(cur_student->individual_course);
    struct course* cur_course=list_get(it);
    while(cur_course!=NULL)
    {
        printf(" %s %ld", cur_course->course_name, cur_course->grade);
        it=list_next(it);
        cur_course=list_get(it);
        if(cur_course!=NULL)
        {
            printf(",");
        }
    }
    printf("\n");
    return TRUE;
*/






	int counter = 1;
	if (!grades) {
		return FALSE;
	}
	struct iterator* it_student = list_begin(grades->individual_student);
	struct student* my_student =(struct student*)list_get(it_student);
	while((my_student->student_ID != id) && (my_student != NULL)) 
		//continue scanning if yet found the relevant ID or NULL
	{
		if(!my_student) {
			return FALSE;
		}
		it_student = list_next(it_student);
		my_student = list_get(it_student);
	}
	printf("%s %ld: ", my_student->name, my_student->student_ID);
	struct iterator* it_course = list_end(my_student->individual_course);
	struct course* my_course= (struct course*)list_get(it_course);
	while(!my_course) 
		//continue scanning if yet found the relevant ID or NULL
	{
		float my_grade = (float)(my_course->grade);
		if((my_grade<0) || (my_grade>100)) 
		{
			return FALSE;
		}
		it_course= list_prev(it_course);
		my_course = list_get(it_course);
		if (counter == list_size(my_student->individual_course)) 
		{
			printf("%s %ld", my_course->course_name, my_course->grade);
		}
		else 
		{
		printf("%s %ld, ", my_course->course_name, my_course->grade);
		}
		counter++;
	}
	return TRUE;
}


/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades) {

/*	
	    if(grades==NULL)
    {
        return FAIL;
    }
    
   struct iterator* it=list_begin(grades->individual_student);
   struct student* cur_student;
    

    while(it!=NULL)
    {
    	cur_student=list_get(it);
        grades_print_student(grades,cur_student->student_ID);
        it=list_next(it);
        
    }
    return TRUE;

*/





	if (!grades) {
		return FALSE;
	}
	struct iterator* it_student = list_end(grades->individual_student);
	struct student* my_student =(struct student*)list_get(it_student);
	while(!my_student)
	{
		grades_print_student(grades ,my_student->student_ID);
		printf("\n");
		it_student = list_prev(it_student);	
		my_student = list_get(it_student);
		
	}
	return TRUE;

}
