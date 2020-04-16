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
/*kshell.c*/
void check_prompt(void);
char *get_input();
char *check_input(char *cmd, char **env);
void check_exit(int ext_stat,char *cmd, char *line, char **av);
/*avtok.c*/
unsigned int num_words(char *line, char delim);
char **line_to_av(char *line);

/*str_helpers.c*/
int _strncmp(const char *s1, const char *s2, size_t n);
unsigned int _strlen(char *s);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
char *_getenv(const char *name, char **env);

/*this is for handling ctrl - c*/
void sigintHandler(int sig_num);


/*dir_helpers.c*/
unsigned int get_num_dir(char *dir);
char *get_dir_cmd(char *dir, char *cmd);
char **get_dir(char **env);



#endif /*KSHELL_H */
