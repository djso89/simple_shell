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


/*free_mem.c*/
void free_upto_n(char **av, unsigned int n);
void free_av(char **cmds);
void free_all(char *line, char **av);
void free3(char *line, char **av, char *fn);
/*kshell.c*/
void check_prompt(void);
char *get_input();
char *check_input(char *cmd, char **env);
void check_exit(int ext_stat, char *cmd, char *line, char **av);
/*avtok.c*/
unsigned int num_words(char *line, char delim);
char **line_to_av(char *line);

/*str_helpers.c*/
int _strncmp(const char *s1, const char *s2, size_t n);
unsigned int _strlen(char *s);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);

/*env_helpers.c*/
char *_getenv(const char *name, char **env);
void show_env(char **env, char *line, char **av);
/*this is for handling ctrl - c*/
void sigintHandler(int sig_num);

/*error.c*/
int _putchar(char c);
void print_number(int n);
void show_error(char *argv, char *cmd, int e_num, int cmd_num);
void errno_file(int *e_num, char *argv0, char **av, char *line, int cmd_num);
void errno_perm(int *es, char *argv0, char **av, char *line, int cn, char *fn);

/*dir_helpers.c*/
unsigned int get_num_dir(char *dir);
char *get_dir_cmd(char *dir, char *cmd);
char **get_dir(char **env);

/*exit_helpers.c*/
int get_exit_stat(int stat);

/*execute.c*/
int execute(pid_t pgm, char **av, char *line, char **env, char *fname);


#endif /*KSHELL_H */
