#ifndef KSHELL_H
#define KSHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/*str_helpers.c */
unsigned int num_words(char *line, char delim);
int _strlen(char *s);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
char **line_to_av(char *line);

/* error.c */


/* kshell.c */
void check_prompt(void);

/* free_mem.c */
void free_av(char **cmds);

/* evn_helpers.c */
char *_getenv(const char *name, char **env);

#endif /*KSHELL_H */
