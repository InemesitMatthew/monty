#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /* for isdigit */

/**
 * push - Pushes an element onto the stack.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the Monty byte code file.
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;
	char *arg;

	/* Tokenize the line to extract the argument */
	arg = strtok(NULL, " \t\n");

	/* Check if the argument is not provided or is not an integer */
	if (arg == NULL || (!isdigit(*arg) && *arg != '-' && *arg != '+'))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* Create a new node and check for allocation failure */
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	/* Assign values to the new node */
	new_node->n = atoi(arg);
	new_node->prev = NULL;
	new_node->next = *stack;

	/* Update the previous node of the current top, if it exists */
	if (*stack != NULL)
		(*stack)->prev = new_node;

	/* Update the stack to point to the new top */
	*stack = new_node;
}
