#define _GNU_SOURCE
#include "monty.h"

bus_t bus = {NULL, NULL, NULL, 0};

int main(int argc, char **argv)
{
    char *content;
    size_t size = 0;
    FILE *file;
    ssize_t read_line = 1;
    stack_t *stack = NULL;
    unsigned int counter = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        return (EXIT_FAILURE);
    }
    file = fopen(argv[1], "r");
    bus.file = file;

    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return (EXIT_FAILURE);
    }

    while (read_line > 0)
    {
        content = NULL;
        read_line = getline(&content, &size, file);
        bus.content = content;
        counter++;
        if (read_line > 0)
        {
            execute_instruction(content, &stack, counter);
        }
        free(content);
    }
    free_stack(stack);
    fclose(file);
    return (EXIT_SUCCESS);
}
