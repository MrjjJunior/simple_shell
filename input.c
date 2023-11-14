#include "shell.h"

/**
 * inputCommand - allows user to input command.
 *
 * @command: user's command.
 * @size: size.
 */
void inputCommand(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("./shell: ");
			exit(EXIT_FAILURE);
		}
	}
	command[strcspn(command, "\n")] = '\0';
}
