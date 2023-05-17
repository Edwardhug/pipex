/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:46 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/17 11:46:45 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av)
{
	int fd;

	if (ac != 5)
	{
		ft_printf("Error\nWrong number of argument\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nNo file1\n");
		close(fd);
		return (0);
	}
	close(fd);
}