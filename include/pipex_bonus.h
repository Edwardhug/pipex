/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:46:55 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/01 16:59:15 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/all_libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

void	ft_apply_exec(char *cmd, char **env);
char	*ft_get_cmd(char **env, char **splited_cmd);
char	*ft_get_path_cmd(char **all_path, char **splited_cmd);
void	ft_here_doc(int ac, char **av);

#endif