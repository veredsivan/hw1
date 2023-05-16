#ifndef __STACK__
#define __STACK__

#include <stddef.h>  /* size_t */
#include <stdbool.h> /* bool   */ 
#include "stdlib.h"
#include "stdio.h"

typedef enum { SUCCESS = 0, FAIL} Result;
 
typedef struct stack *pstack_t;

typedef void *elem_t;

typedef elem_t(*clone_t)(elem_t e);

typedef void (*destroy_t)(elem_t e);

typedef void (*print_t)(elem_t e);


/* ------------------------------------------ */
/* Add here declarations of function pointers */
/* ------------------------------------------ */

pstack_t stack_create(int max_num_of_elem, clone_t student_clone,
					destroy_t student_destroy, 
					print_t student_print);

/**
 * @fn void stack_destroy(pstack_t s);
 * @brief destroys the user_stack. free all the memory of the elements in the
 * stack. user_stack must be a stack created by StackCreate otherwise
 * undefined behavior)
 * @param stack - pointer to the stack to destroy
 * @return none
 */
Result stack_destroy(pstack_t stack);

Result stack_push(pstack_t stack, elem_t new_elem);

void stack_pop(pstack_t stack);

elem_t stack_peek(pstack_t stack);

int stack_size(pstack_t stack);

bool stack_is_empty(pstack_t stack);

int stack_capacity(pstack_t stack);

void stack_print(pstack_t stack);



#endif /* __STACK__ */



