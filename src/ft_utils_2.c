/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:30:14 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/09 17:33:09 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_fd_in(int *i, char **av)
{
	int	fd_in;

	*i = 2;
	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
	{
		*i = 3;
		perror(av[1]);
	}
	else
		dup2(fd_in, STDIN_FILENO);
	close (fd_in);
	return (fd_in);
}

int	open_fd_out(int ac, char **av)
{
	int	fd_out;

	fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		perror(av[ac - 1]);
	return (fd_out);
}
