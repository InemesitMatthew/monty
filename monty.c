#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Global variable to store the stack */
stack_t *stack;

/* Array of instruction functions */
instruction_t instructions[] = {
	{"pall", pall},
	{"push", push},
	{NULL, NULL}
};

/**
 * execute_instruction - Executes the specified instruction.
 * @opcode: The opcode to execute.
 * @line_number: The line number in the Monty byte code file.
 */
void execute_instruction(char *opcode, unsigned int line_number)
{
	unsigned int i;

	/* Iterate through the instructions array */
	for (i = 0; instructions[i].opcode != NULL; i++)
	{
		/* Compare opcodes */
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			/* Execute the corresponding function */
			instructions[i].f(&stack, line_number);
			return;
		}
	}

	/* If the opcode is not found, print an error message and exit */
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

/**
 * process_file - Processes a Monty byte code file.
 * @file: The Monty byte code file to process.
 */
void process_file(FILE *file)
{
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;

	/* Read each line from the file */
	while (getline(&line, &len, file) != -1)
	{
		/* Increment the line number */
		line_number++;

		/* Tokenize the line to extract opcode and arguments */
		char *opcode = strtok(line, " \t\n");
		char *arg = strtok(NULL, " \t\n");

		/* If the line is not empty and not a comment, execute the instruction */
		if (opcode != NULL && opcode[0] != '#')
			execute_instruction(opcode, line_number);
	}

	/* Free the allocated memory for the line */
	free(line);
}

/**
 * main - Entry point for the Monty interpreter.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	FILE *file;

	/* Check for the correct number of command-line arguments */
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	/* Open the Monty byte code file */
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* Process the Monty byte code file */
	process_file(file);

	/* Close the file */
	fclose(file);

	/* Free the stack before exiting */
	free_stack(stack);

	return (0);
}
