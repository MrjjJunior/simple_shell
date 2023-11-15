#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_COMMAND_SIZE 1024

/**
 * prompt - Displays a prompt to user.
 */
void prompt()
{
	printf("cisfun$ ");
}

/**
 * userInput - Gets user command.
 * @input: the command.
 */
void userInput(char *command)
{
	fgets(command, MAX_COMMAND_SIZE, stdin);
	command[strcspn(command, "\n")] = 0;
}

/**
 * executeCommand - execute commands.
 * @command: the command that must be executed.
 */
void executeCommand(char *command)
{
	char *args[MAX_COMMAND_SIZE];
	int arg_count = 0;
	char *token = strtok(command, " ");

	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}

	if (strcmp(command, "env") == 0)
	{
		char *env_var = getenv("PATH");

		if (env_var != NULL)
		{
			printf("PATH = %s\n", env_var);
		}
		return;
	}

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	if (access(args[0], X_OK) != -1)
	{
		pid_t pid = fork();

		if (pid == 0)
		{
			execvp(args[0], args);
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("Fork failed");
		}
		else
		{
			int status;
			wait(&status);
		}
	}
	else
	{
		printf("./shell: No such file or directory\n");
	}
}

/**
 * main - shell .
 * return: Always (0).
 */
int main()
{
	char command[MAX_COMMAND_SIZE];

	while (1)
	{
		prompt();
		userInput(command);
		executeCommand(command);
	}
	return (0);
}
