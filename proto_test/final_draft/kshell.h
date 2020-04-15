#ifndef KSHELL_H
#define KSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

void free_upto_n(char **av, unsigned int n);
void free_av(char **cmds);

void check_prompt(void);

char *get_input();

unsigned int num_words(char *line, char delim);

char **line_to_av(char *line);

int _strncmp(const char* s1, const char* s2, size_t n);
char *_getenv(const char *name, char **env);

void sigintHandler(int sig_num);


/*directory helpers*/

unsigned int get_num_dir(char *dir);
char *get_dir_cmd(char *dir, char *cmd);
char **get_dir(char **env);



#endif /*KSHELL_H */
