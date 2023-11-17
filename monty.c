#include "monty.h"

/**
 * execute_instruction - Executes the Monty bytecode instruction.
 * @opcode: The opcode to execute.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the file.
 * @arg: The argument for the opcode (if any).
 */
void execute_instruction(char *opcode, stack_t **stack, unsigned int line_number, char *arg)
{
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        {NULL, NULL}};

    int i = 0;

    while (instructions[i].opcode)
    {
        if (strcmp(opcode, instructions[i].opcode) == 0)
        {
            instructions[i].f(stack, line_number, arg);
            return;
        }
        i++;
    }

    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
    free_stack(*stack);
    exit(EXIT_FAILURE);
}
