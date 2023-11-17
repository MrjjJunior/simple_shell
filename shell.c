#include "shell.h"

/**
 * showPrompt - Prints the shell prompt.
 */
void showPrompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		char prompt[] = "cisfun$ ";

		write(STDOUT_FILENO, prompt, stringLen(prompt));
		fflush(stdout);
	}
}

/**
 * main- shell program
 * @argc: argument count..
 * @argv: commandline arguments.
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	char *command = NULL;

	UNUSED(argc);

	while (1)
	{
		showPrompt();
		command = readCommand();

		if (command == NULL)
		{
			break;
		}
		exitShell(command);
		printEnv(command);

		executeCommand(command, argv[0]);
		free(command);
	}
	return (EXIT_SUCCESS);
}
