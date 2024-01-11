/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:44:41 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/11 19:53:02 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H
# include <fcntl.h>
# include <string.h>
# include "libft/libft.h"

typedef struct s_store
{
	int		fd;
	char	**paths;
	int		pipe_fd[2];
	pid_t	pid;
	char	**cmd1;
	char	**cmd2;
	char	*shell_name;
	char	*executable;
	char	**exec_args;
	int		fd_out;
}	t_store;

int		ft_abs(int num);
void	real_join(char **string1, char *string2);
char	**split_command(char *cmd);
void	free_paths(char **paths);
char	**find_paths(char *envp[]);
char	*find_exec_path(char **paths, char *name);
char	*find_shell_name(char *envp[]);
void	print_error_msg(char *shell_name, int error_code, char *str);

#endif