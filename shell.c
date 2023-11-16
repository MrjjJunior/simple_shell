#include "shell.h"

/**
 *
 */
void showprompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		char prompt[] = "cisfun$ ";

		write(STDOUT_FILENO, prompt, strlen(prompt));
		fflush(stdout);
	}
}

/**
 *
 */
int main(int argc, char *argv[])
{
	char *command = NULL;

	while(1)
	{
		showprompt();

		command = readcommand();

		if (command == NULL)
		{
			break;
		}

		executeCommand(command, argv[0]);
		free(command);
	}
	return (EXIT_SUCCESS);
}
