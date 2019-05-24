/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:02:21 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/24 02:31:19 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		cd_oldpwd(char *oldpwd)
{
	char	*temp;
	int		i;

	i = -1;
	while (g_env[++i])
	{
		if (ft_strncmp(g_env[i], "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			ft_strdel(&g_env[i]);
			temp = ft_strdup("OLDPWD=");
			g_env[i] = ft_strjoin(temp, oldpwd);
			free(temp);
		}
	}
}

void		cd_pwd(void)
{
	char	*temp;
	char	oldpwd[4096];
	int		i;

	i = -1;
	ft_bzero(oldpwd, 4096);
	getcwd(oldpwd, 4096);
	while (g_env[++i])
	{
		if (ft_strncmp(g_env[i], "PWD", ft_strlen("PWD")) == 0)
		{
			ft_strdel(&g_env[i]);
			temp = ft_strdup("PWD=");
			g_env[i] = ft_strjoin(temp, oldpwd);
			free(temp);
		}
	}
}

int			oldpwd_n_home(char *cmd)
{
	char	*temp;

	if (!cmd)
	{
		temp = search_env("HOME");
		chdir(temp);
		ft_strdel(&temp);
		return (1);
	}
	if (strcmp(cmd, "-") == 0)
	{
		temp = search_env("OLDPWD");
		chdir(temp);
		ft_strdel(&temp);
		return (1);
	}
	return (-1);
}

int			cd_builtin(char **cmd)
{
	char	oldpwd[4096];

	if (cmd[1])
	{
		if (oldpwd_n_home(cmd[1]) == 1)
			return (1);
		getcwd(oldpwd, 4096);
		if (!chdir(cmd[1]))
		{
			cd_oldpwd(oldpwd);
			cd_pwd();
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(cmd[1]);
		}
	}
	else if (oldpwd_n_home(cmd[1]) == 1)
		return (1);
	return (1);
}
