/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:28:20 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/09 17:33:40 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/all_libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

void	ft_apply_exec(char *cmd, char **env);
char	*ft_get_cmd(char **env, char **splited_cmd);
char	*ft_get_path_cmd(char **all_path, char **splited_cmd);
int		open_fd_in(int *i, char **av);
int		open_fd_out(int ac, char **av);

#endif