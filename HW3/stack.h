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

pstack_t stack_create(size_t max_num_of_elem, /* Complete */);

/**
 * @fn void stack_destroy(pstack_t s);
 * @brief destroys the user_stack. free all the memory of the elements in the
 * stack. user_stack must be a stack created by StackCreate otherwise
 * undefined behavior)
 * @param stack - pointer to the stack to destroy
 * @return none
 */
Result stack_destroy(pstack_t stack);
/* ------------------------------------------ */
/* Add here the rest of the declarations      */
/* ------------------------------------------ */

#endif /* __STACK__ */