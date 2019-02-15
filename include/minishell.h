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
#include "get_next_line.h"

char **g_env;

char                    *clean_input(char *input);
char                    **split_input(char *input, char **cmd);

void                    get_paths(char ***bin);
char                    *look_in_path(char **cmd);
void                    run(char *binpath, char **cmd, char **env, pid_t pid);
int                     check_current(char **cmd, pid_t pid);
int                     check_builtin(char **cmd);
int                     execute(char **cmd, char **env);

char                    *search_env(char *var);
int                     print_env();
void                    init_env(char **env);
int                     setenv_builtin(char **cmd);
int                     unsetenv_builtin(char **cmd);
int                     env_builtin(char **cmd);

int                     echo(char **cmd);
int                     cd_builtin(char **cmd);

void                    welcome();
void                    prompt_mod(char **promptpath, int i, char cwd[]);
void                    print_prompt();
void                    free_arr(char **cmd);


#endif