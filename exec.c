#include "shell.h"

/**
 * executeCommand - funtion executes command
 *
 * @command: the command to be executed
 */
void executeCommand(const char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error processing fork.\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *args[100];
		int arg_count = 0;

		char *token = strtok((char *)command, " ");

		while  (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		execvp(args[0], args);

		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(0);
	}
}
