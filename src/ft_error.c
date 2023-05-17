/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:25:27 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/17 18:18:31 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_remove_file(char *file)
{
	int		id;
	char	**exec_arg;

	id = fork();
	if (id == 0)
	{
		exec_arg = malloc(sizeof(char *) * 3);
		if (!exec_arg)
			exit(EXIT_FAILURE);			// may have some leaks
		exec_arg[0] = malloc(sizeof(char) * (ft_strlen("/usr/bin/rm")));
		if (!exec_arg[0])
		{
			free(exec_arg);
			exit(EXIT_FAILURE);
		}
		exec_arg[0] = ft_strdup("/usr/bin/rm");
		exec_arg[1] = file;
		exec_arg[2] = NULL;
		execv(exec_arg[0], exec_arg);
	}
	else
		waitpid(id, 0, 0);
}

int ft_check_name(char **av)
{
	int fd;

	fd = open(av[4], O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		ft_remove_file(av[4]);
	}
	fd = open("tamp", O_RDONLY);
	// ft_printf("%d\n", fd);
	if (fd != -1)
	{
		close(fd);
		ft_remove_file("tamp");
	}
	return (0);
}

int	ft_error_pipex(int ac, char **av)
{
	int fd;

	if (ac != 5)
	{
		ft_printf("Error\nWrong number of argument\n");
		return (0);
	}
	ft_check_name(av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nNo file1\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	return (fd);
}