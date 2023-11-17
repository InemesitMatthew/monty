#include "monty.h"
#include <stdio.h>

/**
 * pall - Prints all the values on the stack.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the Monty byte code file.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	/* Avoid unused parameter warning */
	(void)line_number;

	/* Print each element in the stack */
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
