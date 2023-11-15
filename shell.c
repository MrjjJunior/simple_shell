#include "shell.h"

#include "prompt.c"
#include "input.c"
#include "exec.c"
#include "env-main.c"

/**
 * main - Shell program.
 *
 * Return: Success(0).
 */

int main(void)
{
	char command[100];

	while (1)
	{
		prompt();
		inputCommand(command, sizeof(command));
		printEnvironment(command);
		
		if (strcmp(command, "exit") == 0)
		{
			break;
		}

		executeCommand(command);
		
	}
	return (0);
}
