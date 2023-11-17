#include "shell.h"
/**
 * readCommand -function allow user to input a command and it reads it.
 *
 * Return: A pointer to the dynamically allocated string containing the input
 *         line, or NULL if end-of-file is reached.
 */
char *readCommand(void)
{
	char *command = NULL;
	size_t commandLen = 0;

	if (getline(&command, &commandLen, stdin) == -1)
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
	char *path, *pathCp, *pathToken, *filePath;
	int cmdLen, dirLen;
	struct stat buf;

	path = "/bin:/sbin:/tmp";
	if (path)
	{
		pathCp = _strdup(path);
		cmdLen = stringLen(in);
		filePath = NULL;
		pathToken = stringTokenizer(pathCp, ":");
		while (pathToken != NULL)
		{
			dirLen = stringLen(pathToken);
			filePath = malloc(cmdLen + dirLen + 2);
			stringCpy(filePath, pathToken);
			stringCat(filePath, "/");
			stringCat(filePath, in);
			stringCat(filePath, "\0");
			if (stat(filePath, &buf) == 0)
			{
				free(pathCp);
				return (filePath);
			}
			else
			{
				free(filePath);
				filePath = NULL;
				pathToken = stringTokenizer(NULL, ":");
			}
		}
		free(pathCp);
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
	char *token = stringTokenizer(command, " ");
	int arg_count = 0;

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = stringTokenizer(NULL, " ");
	}
	args[arg_count] = NULL;

	return (arg_count);
}

/**
* executeChild - Execute the command in the child process.
*
* @args: The arguments to execute.
* @cmd: The path of the command.
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
* executeCommand - Execute a command.
*
* @command: The command to execute.
* @argv0: The name of the calling program for error reporting.
*/
void executeCommand(char *command, char *argv0)
{
	char *shortCommand = command + _strspn(command, " "), *cmd;
	int command_length = stringLen(shortCommand);
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
		char *args[MAX_INPUT_LENGTH], *token = stringTokenizer(shortCommand, " ");
		int arg_count = 0;

		while (token != NULL)
		{
			args[arg_count++] = token;
			token = stringTokenizer(NULL, " ");
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
