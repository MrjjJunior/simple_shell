#include "shell.h"

extern char **environ;
char command[100];

/**
 * printEnvironment - Funtion prints environment.
 */

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
