#include "../include/minishell.h"

void welcome()
{
    ft_putstr("\033[1;32m");
    ft_putstr("    __  ________   ___________ __  __________    __ \n");
    usleep(100000);
    ft_putstr("   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / / \n");
    usleep(100000);
    ft_putstr("  / /|_/ // //  |/ // / \\__ \\/ /_/ / __/ / /   / /\n");
    usleep(100000);
    ft_putstr(" / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n");
    usleep(100000);
    ft_putstr("/_/  /_/___/_/ |_/___//____/_/ /_/_____/___________/\n");
    usleep(100000);
    ft_putstr("                                        / // /|__ \\\n");
    usleep(100000);
    ft_putstr("                                       / // /___/ / \n");
    usleep(100000);
    ft_putstr("                                      /__  __/ __/  \n");
    usleep(100000);
    ft_putstr("                                        /_/ /____/  \n");
    ft_putstr("\033[0m");
}

void	init_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	g_env = (char **)malloc(sizeof(char *) * (i + 10));
	g_env[i] = NULL;
	i = -1;
	while (env[++i])
		g_env[i] = ft_strdup(env[i]);
}

char *search_env(char *var)
{
    char *line;
    int i;

    line = NULL;
    i = -1;
    while (g_env[++i])
    {
        if (ft_strstr(g_env[i], var) != 0)
            line = ft_strdup(g_env[i]);
    }
    return (line);
}

int print_env(char **env)
{
    int i;

    i = -1;
    while (env[++i])
        ft_putendl(env[i]);
    return (1);
}

void free_arr(char **cmd)
{
    int i;
    
    i = -1;
    while (cmd[++i])
        ft_strdel(&cmd[i]);
    free(cmd);
    cmd = NULL;
}