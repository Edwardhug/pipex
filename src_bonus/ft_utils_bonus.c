/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:56:17 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/12 16:50:20 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

void	print_error(char **splited_cmd, char **all_path, int i)
{
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	else
		ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(splited_cmd[0], 2);
	ft_putstr_fd("\n", 2);
	ft_free_tab(splited_cmd);
	ft_free_tab(all_path);
}

char	*ft_get_path_cmd(char **all_path, char **splited)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	if (splited[0][0] == '/')
	{
		path_cmd = ft_strdup(splited[0]);
		if (access(path_cmd, F_OK | X_OK) == -1)
			return (print_error(splited, all_path, 0), free(path_cmd), NULL);
		return (ft_free_tab(all_path), path_cmd);
	}
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		path_cmd = ft_strjoin(tmp, splited[0]);
		if (access(path_cmd, F_OK | X_OK) != -1)
			return (free(tmp), path_cmd);
		free(path_cmd);
		free(tmp);
		i++;
	}
	print_error(splited, all_path, 0);
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
	if (!splited_cmd || !splited_cmd[0])
	{
		if (!splited_cmd[0])
			free(splited_cmd);
		ft_putstr_fd("permission denied:\n", 2);
		exit(EXIT_FAILURE);
	}
	path_cmd = ft_get_cmd(env, splited_cmd);
	if (!path_cmd)
		exit(EXIT_FAILURE);
	execve(path_cmd, splited_cmd, env);
	ft_putstr_fd("permission denied: ", 2);
	ft_putstr_fd(path_cmd, 2);
	ft_putstr_fd("\n", 2);
	ft_free_tab(splited_cmd);
	free(path_cmd);
	exit(EXIT_FAILURE);
}
