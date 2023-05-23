/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:40:17 by lgabet            #+#    #+#             */
/*   Updated: 2023/05/23 14:22:20 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/all_libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct	s_com
{
	char	*path;
	char	**all_path;
	int		fd_infile;
	char	*infile;
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;
}				t_com;

int 	ft_get_path(t_com *com, char **env);
int		ft_parsing(char **av, char **env, t_com *com);
void	ft_free_tab(char **str);

#endif