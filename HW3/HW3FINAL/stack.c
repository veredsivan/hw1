#include "stack.h"
#include <stdlib.h>

struct stack {
    // struct fields
    elem_t *data;
    int max_num_of_elem;
    size_t top; // will always point to the slot that will be filled next
    // Store all user-function pointers here
    clone_t student_clone;
    destroy_t student_destroy;
    print_t student_print;
};

// creates a new stack
/*pstack_t stack_create(int max_num_of_elem,
                      clone_t student_clone,
                      destroy_t student_destroy,
                      print_t student_print)
{
    pstack_t stack = (pstack_t) malloc(sizeof(struct stack));
    if (!stack) {
        return NULL; // allocation failed
    }
    
    stack->data = (elem_t*) calloc(max_num_of_elem, sizeof(elem_t));
    if (!stack->data) {
        free(stack); // allocation failed, free the previously allocated memory
        return NULL;
    }
    stack->top = 0;
    stack->max_num_of_elem = max_num_of_elem;
    stack->student_clone = student_clone;
    stack->student_destroy = student_destroy;
    stack->student_print = student_print;
    return stack;
}
*/
pstack_t stack_create(int max_num_of_elem,
                      clone_t student_clone,
                      destroy_t student_destroy,
                      print_t student_print)
{
	pstack_t stack= (pstack_t)malloc(sizeof(struct stack));
	if(stack==NULL){
		/*Error*/
		return NULL;
	}
	stack->data= (elem_t)malloc(max_num_of_elem * sizeof(elem_t));

	if(stack->data==NULL){
			/*Error*/
		free(stack);
		return NULL;
	}

	stack->top=0;
	stack->max_num_of_elem=max_num_of_elem;
	stack->student_clone=student_clone;
	stack->student_destroy=student_destroy;
	stack->student_print=student_print;

	return(stack);
}


// destroys stack
Result stack_destroy(pstack_t pstack)
{
    if (pstack == NULL)
        return FAIL;
    for (size_t i = 0; i < pstack->top; i++) {
        (*pstack->student_destroy)(pstack->data[i]); // free each element
    }
    free(pstack->data);
    free(pstack);
    return SUCCESS;
}

// inserts new element into the stack
Result stack_push(pstack_t stack, elem_t new_elem)
{
    if (stack->max_num_of_elem == stack->top) // Stack is full
        return FAIL;
    if (!(stack->student_clone))
        return FAIL; // invalid student_clone
    void* clone = stack->student_clone(new_elem);
    if (!clone)
    {
        return FAIL; // allocation failed
    }
    stack->data[stack->top++] = clone;
    return SUCCESS;
}

// take out the last element in stack and delete it
void stack_pop(pstack_t stack)
{
    if (stack->top == 0 || !(stack->student_destroy)) // stack is empty or invalid value
        return;
    (*stack->student_destroy)(stack->data[--stack->top]);
}

// returns the pointer to the last element in stack
elem_t stack_peek(pstack_t stack)
{
    if (stack->top == 0) // stack is empty
        return NULL;
    return stack->data[stack->top - 1];
}

int stack_size(pstack_t stack)
{
    return stack->top;
}

// returns true if stack is empty
bool stack_is_empty(pstack_t stack)
{
    return stack->top == 0;
}

// returns how many empty slots are left
int stack_capacity(pstack_t stack)
{
    return stack->max_num_of_elem - stack->top;
}

// prints all of the elements in stack
void stack_print(pstack_t stack)
{
    for (int i = stack->top - 1; i >= 0; i--)
    {
        (*stack->student_print)(stack->data[i]);
    }
}







