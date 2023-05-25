/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:54:50 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/25 12:56:44 by lgabet           ###   ########.fr       */
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

int	ft_setup_last_cmd(t_com *com, char **av, char **env)
{
	int	id;

	id = fork();
	if (id == 0)
		ft_apply_last_cmd(com, av, env);
	else
		waitpid(id, 0, 0);
	return (0);
}

int	ft_apply_cmd(t_com *com, char **av, char **env)
{
	int		id;

	if (pipe(com->fd))
		return (ft_printf("Error with pipe apply\n"), 1);
	id = fork();
	if (id == 0)
		ft_apply_cmd_1(com, av, env);
	else
	{
		close(com->fd[1]);
		waitpid(id, 0, 0);
		ft_setup_last_cmd(com, av, env);
	}
	return (0);
}
