/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:40:17 by lgabet            #+#    #+#             */
/*   Updated: 2023/06/01 16:59:43 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/all_libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

void	ft_apply_exec(char *cmd, char **env);
char	*ft_get_cmd(char **env, char **splited_cmd);
char	*ft_get_path_cmd(char **all_path, char **splited_cmd);

#endif