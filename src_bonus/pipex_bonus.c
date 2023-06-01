/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:45:39 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/01 16:19:33 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_child_process(t_struct param, int i, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	ft_apply_exec(param.av[i], param.env);
}

void	ft_pipe_and_fork(t_struct param, int i)
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0)
		ft_child_process(param, i, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	ft_loop(t_struct param, int i)
{
	while (i < param.ac - 2)
	{
		ft_pipe_and_fork(param, i);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	// t_struct	param;
	int			fd_in;
	int			fd_out;
	int			i;

	// param.ac = ac;
	// param.av = av;
	// param.env = env;
	if (ac < 5)
		return (ft_printf("Wrong number of parameters\n"), 1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		ft_here_doc(ac, av);
		i = 3;
	}
	else
	{
		fd_in = open(av[1], O_RDONLY);
		if (!fd_in)
			return (ft_printf("Unreadable infile\n"), 1);
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd_in, STDIN_FILENO);
		i = 2;
	}
	ft_loop(ac, av, env, i);
	dup2(fd_out, STDOUT_FILENO);
	ft_apply_exec(av[ac - 2], env);
	return (0);
}
