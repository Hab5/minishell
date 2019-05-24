/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:09:10 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/24 02:48:13 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh21.h"

int			execute(char **cmd, char **env)
{
	pid_t	pid;
	char	*binpath;

	pid = 0;
	if (check_builtin(cmd) != 0)
		return (1);
	if (check_current(cmd, pid) > 0)
		return (1);
	if ((binpath = look_in_path(cmd)) == NULL)
	{
		if (cmd[0])
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(cmd[0]);
		}
		return (-1);
	}
	run(binpath, cmd, env, pid);
	free(binpath);
	wait(&pid);
	return (1);
}

int			main(int argc, char **argv, char **env)
{
	char	**cmd;
	t_multi	*multi_input;
	char	*input;
	t_pos	pos;

	(void)argc;
	(void)argv;
	multi_input = NULL;
	input = NULL;
	cmd = NULL;
	if ((welcome(env)) == -1)
		return (0);
	init_prompt(&pos);
	init_env(env);
	while (1)
		if ((input = prompt(multi_input, &pos)))
			if ((input = clean_input(input)))
				if (((cmd = split_input(input, cmd))))
				{
					cmd = expand(cmd);
					execute(cmd, env);
					free_arr(cmd);
				}
	return (0);
}
