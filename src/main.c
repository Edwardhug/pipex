/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:46 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/25 17:14:46 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_com	com;
	int		fd;

	if (ac != 5)
		return (ft_printf("Wrong number of parameters\n"), 1);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(fd);
	if (ft_parsing(av, env, &com))
		return (ft_printf("Error with parsing\n"), 1);
	if (ft_apply_cmd(&com, av, env))
		return (ft_printf("Error with apply\n"), 1);
	ft_free_t_com(&com);
	return (0);
}
