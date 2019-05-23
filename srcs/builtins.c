/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:02:21 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/23 23:22:56 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		echo_basic(char **cmd, int i, int j)
{
	while (cmd[i][j] != '\0')
		ft_putchar(cmd[i][j++]);
	ft_putstr(" ");
	j = 0;
}

int			echo(char **cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[++i])
	{
		if (echo_path(cmd, i) != 1)
			echo_basic(cmd, i, j);
		j = 0;
	}
	ft_putstr("\n");
	return (1);
}

int			cd_builtin(char **cmd)
{
	char	*home;

	if (cmd[1])
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
		chdir(home);
		free(home);
	}
	return (1);
}
