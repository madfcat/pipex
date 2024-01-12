/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:41:42 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/12 18:57:57 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*find_shell_name(char *envp[])
{
	char	*line;
	char	*shell_name;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		line = ft_strnstr(envp[i], "SHELL=", ft_strlen(envp[i]));
		if (line)
		{
			shell_name = ft_strrchr(envp[i], '/') + 1;
			return (shell_name);
		}
		i++;
	}
	return (NULL);
}

void	handle_zsh_error_msg(char *sh_name, char *err, char **final, char *str)
{
	int	i;

	i = 0;
	while (err[i])
	{
		err[i] = ft_tolower(err[i]);
		i++;
	}
	*final = ft_strjoin(sh_name, ": ");
	allocation_check(*final, sh_name);
	real_join(final, err, sh_name);
	if (str != NULL && str[0] != '\0')
	{
		real_join(final, ": ", sh_name);
		real_join(final, str, sh_name);
	}
	real_join(final, "\n", sh_name);
}

void	handle_sh_error_msg(char *sh_name, char *err, char **final, char *str)
{
	*final = ft_strdup(sh_name);
	allocation_check(*final, sh_name);
	if (str != NULL && str[0] != '\0')
	{
		real_join(final, ": ", sh_name);
		real_join(final, str, sh_name);
	}
	real_join(final, ": ", sh_name);
	real_join(final, err, sh_name);
	real_join(final, "\n", sh_name);
}

/**
 * str can be a filename for No such file or directory error
 */
void	print_error_msg(char *shell_name, int error_code, char *str)
{
	char	*error_msg;
	char	*final_msg;

	final_msg = NULL;
	if (error_code == 22)
	{
		error_msg = ft_strdup("command not found");
		allocation_check(error_msg, shell_name);
	}
	else
		error_msg = ft_strdup(strerror(error_code));
	if (ft_strncmp(shell_name, "zsh", ft_strlen(shell_name)) == 0)
		handle_zsh_error_msg(shell_name, error_msg, &final_msg, str);
	else
		handle_sh_error_msg(shell_name, error_msg, &final_msg, str);
	ft_putstr_fd(final_msg, 2);
	free(error_msg);
	free(final_msg);
	if (error_code == 22)
		exit(127);
}
