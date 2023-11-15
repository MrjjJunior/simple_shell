#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void display_prompt()
{
	printf("#cisfun$ ");
}

void read_input(char *command)
{
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
        // Handle Ctrl+D (EOF condition)
		printf("\n");
		exit(EXIT_SUCCESS); // Exit gracefully
	}
	command[strcspn(command, "\n")] = '\0'; // Remove newline character
}

void execute_command(char *command)
{
	char *args[MAX_ARGS]; // Array to store command and its arguments
	int arg_count = 0;

	char *token = strtok(command, " "); // Tokenize input based on spaces

	while (token != NULL && arg_count < MAX_ARGS - 1)
	{
		args[arg_count++] = token; // Store each token as an argument
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL; // NULL-terminate the argument list

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
        // Child process
		if (execvp(args[0], args) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
        // Parent process
	int status;
	waitpid(pid, &status, 0); // Wait for child process to finish
	}
}

int main()
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		display_prompt();
		read_input(command);
		execute_command(command);
	}

	return 0;
}
