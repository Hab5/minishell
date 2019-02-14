/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 00:15:09 by mbellaic          #+#    #+#             */
/*   Updated: 2019/02/14 20:58:15 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define _GNU_SOURCE
# define _POSIX_C_SOURCE 200809L

# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include "../libft/libft.h"

# define BUFF_SIZE 64

int	get_next_line(const int fd, char **line);
#endif
