/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:38:06 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/17 17:58:37 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_init_tamp(int fd)
{
	int	tamp;

	tamp = open("tamp", O_WRONLY | O_CREAT, 0777);
	if (tamp == -1)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	return (tamp);
}

int	ft_init_fileout(char**av, int fd, int tamp)
{
	int	fileout;
	
	fileout = open(av[4], O_WRONLY | O_CREAT, 0777);
	if (fileout == -1)
	{
		close (fd);
		ft_remove_file("tamp");
		close (tamp);
		exit(EXIT_FAILURE);
	}
	return (fileout);
}