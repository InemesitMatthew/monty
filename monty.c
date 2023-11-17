#include "monty.h"

int mode = STACK_MODE;

/**
 * main - entry point for the Monty Bytecode Interpreter
 * @argc: argument count
 * @argv: arguments
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Process file */
    process_file(file);

    /* Clean up */
    fclose(file);
    free(line);

    return EXIT_SUCCESS;
}

/**
 * process_file - process a Monty bytecode file
 * @file: pointer to the file to process
 */
void process_file(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;

    stack_t *stack = NULL;
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        /* Add more instructions as needed */
        {NULL, NULL}};

    while (getline(&line, &len, file) != -1)
    {
        line_number++;
        execute_instruction(line, &stack, line_number);
    }

    /* Clean up */
    free_stack(stack);
    free(line);
}

/**
 * execute_instruction - execute a Monty bytecode instruction
 * @opcode: opcode to execute
 * @stack: double pointer to the stack
 * @line_number: current line number in the file
 */
void execute_instruction(char *opcode, stack_t **stack, unsigned int line_number)
{
    int i;

    for (i = 0; instructions[i].opcode != NULL; i++)
    {
        if (strcmp(opcode, instructions[i].opcode) == 0)
        {
            instructions[i].f(stack, line_number);
            return;
        }
    }

    fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
    exit(EXIT_FAILURE);
}
