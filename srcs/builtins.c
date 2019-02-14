#include "../include/minishell.h"

int         echo_path(char **cmd, int i)
{
    char    *var;
    
    if (cmd[i][0] == '$')
    {
        cmd[i] += 1;
        if((var = search_env(cmd[i])) != NULL)
        {
            ft_putstr(var);
            ft_putstr(" ");
            free (var);
            cmd[i] -= 1;
            return (1);
        }
        cmd[i] -= 1;
        free(var);   
    }
    return (0);
}

void        echo_basic(char **cmd, int i, int j)
{
    while (cmd[i][j] != '\0')
    {
        if (!(cmd[i][j] == '\'' || cmd[i][j] == '"'))
            ft_putchar(cmd[i][j]);
        j++;
    }
    ft_putstr(" ");
    j = 0;
}

int         echo(char **cmd)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (ft_strequ(cmd[1], "-n"))
        i++;
    while (cmd[++i])
    {
        if (echo_path(cmd, i) != 1)
        {
            echo_basic(cmd, i, j);
        }
        j = 0;
    }
    ft_putstr("\n");
    return (1);
}

int         cd_builtin(char **cmd)
{
    char    *home;

    if (cmd[1] && !ft_strequ(cmd[1], "~") && !ft_strequ(cmd[1], "-"))
    {
        if (chdir(cmd[1]))
        {
            ft_putstr("cd: no such file or directory: ");
            ft_putendl(cmd[1]);
        }
    }
    else
    {
        home = search_env("HOME");
        home += 5;
        chdir(home);
        home -= 5;
        free(home);
    }
    return (1); 
}
