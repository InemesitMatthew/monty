#include "monty.h"

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
 * main - Monty ByteCode Interpreter
 * @argc: The number of command-line arguments.
 * @argv: An array containing the command-line arguments.
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;
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

    /* Read and interpret Monty byte code instructions */
    while (getline(&line, &len, file) != -1)
    {
        line_number++;

        char *opcode = strtok(line, " \t\n");
        char *arg = strtok(NULL, " \t\n");

        if (opcode)
        {
            instruction_t *instruction = get_instruction(opcode);

            if (instruction)
            {
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

    /* Clean up */
    free_stack(stack);
    free(line);
    fclose(file);

    return 0;
}
