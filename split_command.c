/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:48:28 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/12 19:44:06 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static void	replace_spaces(unsigned int i, char *c)
{
	(void)i;
	if (is_space(c[0]))
		c[0] = ' ';
}

char	**split_command(char *cmd, char *shell_name)
{
	char	**command;

	ft_striteri(cmd, *replace_spaces);
	command = ft_split(cmd, ' ');
	allocation_check(command, shell_name);
	return (command);
}
