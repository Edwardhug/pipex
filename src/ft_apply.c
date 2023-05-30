/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:54:50 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/30 11:30:42 by lgabet           ###   ########.fr       */
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
