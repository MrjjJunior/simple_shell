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
char *stringChar(const char *s, char c);
char *stringTokenizer(char *str, const char *delimiters);
int stringCom(char *s1, char *s2);
int stringLen(char *str);
char *stringCpy(char *dest, char *src);
char *stringCat(char *dest, char *src);
char *_strdup(char *s);
int _strspn(char *s, char *accept);
int _strcspn(const char *s, const char *reject);

int main(int argc, char *argv[]);
void showPrompt(void);
void executeCommand(char *command, char *argv0);
char *readCommand(void);
void exitShell(char *command);
void printEnv(char *command);
char **splitPath(void);
void freePath(char **path);
char *getPath(char *in);
int splitArgs(char *command, char **args);
void executeChild(char **args, char *cmd, char *argv0);

#endif
