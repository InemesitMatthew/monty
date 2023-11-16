#include "monty.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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

/**
 * push - Pushes an element to the stack.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the file.
 * @value: The value to push.
 */
void push(stack_t **stack, unsigned int line_number, char *value)
{
    int num;

    if (!value || (!isdigit(*value) && *value != '-'))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }

    num = atoi(value);

    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node)
    {
        fprintf(stderr, "Error: malloc failed\n");
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }

    new_node->n = num;
    new_node->next = *stack;
    new_node->prev = NULL;

    if (*stack)
        (*stack)->prev = new_node;

    *stack = new_node;
}

/**
 * pall - Prints all the values on the stack.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the file.
 */
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;

    (void)line_number; // Unused parameter

    while (current)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}
