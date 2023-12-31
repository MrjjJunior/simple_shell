#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

#define MAX_INPUT_LEN 1024

#define UNUSED(x) (void)(x)
#define MAX_INPUT_LENGTH 1024
extern char **environ;

char *_strpbrk(char *s, const char *accept);
char *_strchar(const char *s, char c);
char *_strtok(char *str, const char *delimiters);
int _strcmp(char *s1, char *s2);
int _strlen(char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(char *s);
int _strspn(char *s, char *accept);
int _strcspn(const char *s, const char *reject);

int main(int argc, char *argv[]);
void showPrompt(void);
void executeCommand(char *command, char *argv0);
char *inputCommand(void);
void exitShell(char *command);
void printEnv(char *command);
char **splitPath(void);
void freePath(char **path);
char *getPath(char *in);
int splitArgs(char *command, char **args);

#endif
