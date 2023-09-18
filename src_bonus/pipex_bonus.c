/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:45:39 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/18 11:55:49 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	close_fd(char **av, int fd_in, int fd_out)
{
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) != 0)
		close(fd_in);
	close(fd_out);
}

void	ft_child_process(char **av, char **env, int i, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_apply_exec(av[i], env);
	exit(EXIT_FAILURE);
}

void	ft_pipe_and_fork(char **av, char **env, int i)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (i == -1)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			exit(EXIT_FAILURE);
		}
		ft_child_process(av, env, i, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	ft_loop(int ac, char **av, char **env, int i)
{
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) != 0
		&& i == 3)
		ft_pipe_and_fork(av, env, -1);
	while (i < ac - 2)
	{
		ft_pipe_and_fork(av, env, i);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int			fd_in;
	int			fd_out;
	int			i;

	if (ac < 5)
		return (ft_printf("Wrong number of parameters\n"), 1);
	check_here_doc(ac, av, &i);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) != 0)
		fd_in = open_fd_in(&i, av);
	else
		fd_in = -1;
	ft_loop(ac, av, env, i);
	fd_out = open_fd_out(ac, av);
	if (fd_out > 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close (fd_out);
		ft_apply_exec(av[ac - 2], env);
	}
	close_fd(av, fd_in, fd_out);
}
