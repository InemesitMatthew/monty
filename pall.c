#include "monty.h"

/**
 * pall - print all elements of the stack
 * @stack: double pointer to the stack
 * @line_number: current line number in the file
 */
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;

    (void)line_number; /* Unused parameter */

    while (current)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}
