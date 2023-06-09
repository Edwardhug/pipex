/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:42:42 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/09 17:36:36 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	check_here_doc(int ac, char **av, int *i)
{
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		ft_here_doc(ac, av);
		*i = 3;
	}
}

void	ft_child_here_doc(char **av, int *fd)
{
	char	*tmp;

	close(fd[0]);
	while (1)
	{
		ft_printf("heredoc> ");
		tmp = get_next_line(0);
		if (ft_strncmp(tmp, av[2], ft_strlen(av[2])) == 0)
		{
			free(tmp);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(tmp, fd[1]);
		free(tmp);
	}
}

void	ft_here_doc(int ac, char **av)
{
	int	fd[2];
	int	pid;

	if (ac < 6)
	{
		ft_putstr_fd("Wrong number of parameters\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		ft_child_here_doc(av, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	open_fd_in(int *i, char **av)
{
	int	fd_in;

	*i = 2;
	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
	{
		*i = 3;
		perror(av[1]);
	}
	else
		dup2(fd_in, STDIN_FILENO);
	if (fd_in != -1)
		close (fd_in);
	return (fd_in);
}

int	open_fd_out(int ac, char **av)
{
	int	fd_out;

	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		perror(av[ac - 1]);
	return (fd_out);
}
