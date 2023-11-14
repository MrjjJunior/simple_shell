#include "shell.h"

/**
 * change_directory - Funtion changes directory in shell program.
 */
void change_directory(const char *path)
{
	char current_path[1024];

	if (chdir(path) == 0)
	{
		getcwd(current_path, sizeof(current_path));
		setenv("PWD", current_path, 1);
	}
	else
	{
		perror("cd");
	}
}
