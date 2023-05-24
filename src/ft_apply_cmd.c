/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:10:26 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/24 15:45:23 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_apply_cmd_1(t_com *com, char **av, char **env)
{
	char	**exe_arg;
	int		i;

	close(com->fd[0]);
	exe_arg = malloc(sizeof(char *) * (ft_strlen_tab(com->cmd1) + 2));
	if (!exe_arg)
		return (ft_printf("Error malloc exe_arg\n"), 1);
	exe_arg[0] = com->path_cmd1;
	i = 1;
	while (com->cmd1[i])
	{
		exe_arg[i] = com->cmd1[i];
		i++;
	}
	exe_arg[i] = av[1];
	i++;
	exe_arg[i] = NULL;
	dup2(com->fd[1], 1);
	execve(exe_arg[0], exe_arg, env);
	return (0);
}

int	ft_apply_last_cmd(t_com *com, char **av, char **env)
{
	char	**exe_arg;
	int		i;
	int		fd;

	fd = open(av[4], O_WRONLY | O_CREAT, 0777);
	exe_arg = malloc(sizeof(char *) * (ft_strlen_tab(com->cmd2) + 2));
	if (!exe_arg)
		return (ft_printf("Error malloc exe_arg\n"), 1);
	exe_arg[0] = com->path_cmd2;
	i = 1;
	while (com->cmd2[i])
	{
		exe_arg[i] = com->cmd2[i];
		i++;
	}
	exe_arg[i] = com->fd[0];		// ?
	i++;
	exe_arg[i] = NULL;
	dup2(fd, 1);
	execve(exe_arg[0], exe_arg, env);
	return (0);
}
