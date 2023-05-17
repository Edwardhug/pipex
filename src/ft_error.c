/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:25:27 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/17 17:26:03 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_remove_file(char **av, int fd)
{
	int		id;
	char	**exec_arg;

	id = fork();
	if (id == 0)
	{
		exec_arg = malloc(sizeof(char *) * 3);
		if (!exec_arg)
			return (1);
		exec_arg[0] = malloc(sizeof(char) * (ft_strlen("/usr/bin/rm")));
		if (!exec_arg[0])
		{
			free(exec_arg);
			EXIT_FAILURE;
		}
		exec_arg[0] = ft_strdup("/usr/bin/rm");
		exec_arg[1] = av[4];
		exec_arg[2] = NULL;
		execv(exec_arg[0], exec_arg);
	}
	else
		waitpid(id, 0, 0);
}

int	ft_error_pipex(int ac, char **av)
{
	int fd;

	if (ac != 5)
	{
		ft_printf("Error\nWrong number of argument\n");
		return (0);
	}
	fd = open(av[4], O_RDONLY);
	if (fd)
	{
		close(fd);
		ft_remove_file(av, fd);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nNo file1\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	return (fd);
}