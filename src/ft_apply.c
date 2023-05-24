/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:54:50 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/24 14:08:54 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

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

char	*ft_read_pipex(int fd)
{
	char	*tamp;
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (ft_printf("Error with malloc ft_read 1\n"), NULL);
	str[0] = 0;
	tamp = get_next_line(fd);
	while (1)
	{
		str = ft_strjoin(str, tamp);
		tamp = get_next_line(fd);
		if (!str)
			return (ft_printf("Error with malloc ft_read 2\n"), NULL);
		if (!tamp)
			break ;
	}
	return (str);
		
}

int	ft_apply_cmd(t_com *com, char **av, char **env)
{
	char	*tamp;
	int		id;

	if (pipe(com->fd))
		return (ft_printf("Error with pipe\n"), 1);
	id = fork();
	if (id == 0)
		ft_apply_cmd_1(com, av, env);
	else
	{
		close(com->fd[1]);
		waitpid(id, 0, 0);
		// ft_printf("read = %d\n", read(com->fd[0], 0, 0));
		tamp = ft_read_pipex(com->fd[0]);
		if (!tamp)
			return (ft_printf("Error with tamp ft_apply_cmd\n"), 1);
		ft_printf("%s\n", tamp);
	}
	return (0);
}