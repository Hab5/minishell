#include "../include/minishell.h"

void welcome()
{
    int c;
    FILE *file;
    file = fopen("welcome", "r");
    ft_putstr("\033[1;32m");
    if (file)
    {
        while ((c = getc(file)) != EOF)
            ft_putchar(c);
    fclose(file);
    }
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
    while(g_env[++i])
    {
        if(ft_strstr(g_env[i], var) != 0)
            line = ft_strdup(g_env[i]);
    }
    return (line);
}

int print_env(char **env)
{
    int i;

    i = -1;
    while(env[++i])
        ft_putendl(env[i]);
    return(1);
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