/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:58:39 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/01 17:02:34 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_child_process(char **av, char **env, int i, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	ft_apply_exec(av[i], env);
}

void	ft_pipe_and_fork(char **av, char **env, int i)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		ft_child_process(av, env, i, fd);
	else
	{
		close(fd[1]);
		waitpid(pid, 0, 0);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	ft_loop(int ac, char **av, char **env, int i)
{
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

	if (ac != 5)
		return (ft_printf("Wrong number of parameters\n"), 1);
	fd_in = open(av[1], O_RDONLY);
	if (!fd_in)
		return (ft_printf("Unreadable infile\n"), 1);
	fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd_in, STDIN_FILENO);
	i = 2;
	ft_loop(ac, av, env, i);
	dup2(fd_out, STDOUT_FILENO);
	ft_apply_exec(av[ac - 2], env);
	return (0);
}
