/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:46 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/17 16:10:22 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_apply_cmd1(char **av, int fd)
{
	char	**exec_arg;

	exec_arg = malloc(sizeof(char *) * 3);
	if (!exec_arg)
		return (1);
	exec_arg[0] = malloc(sizeof(char) * (ft_strlen("/usr/bin/") + ft_strlen(av[2])));
	if (!exec_arg[0])
	{
		free(exec_arg);
		return (1);
	}
	exec_arg[0] = ft_strjoin("/usr/bin/", av[2]);
	exec_arg[1] = av[1];
	exec_arg[2] = NULL;
	execv(exec_arg[0], exec_arg);
	return (0);
}

int	main(int ac, char **av)
{
	int 	fd;
	int 	id;

	if (ac != 5)
	{
		ft_printf("Error\nWrong number of argument\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nNo file1\n");
		close(fd);
		return (0);
	}
	id = fork();
	// ft_printf("id fork = %d\n", id);
	if (id == 0)
		ft_apply_cmd1(av, fd);
	else
	{
		waitpid(id, 0, 0);
	}
	close(fd);
} 