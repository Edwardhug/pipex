/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:54:50 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/23 16:11:06 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_apply_cmd_1(t_com *com, char **av, char **env)
{
	char	*exe_arg[3];

	close(com->fd[0]);
	dup2(com->fd[1], 1);
	ft_printf("salut\n");
	exe_arg[0] = com->path_cmd1;
	// ft_printf("%s\n", exe_arg[0]);
	exe_arg[1] = av[1];
	exe_arg[2] = NULL;
	// ft_printf("salut\n");
	execve(exe_arg[0], exe_arg, env);
	return (0);
}

int	ft_apply_cmd(t_com *com, char **av, char **env)
{
	int	tamp;
	int	id;
	char	*str;

	str = NULL;
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
		close(com->fd[1]);
		// waitpid(id, 0, 0);
		// read(com->fd[0], tamp, 30);
		tamp = com->fd[0];
		read(tamp, str, 30);
		ft_printf("read from pipe: %s\n", str);
	}
	return (0);
}