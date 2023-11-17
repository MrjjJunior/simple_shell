#include "shell.h"
/**
 * exitShell - Handles the "exit" command.
 *
 * @command: The input string to check.
 */
void exitShell(char *command)
{
	if (stringCom(command, "exit") == 0)
	{
		_exit(EXIT_SUCCESS);
	}
}

/**
 * printEnv - Handles the "env" by printing the
 * the current environment
 *
 * @command: The input string to check.
 */
void printEnv(char *command)
{
	if (stringCom(command, "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			env++;
		}
	}
}
