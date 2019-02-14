/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 23:30:08 by mbellaic          #+#    #+#             */
/*   Updated: 2018/09/12 00:12:10 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				reset_stock(char **line, char **stock)
{
	*line = *stock;
	*stock = NULL;
	return (1);
}

int				check_n(char *stock)
{
	int			i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int				clean_stock(char **line, char **stock)
{
	char		*temp;
	int			len;

	len = ft_strlen(*stock);
	*line = ft_strsub(*stock, 0, check_n(*stock));
	temp = *stock;
	*stock = ft_strsub(*stock, check_n(*stock) + 1, len - check_n(*stock));
	free (temp);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char	*stock;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (!stock)
		stock = ft_strdup("");
	ret = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		stock = ft_strjoinfree(stock, buf);
		if (check_n(stock) != -1)
			return (clean_stock(line, &stock));
	}
	if (ret == -1)
		return (-1);
	if (check_n(stock) != -1)
		return (clean_stock(line, &stock));
	if (ft_strlen(stock) != 0)
		return (reset_stock(line, &stock));
	return (0);
}
