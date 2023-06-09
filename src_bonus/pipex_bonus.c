/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:45:39 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/09 17:11:03 by lgabet           ###   ########.fr       */
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
	check_here_doc(ac, av, &fd_out, &i);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) != 0)
	{
		fd_in = open_fd_in(&i, av);
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			perror(av[ac - 1]);
	}
	ft_loop(ac, av, env, i);
	if (fd_out > 0)
	{
		close(fd_out);
		dup2(fd_out, STDOUT_FILENO);
		ft_apply_exec(av[ac - 2], env);
	}
	close_fd(av, fd_in, fd_out);
}
