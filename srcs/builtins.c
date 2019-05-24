/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:02:21 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/24 02:16:42 by mbellaic         ###   ########.fr       */
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
		echo_basic(cmd, i, j);
		j = 0;
	}
	ft_putstr("\n");
	return (1);
}
