#include "../include/minishell.h"

int             check_builtin(char **cmd, char **env)
{
    if(ft_strequ(cmd[0], "exit"))
        exit (1);
    if(ft_strequ(cmd[0], "echo"))
        {printf("echo not here yet\n");return (1);}
    if(ft_strequ(cmd[0], "cd"))
        {printf("cd not here yet\n");return (1);}
    if(ft_strequ(cmd[0], "env"))  
            return(print_env());
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
        binpath = NULL;
    }
    bin[0] -= 5;
    free_arr(bin);
    return (binpath != NULL) ? binpath : NULL;
}

int             execute(char **cmd, char **env)
{
    pid_t       pid;
    char        *binpath;
    
    if(check_builtin(cmd, env) != 0)
        return(1); 
    if ((binpath = look_in_path(cmd, env)) == NULL)
    {
        printf("minishell: command not found: %s\n", cmd[0]);
        return (-1);
    }
    pid = fork();
    if (pid == 0)
    {
        if (execve(binpath, cmd, env) < 0)
            printf("exec fail\n");
        exit(0);
    }
    else if (pid < 0)
    {
        printf("fork fail\n");
        return (-1);
    }
    free(binpath);
    wait(&pid);
    return (1);
}