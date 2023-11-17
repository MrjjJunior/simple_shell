#include "shell.h"
/**
 * inputCommand - Read a line of text from standard input.
 *
 * Return: A pointer to the dynamically allocated string containing the input
 *         line, or NULL if end-of-file is reached.
 */
char *inputCommand(void)
{
	char *command = NULL;
	size_t command_len = 0;

	if (getline(&command, &command_len, stdin) == -1)
	{
		free(command);
		return (NULL);
	}

	command[_strcspn(command, "\n")] = '\0';
	return (command);
}

/**
 * getPath - Locate a command in the system's PATH directories
 * @in: The command to search for
 *
 * Return: A pointer to the full path of the command if found, or NULL
 */
char *getPath(char *in)
{
	char *path, *path_cp, *path_token, *filePath;
	int cmd_len, dir_len;
	struct stat buf;

	path = "/bin:/sbin:/tmp";
	if (path)
	{
		path_cp = _strdup(path);
		cmd_len = _strlen(in);
		filePath = NULL;
		path_token = strtok(path_cp, ":");
		while (path_token != NULL)
		{
			dir_len = _strlen(path_token);
			filePath = malloc(cmd_len + dir_len + 2);
			_strcpy(filePath, path_token);
			_strcat(filePath, "/");
			_strcat(filePath, in);
			_strcat(filePath, "\0");
			if (stat(filePath, &buf) == 0)
			{
				free(path_cp);
				return (filePath);
			}
			else
			{
				free(filePath);
				filePath = NULL;
				path_token = strtok(NULL, ":");
			}
		}
		free(path_cp);
		free(filePath);
		if (stat(in, &buf) == 0)
		{
			return (in);
		}
		return (NULL);
	}
	return (NULL);
}


/**
* splitArgs - Split the command string into arguments.
*
* @command: The command string to split.
* @args: An array to store the arguments.
*
* Return: The number of arguments.
*/
int splitArgs(char *command, char **args)
{
	char *token = strtok(command, " ");
	int arg_count = 0;

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	return (arg_count);
}

/**
* executeChild - Execute the command in the child process.
*
* @args: The arguments to execute.
* @cmd: The full path of the command.
* @argv0: The name of the calling program for error reporting.
*/
void executeChild(char **args, char *cmd, char *argv0)
{
	if (execve(cmd, args, environ) == -1)
	{
		perror(argv0);
		exit(EXIT_FAILURE);
	}
}

/**
* executeCommand - Execute a command using fork and execlp.
*
* @command: The command to execute.
* @argv0: The name of the calling program for error reporting.
*/
void executeCommand(char *command, char *argv0)
{
	char *shortcommand = command + _strspn(command, " "), *cmd;
	int command_length = _strlen(shortcommand);
	pid_t pid = fork();

	if (command_length == 0)
	{
		return;
	}
	if (pid == -1)
	{
		perror(argv0);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[MAX_INPUT_LENGTH], *token = strtok(shortcommand, " ");
		int arg_count = 0;

		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;
		cmd = getPath(args[0]);
		if (cmd == NULL)
		{
			perror(argv0);
			return;
		}
		executeChild(args, cmd, argv0);
		free(cmd);
	}
	else
	{
		wait(NULL);
	}
}
