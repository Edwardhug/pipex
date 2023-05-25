/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:38:46 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/25 11:26:53 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_remove_file(char *file, char	**env)
{
	int		id;
	char	**exec_arg;

	id = fork();
	if (id == 0)
	{
		exec_arg = malloc(sizeof(char *) * 3);
		if (!exec_arg)
			exit(EXIT_FAILURE);
		exec_arg[0] = malloc(sizeof(char) * (ft_strlen("/usr/bin/rm")));
		if (!exec_arg[0])
		{
			free(exec_arg);
			exit(EXIT_FAILURE);
		}
		exec_arg[0] = ft_strdup("/usr/bin/rm");
		exec_arg[1] = file;
		exec_arg[2] = NULL;
		execve(exec_arg[0], exec_arg, env);
	}
	else
		waitpid(id, 0, 0);
}

int	main(int ac, char **av, char **env)
{
	t_com com;

	if (ac != 5)
		return (ft_printf("Wrong number of parameters\n"), 1);
	ft_remove_file(av[4], env);
	if (ft_parsing(av, env, &com))
		return (ft_printf("Error with parsing\n"), 1);
	if (ft_apply_cmd(&com, av, env))
		return (ft_printf("Error with apply\n"), 1);
	ft_free_t_com(&com);
	return (0);
}