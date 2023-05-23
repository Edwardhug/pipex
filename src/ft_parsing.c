/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:42:48 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/23 12:49:27 by lgabet           ###   ########.fr       */
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

int	ft_parsing(int ac, char **av, char **env, t_com *com)
{
	(void) av;
	(void) ac;
	if (ft_get_path(com, env))
		return (ft_printf("Error\nError with ft_get_path\n"), 1);
	return (0);
}