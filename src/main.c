/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:46 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/17 17:16:15 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_init_tamp(int ac, char **av, int fd)
{
	int	tamp;

	tamp = open(av[4], O_WRONLY | O_CREAT, 0777);
	if (tamp == -1)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
}

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
	int		tamp;

	fd = ft_error_pipex(ac, av);
	tamp = ft_init_tamp(ac, av, fd);
	tamp = open(av[4], O_WRONLY | O_CREAT, 0777);
	// if (tamp == -1)
	// {
	// 	close(fd);
	// 	return (2);
	// }
	dup2(tamp, 1);
	id = fork();
	if (id == 0)
		ft_apply_cmd1(av, fd);
	else
	{
		waitpid(id, 0, 0);
	}
	close(fd);
	close(tamp);
} 