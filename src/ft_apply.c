/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:54:50 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/24 11:40:06 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_apply_cmd_1(t_com *com, char **av, char **env)
{
	char	*exe_arg[3];

	close(com->fd[0]);
	ft_printf("com->fd[1] = %d\n", com->fd[1]);
	ft_printf("dup2 = %d\n", dup2(com->fd[1], 1));
	// ft_printf("salut\n");
	exe_arg[0] = com->path_cmd1;
	exe_arg[1] = av[1];
	exe_arg[2] = NULL;
	execve(exe_arg[0], exe_arg, env);
	return (0);
}

int	ft_apply_cmd(t_com *com, char **av, char **env)
{
	char	tamp[200];
	int		id;

	// tamp = NULL;
	if (pipe(com->fd))
		return (ft_printf("Error with pipe\n"), 1);
	id = fork();
	if (id == 0)
	{
		// ft_printf("salut\n");
		ft_apply_cmd_1(com, av, env);
	}
	else
	{
		// close(com->fd[1]);
		waitpid(id, 0, 0);
		ft_printf("size read = %d\n", read(com->fd[0], tamp, 200));
		ft_printf("read from pipe: %s\n", tamp);
	}
	return (0);
}