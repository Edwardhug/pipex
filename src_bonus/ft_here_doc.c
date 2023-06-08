/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:42:42 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/08 12:03:07 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	check_here_doc(int ac, char **av, int *fd_out, int *i)
{
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		*fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
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
			return ;
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
