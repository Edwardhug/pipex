/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:23:36 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/26 14:11:15 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*ft_get_path_cmd(char **all_path, char **splited_cmd)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	if (splited_cmd[0][0] == '/')
	{
		path_cmd = splited_cmd[0];
		if (access(path_cmd, F_OK | X_OK) == -1)
			return (free(path_cmd), NULL);
		return (path_cmd);
	}
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		path_cmd = ft_strjoin(tmp, splited_cmd[0]);
		if (access(path_cmd, F_OK | X_OK) != -1)
			return (free(tmp), path_cmd);
		free(path_cmd);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*ft_get_cmd(char **env, char **splited_cmd)
{
	int		i;
	char	*path;
	char	**all_path;

	i = 0;
	path = NULL;
	while (!path)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i];
		i++;
	}
	path = path + 5;
	all_path = ft_split(path, ':');
	if (!all_path)
		return (NULL);
	return (ft_get_path_cmd(all_path, splited_cmd));
}

void	ft_apply_exec(char *cmd, char **env)
{
	char	*path_cmd;
	char	**splited_cmd;

	splited_cmd = ft_split(cmd, ' ');
	if (!splited_cmd)
		exit(ft_printf("malloc error splited_cmd\n", EXIT_FAILURE));
	path_cmd = ft_get_cmd(env, splited_cmd);
	if (!path_cmd)
		exit(ft_printf("malloc error path_cmd\n", EXIT_FAILURE));
	execve(path_cmd, splited_cmd, env);
}