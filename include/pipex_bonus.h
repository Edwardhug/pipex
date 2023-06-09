/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:46:55 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/09 17:31:07 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/all_libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

void	ft_apply_exec(char *cmd, char **env);
char	*ft_get_cmd(char **env, char **splited_cmd);
char	*ft_get_path_cmd(char **all_path, char **splited_cmd);
void	ft_here_doc(int ac, char **av);
void	check_here_doc(int ac, char **av, int *i);
int		open_fd_in(int *i, char **av);
int		open_fd_out(int ac, char **av);

#endif