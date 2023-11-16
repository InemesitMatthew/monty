#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * process_file - Processes the Monty byte code instructions from a file.
 * @file: A pointer to the file.
 * @stack: A pointer to the top of the stack.
 */
void process_file(FILE *file, stack_t **stack)
{
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;

    while (getline(&line, &len, file) != -1)
    {
        line_number++;

        /* Tokenize the line to extract opcode and arguments */
        char *opcode = strtok(line, " \t\n");
        char *arg = strtok(NULL, " \t\n");

        if (opcode)
        {
            execute_instruction(opcode, stack, line_number, arg);
        }
    }

    free(line);
}

int main(int argc, char *argv[])
{
    FILE *file;
    stack_t *stack = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    process_file(file, &stack);

    /* Clean up */
    free_stack(stack);
    fclose(file);

    return 0;
}
