#ifndef MONTY_H
#define MONTY_H

#include <ctype.h>

typedef struct stack_s {
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

typedef void (*instruction_func)(stack_t **stack, unsigned int line_number, char *arg);

typedef struct instruction_s {
    char *opcode;
    instruction_func f;
} instruction_t;

void free_stack(stack_t *stack);
void execute_instruction(char *opcode, stack_t **stack, unsigned int line_number, char *arg);

extern instruction_t instructions[];

#endif /* MONTY_H */
