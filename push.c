#include "monty.h"
#include <stdlib.h>

void push(stack_t **stack, unsigned int line_number, char *arg) {
    (void)line_number; /** Unused parameter */
    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    if (!arg || (!isdigit(*arg) && *arg != '-' && *arg != '+')) {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        free_stack(*stack);
        free(new_node);
        exit(EXIT_FAILURE);
    }

    new_node->n = atoi(arg);
    new_node->next = *stack;
    new_node->prev = NULL;

    if (*stack)
        (*stack)->prev = new_node;
    
    *stack = new_node;
}
