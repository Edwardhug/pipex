/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:48:17 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/25 11:34:43 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_cmd(t_com *com)
{
	int	i;

	i = 0;
	while (com->cmd1[i])
	{
		free(com->cmd1[i]);
		i++;
	}
	free(com->cmd1);
	i = 0;
	while (com->cmd2[i])
	{
		free(com->cmd2[i]);
		i++;
	}
	free(com->cmd2);
}

void	ft_free_t_com(t_com *com)
{
	int	i;

	i = 0;
	while (com->all_path[i])
	{
		free(com->all_path[i]);
		i++;
	}
	free(com->all_path);
	ft_free_cmd(com);
	free(com->path_cmd1);
	free(com->path_cmd2);
}