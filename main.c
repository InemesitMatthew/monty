#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * main - Monty ByteCode Interpreter
 * @argc: The number of command-line arguments.
 * @argv: An array containing the command-line arguments.
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Initialize the stack
    stack_t *stack = NULL;

    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;

    // Read and interpret Monty byte code instructions
    while (getline(&line, &len, file) != -1)
    {
        line_number++;

        // Tokenize the line to extract opcode and arguments
        char *opcode = strtok(line, " \t\n");
        char *arg = strtok(NULL, " \t\n");

        if (opcode)
        {
            // Find corresponding function for the opcode
            instruction_t *instruction = get_instruction(opcode);

            if (instruction)
            {
                // Execute the opcode function
                instruction->f(&stack, line_number, arg);
            }
            else
            {
                fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
                free_stack(stack);
                free(line);
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Clean up
    free_stack(stack);
    free(line);
    fclose(file);

    return 0;
}
