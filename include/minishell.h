#ifndef MS_H
# define MS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "../libft/libft.h"
#include "get_next_line/get_next_line.h"

char **g_env;

typedef struct          s_all
{
    char *input;
    char **command;
}                       t_all;

typedef struct          s_node
{
    char                *input;
	int			        *position;
    struct              s_node *next;
}                       t_node;

char                    *clean_input(char *input);
char                    **split_input(char *input, char **cmd);

void                    get_paths(char **env, char ***bin);
char                    *look_in_path(char **cmd, char **env);
void                    run(char *binpath, char **cmd, char **env, pid_t pid);
int                     check_current(char **cmd, pid_t pid);
int                     check_builtin(char **cmd, char **env);
int                     execute(char **cmd, char **env);

char                    *search_env(char *var);
int                     print_env();
void                    init_env(char **env);
int                     setenv_builtin(char **cmd, char **env);
int                     unsetenv_builtin(char **cmd, char **env);
int                     env_builtin(char **cmd, char **env);

int                     echo(char **cmd, char **env);
int                     cd_builtin(char **cmd, char **env);

void                    welcome();
void                    prompt_mod(char **promptpath, int i, char cwd[]);
void                    print_prompt();
void                    free_arr(char **cmd);


#endif