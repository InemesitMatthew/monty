#include "monty.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * free_stack - Frees a stack.
 * @stack: A pointer to the top of the stack.
 */
void free_stack(stack_t *stack)
{
    stack_t *temp;

    while (stack)
    {
        temp = stack->next;
        free(stack);
        stack = temp;
    }
}
