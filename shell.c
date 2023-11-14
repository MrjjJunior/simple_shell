#include "shell.h"

#include "prompt.c"
#include "input.c"
#include "exec.c"
#include "env-main.c"
#include "cd.c"

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

		if (strncmp(command, "cd ", 3) == 0)
		{
			const char *path = command +3;
			change_directory(path);
		}
		executeCommand(command);
		
	}
	return (0);
}
