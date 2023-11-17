#include "shell.h"
/**
 * _strpbrk - Searches a string for any of a set of bytes.
 * @s: Pointer to the string to be searched.
 * @accept: Pointer to the string containing the bytes to search for.
 *
 * Return: A pointer to the first occurrence of a byte in s that matches one
 *         of the bytes in accept, or NULL if no such byte is found.
 */
char *_strpbrk(char *s, const char *accept)
{
	while (*s != '\0')
	{
		const char *c = accept;

		while (*c != '\0')
		{
			if (*s == *c)
			{
				return (s);
			}
			c++;
		}
		s++;
	}
	return (NULL);
}

/**
 * _strchar - Locates the first occurrence of a character in a string.
 * @s: Pointer to the string.
 * @c: Character to be located.
 *
 * Return: Pointer to the first occurrence of the character c in the string s,
 *         or NULL if the character is not found.
 */
char *_strchar(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (c == '\0')
	{
		return ((char *)s);
	}
	return ('\0');
}

/**
 * _strtok - Tokenize a string using specified delimiters
 * @str: The string to be tokenized
 * @delimiters: A string containing delimiters
 *
 * Return: A pointer to the next token, or NULL if no more tokens are found
 */
char *_strtok(char *str, const char *delimiters)
{
	static char *rest;
	char *token = rest;
	char *delimiter_position = _strpbrk(rest, delimiters);

	if (str != NULL)
	{
		rest = str;
	}

	if (rest == NULL || *rest == '\0')
	{
		return (NULL);
	}

	while (*rest != '\0' && _strchar(delimiters, *rest) != NULL)
	{
		rest++;
	}

	if (*rest == '\0')
	{
		return (NULL);
	}

	if (delimiter_position != NULL)
	{
		*delimiter_position = '\0';
		rest = delimiter_position + 1;
	}
	else
	{
		rest = NULL;
	}
	return (token);
}

/**
* _strlen - function that calculates the length of a string
* @str: length is to be calculated
* Return: length of the string
*/
int _strlen(char *str)
{
	char *len = str;

	while (*len != '\0')
	{
		len++;
	}
	return (len - str);
}
/**
 * _strcat - Concatenates two strings.
 * @destination: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the resulting string dest.
 */
char *_strcat(char *destination, char *src)
{
	char *ptr = destination;

	while (*ptr != '\0')
	{
		ptr++;
	}
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (destination);
}
#include "shell.h"
/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return:
 * - 0 if the strings are equal.
 * - a negative value if s1 is less than s2.
 * - a positive value if s1 is greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strcpy - Copying a string
 * destestination: Destination input
 * @src: Source Value
 * Return: The poiner to destination
 */
char *_strcpy(char *destination, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		destination[i] = src[i];
		i++;
	}
	destination[i++] = '\0';
	return (destination);
}

/**
 * _strdup - Returns a pointer to a newly allocated space in memory,
 *           which contains a copy of the string given as a parameter.
 * @s: The string to duplicate.
 * Return: Pointer to the duplicated string, or NULL if it fails.
 */
char *_strdup(char *s)
{
	size_t len = _strlen(s);
	char *copy = (char *)malloc(len + 1);

	if (s == NULL)
	{
		return (NULL);
	}

	if (copy == NULL)
	{
		return (NULL);
	}
	_strcpy(copy, s);

	return (copy);
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: Pointer to the string to be checked.
 * @accept: Pointer to the string containing the acceptable characters.
 *
 * Return: The number of bytes in the initial segment of s that consist only
 *         of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int count = 0;
	int i, j, fnd;

	for (i = 0; s[i] != '\0'; i++)
	{
		fnd = 0;
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				count++;
				fnd = 1;
				break;
			}
		}
		if (fnd == 0)
		{
			break;
		}
	}
	return (count);
}

/**
 * _strcspn - Calculates the length of a prefix substring in the input string
 * that does not contain any character from the reject set.
 *
 * @s: The input string to search.
 * @reject: The set of characters to reject.
 *
 * Return: The length of the prefix substri.
 */
int _strcspn(const char *s, const char *reject)
{
	const char *p, *r;
	int count = 0;

	for (p = s; *p != '\0'; p++)
	{
		for (r = reject; *r != '\0'; r++)
		{
			if (*p == *r)
			{
				return (count);
			}
		}
		count++;
	}
	return (count);
}
