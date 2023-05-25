/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:42:48 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/25 12:00:07 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int ft_get_path(t_com *com, char **env)
{
	int	i;

	i = 0;
	com->path = NULL;
	while (!com->path)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			com->path = env[i];
		i++;
	}
	com->path = com->path + 5;
	com->all_path = ft_split(com->path, ':');
	if (!com->all_path)
		return (1);
	return (0);
}

int	ft_get_command(t_com *com, char **av)
{
	com->cmd1 = ft_split(av[2], ' ');
	if (!com->cmd1)
		return (ft_printf("Split command1\n"), 1);
	com->cmd2 = ft_split(av[3], ' ');
	if (!com->cmd2)
	{
		ft_free_tab(com->cmd1);
		return (ft_printf("Split command1\n"), 1);
	}
	return (0);
}

int	ft_check_command1(t_com *com)
{
	int		i;
	char	*tmp;

	i = 0;
	if (com->cmd1[0][0] == '/')
	{
		com->path_cmd1 = com->cmd1[0];
		if (access(com->path_cmd1, F_OK | X_OK) == -1)
			return (free(com->path_cmd1), 1);
		return (0);
	}
	while (com->all_path[i])
	{
		tmp = ft_strjoin(com->all_path[i], "/");
		com->path_cmd1 = ft_strjoin(tmp, com->cmd1[0]);
		if (access(com->path_cmd1, F_OK | X_OK) != -1)
			return (free(tmp), 0);
		free(com->path_cmd1);
		free(tmp);
		i++;
	}
	return (1);
}

int	ft_check_command2(t_com *com)
{
	int		i;
	char	*tmp;

	i = 0;
	if (com->cmd2[0][0] == '/')
	{
		com->path_cmd2 = com->cmd2[0];
		if (access(com->path_cmd2, F_OK | X_OK) == -1)
			return (free(com->path_cmd2), 1);
		return (0);
	}
	while (com->all_path[i])
	{
		tmp = ft_strjoin(com->all_path[i], "/");
		com->path_cmd2 = ft_strjoin(tmp, com->cmd2[0]);
		if (access(com->path_cmd2, F_OK | X_OK) != -1)
			return (free(tmp), 0);
		free(com->path_cmd2);
		free(tmp);
		i++;
	}
	return (1);
}

int	ft_parsing(char **av, char **env, t_com *com)
{
	if (ft_get_path(com, env))
		return (ft_printf("Error with ft_get_path\n"), 1);
	com->fd_infile = open(av[1], O_RDONLY);
	if (com->fd_infile == -1)
	{
		ft_free_tab(com->all_path);
		return (ft_printf("Unreadable infile\n"), 1);
	}
	if (ft_get_command(com, av))
		return (ft_printf("Error getting command 1\n"), 1);
	if (ft_check_command1(com))
		return (ft_printf("Command1 doesn't exist\n"), 1);
	if (ft_check_command2(com))
		return (ft_printf("Command2 doesn't exist\n"), 1);
	return (0);
}