#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_COMMAND_SIZE 1024

/**
 * prompt - Displays a prompt to user.
 */
void prompt(void)
{
	printf("cisfun$ ");
}

/**
 * userInput - Gets user command.
 * @command: the command.
 * @size: size of command.
 */
void userInput(char *command)
{
	if (fgets(command, MAX_COMMAND_SIZE, stdin) == NULL)
	{
		printf("\n");
		exit(EXIT_SUCCESS);
		
	}
	command[strcspn(command, "\n")] = '\0';
}

/**
 * execute_Command - execute commands.
 * @command: the command that must be executed.
 */
void execute_Command(const char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork.\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (execlp(command, command, NULL) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;
		waitpid(child_pid, &status, 0);
	}
}

/**
 * printEnvironment - funtion prints environment.
 */
extern char **environ;
char command[100];

void printEnvironment()
{
	if (strcmp(command, "env") == 0)
	{
		char *env_var;
		int i = 0;

		while ((env_var = environ[i++]) != NULL)
		{
			printf("%s\n", env_var);
		}
	}
}

/**
 * main - shell program.
 *
 * Return: Always (0).
 */
int main(void)
{
	char command[MAX_COMMAND_SIZE];

	while (1)
	{
		prompt();
		userInput(command);
		printEnvironment(command);

		if (strcmp(command, "exit") == 0)
		{
			break;
		}

		execute_Command(command);
	}
	return (0);
}
