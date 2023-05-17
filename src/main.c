/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:46 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/17 18:19:34 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_apply_cmd2(char **av, int fd, int tamp)
{
	char	**exec_arg;
	int		fileout;

	fileout = ft_init_fileout(av, fd, tamp);
	dup2(fileout, 1);
	exec_arg = malloc(sizeof(char *) * 3);
	if (!exec_arg)
		return (1);
	exec_arg[0] = malloc(sizeof(char) * (ft_strlen("/usr/bin/") + ft_strlen(av[3])));
	if (!exec_arg[0])
	{
		free(exec_arg);
		return (1);
	}
	exec_arg[0] = ft_strjoin("/usr/bin/", av[3]);
	exec_arg[1] = av[4];
	exec_arg[2] = NULL;
	execv(exec_arg[0], exec_arg);
	return (0);
}

int	ft_apply_cmd1(char **av)
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
	int 	id[2];
	int		tamp;

	fd = ft_error_pipex(ac, av);
	tamp = ft_init_tamp(fd);
	// tamp = open("tamp", O_WRONLY | O_CREAT, 0777);
	dup2(tamp, 1);
	id[0] = fork();
	if (id[0] == 0)
		ft_apply_cmd1(av);
	else
	{
		waitpid(id[0], 0, 0);
		id[1] = fork();
		if (id[1] == 0)
			ft_apply_cmd2(av, fd, tamp);
		else 
		{
			waitpid(id[1], 0, 0);
			// ft_remove_file("tamp");
		}
	}
	// close(fd);
	// close(tamp);
} 