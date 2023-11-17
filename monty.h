#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>

/**
 * struct stack_s - Doubly linked list representation of a stack (or queue)
 * @n: Integer stored in the node
 * @prev: Pointer to the previous element of the stack (or queue)
 * @next: Pointer to the next element of the stack (or queue)
 */
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - Struct for opcode and its associated function
 * @opcode: The opcode
 * @f: The function associated with the opcode
 */
typedef struct instruction_s
{
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number, char *arg);
} instruction_t;

/* Function prototypes */
void execute_instruction(char *opcode, stack_t **stack, unsigned int line_number, char *arg);
void free_stack(stack_t *stack);
void process_file(FILE *file, stack_t **stack);
void push(stack_t **stack, unsigned int line_number, char *value);
void pall(stack_t **stack, unsigned int line_number);

#endif /* MONTY_H */
