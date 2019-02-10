#include "../include/minishell.h"

int             check_builtin(char **cmd, char **env)
{
    if(ft_strequ(cmd[0], "exit"))
        exit (1);
    if(ft_strequ(cmd[0], "echo"))
        return(echo(cmd)); 
    if(ft_strequ(cmd[0], "cd"))
        return(cd_builtin(cmd, env));
    if(ft_strequ(cmd[0], "env"))  
            return(print_env(env));
    if(ft_strequ(cmd[0], "setenv"))
        {printf("setenv not here yet\n");return (1);}
    if(ft_strequ(cmd[0], "unsetenv"))
        {printf("unsetenv not here yet\n");return (1);}
    return(0);
}

void            get_paths(char **env, char ***bin)
{
    char        *pathline;
    
    init_env(env);
    pathline = search_env("PATH");
    *bin = ft_strsplit(pathline, ':');
    free_arr(g_env);
    free(pathline);
}

char            *look_in_path(char **cmd, char **env)
{
    struct stat st;
    char        **bin;
    char        *temp;
    char        *binpath;

    get_paths(env, &bin);
    bin[0] += 5;
    int i = -1;
    while(bin[++i])
    {
        temp = ft_strjoin(bin[i], "/");
        binpath = ft_strjoin(temp, cmd[0]);
        free(temp);
        if(!(stat(binpath, &st)) && (st.st_mode & S_IXUSR))
            break;
        free(binpath);
        //free(g_env);
        binpath = NULL;
    }
    bin[0] -= 5;
    free_arr(bin);
    return (binpath != NULL) ? binpath : NULL;
}

void             run(char *binpath, char **cmd, char **env, pid_t pid)
{
    pid = fork();
    if (pid == 0)
    {
        execve(binpath, cmd, env);
        exit(0);
    }
    else if (pid < 0)
        ft_putstr("fork() failed.\n");
}

int             check_current(char **cmd, pid_t pid)
{
    struct stat st;

    if(!(stat(cmd[0], &st)) && (st.st_mode & S_IXUSR))
    {
        pid = fork();
        if (pid == 0)
        {
            execve(cmd[0], cmd, 0);
            exit(0);
        }
        else if (pid < 0)
            ft_putstr("fork() failed.\n");
        wait(&pid);
        return(1);
    }
    return (-1);
}