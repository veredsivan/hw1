#include "stack.h"
struct stack
{
	// struct fields
	void** data;
	int max_num_of_elem;
	int top;// will allway point to the slot that will be filled next
// Store all user-function pointers here
	clone_t student_clone;
	destroy_t student_destroy;
	print_t student_print;
};

//creats new stack
pstack_t stack_create(size_t max_num_of_elem,
	clone_t student_clone,
	destroy_t student_destroy,
	print_t student_print)
{
	struct stack* pstack_t = (elem_t)calloc(max_num_of_elem, sizeof(elem_t));
	return pstack_t;
}

//destroys struck 
Result stack_destroy(pstack_t pstack)
{
	if (pstack == NULL)
		return FAIL;
	free(pstack);
	return SUCCESS;
}

//inserts new element into the stack
/*Result stack_push(pstack_t stack, elem_t new_elem)
{
	if (stack->max_num_of_elem == stack->top)// Stack is full
		return FAIL;
	if (!(stack->student_clone))
		return FAIL;//invalid student_clone
	void* clone = stack->student_clone(new_elem);
	if (!clone)
	{
		return FAIL;  //free(clone);
	}
	stack->data[stack->top++] = clone;
	return SUCCESS;
}
*/

RESULT stack_push(pstack_t stack, elem_t new_elem)
{
	if (stack->max_num_of_elem == stack->top)// Stack is full
		return FAIL;

	if (stack->student_clone == NULL)
		return FAIL;//invalid student_clone 

	void* clone = stack->student_clone(new_elem);
	if (clone == NULL)
	{
		return FAIL;
	}

	stack->data[stack->top++] = clone;
	return SUCCESS;
}

// take out the last element in stack and delete it
void stack_pop(pstack_t stack)
{
	if (!(stack->top) || (!(stack->student_destroy)))//stack is empty or invalid value
		return;
	(*stack->student_destroy)(stack->data[--stack->top]);

}
// returns the pointer to the last element in stack
elem_t stack_peek(pstack_t stack)
{
	if (!(stack->top))//stack is empty
		return NULL;
	return stack->data[(stack->top) - 1];
}

int stack_size(pstack_t stack)
{
	return stack->top;
}
//returns true if stack us empty
bool stack_is_empty(pstack_t stack)
{
	return(!(stack->top));//if top ==0 then stack is empty
}
//returns how many empty slots are left
int stack_capacity(pstack_t stack)
{
	return(stack->max_num_of_elem - stack->top);
}
//prints all of the elemts in stack
void stack_print(pstack_t stack)
{
	for (int i = stack->top - 1; i >= 0; i--)
	{
		(*stack->student_print)(stack->data[i]);
	}
}