/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:06:11 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/24 00:20:46 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "sh21.h"

int				check_builtin(char **cmd)
{
	if (ft_strequ(cmd[0], "exit"))
	{
		default_term_mode();
		exit(1);
	}
	if (ft_strequ(cmd[0], "echo"))
		return (echo(cmd));
	if (ft_strequ(cmd[0], "cd"))
		return (cd_builtin(cmd));
	if (ft_strequ(cmd[0], "env"))
		return (env_builtin(cmd));
	if (ft_strequ(cmd[0], "setenv"))
		return (setenv_builtin(cmd));
	if (ft_strequ(cmd[0], "unsetenv"))
		return (unsetenv_builtin(cmd));
	return (0);
}

void			get_paths(char ***bin)
{
	char		*pathline;

	pathline = search_env("PATH");
	*bin = ft_strsplit(pathline, ':');
	ft_strdel(&pathline);
}

char			*look_in_path(char **cmd)
{
	struct stat st;
	char		**bin;
	char		*temp;
	char		*binpath;
	int			i;

	get_paths(&bin);
	i = -1;
	while (bin[++i])
	{
		temp = ft_strjoin(bin[i], "/");
		binpath = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (!(stat(binpath, &st)) && (st.st_mode & S_IXUSR))
			break ;
		free(binpath);
		binpath = NULL;
	}
	free_arr(bin);
	return (binpath != NULL) ? binpath : NULL;
}

void			run(char *binpath, char **cmd, char **env, pid_t pid)
{
	pid = fork();
	if (pid == 0)
	{
		execve(binpath, cmd, env);
		exit(0);
	}
	else if (pid < 0)
		ft_putstr("fork() failed.\n");
}

int				check_current(char **cmd, pid_t pid)
{
	struct stat st;

	if (!(stat(cmd[0], &st)) && (st.st_mode & S_IXUSR))
	{
		pid = fork();
		if (pid == 0)
		{
			execve(cmd[0], cmd, 0);
			exit(0);
		}
		else if (pid < 0)
			ft_putstr("fork() failed.\n");
		wait(&pid);
		return (1);
	}
	return (-1);
}
