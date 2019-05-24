/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:11:26 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/24 02:42:57 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "sh21.h"

int			welcome(char **env)
{
	if (env[0] == NULL)
	{
		ft_putstr("I need an env to work.\n");
		return (-1);
	}
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
	return (1);
}

void		init_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	g_env = (char **)malloc(sizeof(char *) * (i + 10));
	g_env[i] = NULL;
	i = -1;
	while (env[++i])
		g_env[i] = ft_strdup(env[i]);
}

char		*search_env(char *var)
{
	char	*content;
	char	*line;
	int		i;

	content = ft_strdup(var);
	line = NULL;
	i = -1;
	while (g_env[++i])
	{
		if (ft_strncmp(g_env[i], var, ft_strlen(var)) == 0)
			line = ft_strdup(g_env[i]);
	}
	i = 0;
	if (line != NULL)
	{
		while (line[i] && line[i] != '=')
			i++;
		free(content);
		content = ft_strdup((line + (i + 1)));
		free(line);
	}
	return (content == NULL) ? NULL : (content);
}

int			print_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
	return (1);
}

void		free_arr(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		ft_strdel(&cmd[i++]);
	free(cmd);
	cmd = NULL;
}
