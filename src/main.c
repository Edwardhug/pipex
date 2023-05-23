/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:46 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/23 12:50:11 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_com com;

	if (ac != 5)
		return (ft_printf("Error\nWrong number of parameters\n"), 1);
	if (ft_parsing(ac, av, env, &com))
		return (ft_printf("Error\nError with parsing\n"), 1);
	ft_printf("%s\n", com.path);
}