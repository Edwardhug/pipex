/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:46 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/23 12:08:16 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void ft_get_path(t_com *com, char **env)
{
	int	i;

	i = 0;
	com->path = NULL;
	while (!com->path)
	{
		com->path = ft_strncmp(env[i], "PATH=", 5);
		i++;
	}
	ft_printf("%s\n", com->path);
}

int	main(int ac, char **av, char **env)
{
	t_com com;

	if (ac != 5)
		return (ft_printf("Error\nWrong number of parameters\n"));
	(void) av;
	ft_get_path(&com, env);
}