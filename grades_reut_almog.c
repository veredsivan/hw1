/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grades.h"
#include "linked-list.h"
#define SUCCESS 0
#define FAIL -1

/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */

 struct course
 {
     int grade;
     char* name;
 };

 struct student
 {
    char *name;
    int id;
    struct list *student_courses;
 };

 struct grades
 {
    struct list *all_students;
 };
 void course_destroy(void* e)
 {
    struct course* my_course=(struct course*)e;
    if(my_course==NULL)
    {
        return;
    }

    free(my_course->name);
    free(my_course);
 }
 int course_clone(void* e, void** output)
 {
    struct course* new_course=(struct course*)malloc(sizeof(struct course));
    if(new_course==NULL)
    {
    	*output=NULL;
        return FAIL;
    }

    struct course* my_course=(struct course*)e;

     new_course->name=(char*)malloc(strlen(my_course->name)+ 1);
     if(new_course->name==NULL)
     {
    	 *output=NULL;
         return FAIL;
     }
     strcpy(new_course->name, my_course->name);
     new_course->grade=my_course->grade;
     *output=new_course;
     course_destroy((void*)my_course);

     return SUCCESS;
 }
 void student_destroy (void* e)
  {
     struct student* my_student=(struct student*)e;

     if(my_student==NULL)
     {
         return;
     }

     free(my_student->name);
     list_destroy(my_student->student_courses);
     free(my_student);
  }


 int student_clone (void* e, void** output)
 {
     struct student* new_student=(struct student*)malloc(sizeof(struct student));
     if(new_student==NULL)
     {
    	 *output=NULL;
         return FAIL;
     }

     struct student* my_student=(struct student*)e;
     new_student->student_courses=list_init(course_clone,course_destroy);
     if(new_student->student_courses == NULL)
     {
    	 free(new_student);
    	 return FAIL;
     }
     new_student->name=(char*)malloc(strlen(my_student->name)+ 1);
     if(new_student->name==NULL)
     {
    	*output=NULL;
    	 free(new_student);
         return FAIL;
     }
     strcpy(new_student->name, my_student->name);
     new_student->id=my_student->id;
    
     *output=new_student;
     
     struct iterator* cur_it=list_begin(my_student->student_courses);
     while(cur_it != NULL)
     {
    	 struct course* cur_course=list_get(cur_it);
    	 list_push_back(my_student->student_courses,cur_course);
    	 cur_it=list_next(cur_it);
     }
    
     student_destroy(my_student);
     *output=(void*)new_student;
     return SUCCESS;
 }

struct grades* grades_init()
{
    struct grades* my_grades=(struct grades*)malloc(sizeof(struct grades));
    if(my_grades==NULL)
    {
        return NULL;
    }
    my_grades->all_students=list_init(student_clone,student_destroy);
    
    if(my_grades->all_students == NULL)
    {
    	free(my_grades);
    	return NULL;
    }
    return my_grades;
}

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades)
{
    if(grades==NULL)
    {
        return;
    }
   
   list_destroy(grades->all_students);
    free(grades);
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id)
{
    if (grades==NULL)
    {
        return FAIL;
    }

    struct iterator* it=list_begin(grades->all_students);
    struct student* cur_student=list_get(it);
    
    while(cur_student!=NULL)
    {
        if(cur_student->id==id)
        {
            return FAIL;
        }

        it=list_next(it);
        cur_student=list_get(it);
    }
   struct student* new_student=(struct student*)malloc(sizeof(struct student));
   if(new_student==NULL)
   {
	   return FAIL;
   }
   new_student->name=(char*)malloc(strlen(name)+1);
   if(new_student->name == NULL)
   {
	   free(new_student);
	   return FAIL;
   }
   strcpy(new_student->name,name);
   new_student->id=id;
   new_student->student_courses= list_init(course_clone, course_destroy);
   
   if(new_student->student_courses == NULL)
   {
	   free(new_student->name);
	   free(new_student);
	   return FAIL;   
   }
   
   int result=list_push_back(grades->all_students,new_student);
   if(result !=SUCCESS)
   {
	   list_destroy(new_student->student_courses);
	   free(new_student->name);
	   free(new_student);
	   return FAIL;
   }
   return SUCCESS;
   
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
    if(grades==NULL||grade>100||grade<0)
    {
        return FAIL;
    }

    struct iterator* it=list_begin(grades->all_students);
   	struct student* cur_student=list_get(it);

    while(cur_student!=NULL && cur_student->id!=id)
    {
    	it=list_next(it);
    	cur_student=list_get(it);
    }
    if(cur_student==NULL)
    {
        return FAIL;
    }
    it=list_begin(cur_student->student_courses);
    struct course* cur_course=list_get(it);
    while(cur_course!=NULL)
    {
        if(strcmp(cur_course->name, name)==0)
        {
            return FAIL;
        }
        it=list_next(it);
        cur_course=list_get(it);
    }

     struct course* new_course=(struct course*)malloc(sizeof(struct course));
     if(new_course== NULL)
     {
    	 return FAIL;
     }
        new_course->name=(char*)malloc(strlen(name)+1);
        if(new_course->name == NULL)
        {
        	free(new_course);
        	return FAIL;
        }
        strcpy(new_course->name,name);
        new_course->grade=grade;
        
        int result=list_push_back(cur_student->student_courses,new_course);
           if(result !=SUCCESS)
           {
        	   free(new_course->name);
        	   free(new_course);
        	   return FAIL;
           }
           return SUCCESS;
     
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
	if(grades==NULL)
	{
		*out=NULL;
		return FAIL;
	}
	 int counter=0;
	 float sum=0.00;
	 struct iterator* it=list_begin(grades->all_students);
	 struct student* cur_student=list_get(it);

    while(cur_student!=NULL && cur_student->id!=id)
    {
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
    it=list_begin(cur_student->student_courses);
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
}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id)
{
 if(grades==NULL)
    {
        return FAIL;
    }

    struct iterator* it=list_begin(grades->all_students);
    struct student* cur_student=list_get(it);

    while(cur_student!=NULL && cur_student->id!=id)
    {
        it=list_next(it);
    	cur_student=list_get(it);
    }
    if(cur_student==NULL)
    {
        return FAIL;
    }
   
    printf("%s %d:", cur_student->name, cur_student->id);
    it=list_begin(cur_student->student_courses);
    struct course* cur_course=list_get(it);
    while(cur_course!=NULL)
    {
        printf(" %s %d", cur_course->name, cur_course->grade);
        it=list_next(it);
        cur_course=list_get(it);
        if(cur_course!=NULL)
        {
            printf(",");
        }
    }
    printf("\n");
    return SUCCESS;
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
int grades_print_all(struct grades *grades)
{
    if(grades==NULL)
    {
        return FAIL;
    }
    
   struct iterator* it=list_begin(grades->all_students);
   struct student* cur_student;
    

    while(it!=NULL)
    {
    	cur_student=list_get(it);
        grades_print_student(grades,cur_student->id);
        it=list_next(it);
        
    }
    return SUCCESS;
}
