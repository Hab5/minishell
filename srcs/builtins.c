#include "../include/minishell.h"

int     echo(char **cmd) //NOPE
{
    int i;

    i = 0;
    while(cmd[++i])
    {
        ft_putstr(cmd[i]);
        ft_putstr(" ");
    }
    ft_putstr("\n");
    return(1);
}

int     cd_builtin(char **cmd, char **env)
{
    char *home;

    if(cmd[1] && !ft_strequ(cmd[1], "~") && !ft_strequ(cmd[1], "-"))
    {
        if(chdir(cmd[1]))
        {
            ft_putstr("cd: no such file or directory: ");
            ft_putendl(cmd[1]);
        }
    }
    else
    {
        init_env(env);
        home = search_env("HOME");
        home += 5;
        chdir(home);
        home -= 5;
        free(home);
    }
    return (1); 
}