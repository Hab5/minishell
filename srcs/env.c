#include "../include/minishell.h"

int set(char **cmd)
{
    int i;
    char *temp;

    i = 0;
    while (g_env[++i])
    {
        if (ft_strstr(g_env[i], cmd[1]) != 0)
        {
            free(g_env[i]);
            temp = ft_strjoin(cmd[1], "=");
            g_env[i] = ft_strjoin(temp, cmd[2]);
            free(temp);
            return (1);
        }
    }
    return (0);
}

int setenv_builtin(char **cmd, char **env)
{
    if (!cmd[2] || !cmd[1] || cmd[3])
    {
        ft_putstr("usage: setenv [NAME] [VALUE]\n");
        return (1);
    }
    if (set(cmd) > 0)
        return (1);
    ft_putstr(cmd[1]);
    ft_putstr(" does not exist.\n");
    return (1);
}

int unset(char **cmd)
{
    int i;

    i = 0;
    while(g_env[++i])
    {
        if(ft_strstr(g_env[i], cmd[1]) != 0)
        {
            free(g_env[i]);
            g_env[i] = ft_strjoin(cmd[1], "=");
            return (1);
        }
    }
    return (0);
}

int unsetenv_builtin(char **cmd, char **env)
{
    if (cmd[2] || !cmd[1])
    {
        ft_putstr("usage: unsetenv [NAME]\n");
        return (1);
    }
    if(unset(cmd) > 0)
        return (1);
    ft_putstr(cmd[1]);
    ft_putstr(" does not exist.\n");
    return (1);
}

int env_builtin(char **cmd, char **env)
{
    int i;
    int j;
    
    i = -1;
    j = 0;
    while (cmd[++i])
    {
        if (!cmd[1])
            print_env(g_env);
    }
    return (1);
}