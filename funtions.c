#include "shell.h"

/**
 *
 */
char *readcommand(void)
{
	char *command = NULL;
	size_t command_len = 0;

	if (getline(&command, &command_len, stdin) == -1)
	{
		free(command);
		return (NULL);
	}

	input[_strcspn(command, "\n")] = '\0';
}

/**
 *
 */
char *get_path(chaar *in)
{
	char *path, *pathCp, *pathToken, *filePath;
	int cmdLen, dirLen;
	struct stat buf;

	path = "/bin:/sbin:/tmp";
	if (path)
	{
		pathCp = strdup(path);
		cmdLen = strlen(in);
		filePath = NULL;
		pathToken = strtok(pathCp, ":");
		while (pathToken != NULL)
		{
			dirLen = _strlen(pathToken);
			filePath = malloc(cmd_len + dirlen + 2);
			_strcpy(filePath, pathToken);
			_strcat(filePath, "/");
			_strcat(filePath, in);
			_strcat(filePath, "\0");

			if (stat(filePath, &buf) == 0)
			{
				free(pathCp);
				return (filePath);
			}
			else
			{
				free(filePath);
				filePath = NULL;
				pathToken = strtok(NULL, ":");
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
 *
 */
int split_args(char *command, char **args)
{
	char *token = strtom(command, " ");
	int arg_count = 0;

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = str(NULL, " ");
	}
	args[arg_count] = NULL;

	return (arg_count);
}

/**
 *
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
 *
 */
void executeCommand(char *command, char *argv0)
{
	char *shortCmd = command + strspn(command, " "), *cmd;
	int cmdLen = strlen(shortCmd);
	pid_t pid = fork();

	if (cmdLen == 0)
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
		char *args[MAX_COMMAND_LENGTH], *token = strtok(shortCmd, " ");
		int arg_count = 0;

		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;
		cmd = get_path(args[0]);
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
