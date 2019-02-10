#include "../include/minishell.h"

void	init_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	g_env = (char **)malloc(sizeof(char *) * (i + 1));
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
    while(g_env[++i])
    {
        if(ft_strstr(g_env[i], var) != 0)
            line = ft_strdup(g_env[i]);
    }
    return (line);
}

int print_env()
{
    int i;

    i = -1;
    while(g_env[++i])
        ft_putendl(g_env[i]);
    return(1);
}