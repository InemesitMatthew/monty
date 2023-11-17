#include "monty.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

instruction_t instructions[] = {
    {"pall", pall},
    {"push", push},
    {NULL, NULL}
};

void execute_instruction(char *opcode, stack_t **stack, unsigned int line_number, char *arg) {
    int i;
    for (i = 0; instructions[i].opcode; i++) {
        if (strcmp(opcode, instructions[i].opcode) == 0) {
            instructions[i].f(stack, line_number, arg);
            return;
        }
    }

    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
    free_stack(*stack);
    free(opcode);
    exit(EXIT_FAILURE);
}

void free_stack(stack_t *stack) {
    stack_t *temp;
    while (stack) {
        temp = stack->next;
        free(stack);
        stack = temp;
    }
}
