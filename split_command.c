/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:48:28 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/09 19:46:05 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	is_space(char c) {
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static void replace_spaces(unsigned int i, char *c)
{
	(void)i;
	// if (is_space(c[0]) || c[0] == '"' || c[0] == 39)
	if (is_space(c[0]))
		c[0] = ' ';
}

/* static void replace_instring_spaces(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || )
	}
} */

char	**split_command(char *cmd)
{
	char	**command;
	ft_striteri(cmd, *replace_spaces);
	command = ft_split(cmd, ' ');
	// printf("%s, %ld\n", command[0], ft_strlen(command[0]));
	// printf("%s, %ld\n", command[1], ft_strlen(command[1]));
	// printf("%s\n", command[2]);
	return (command);
}

// int main(void)
// {
// 	ft_printf("%d", (access("/usr/local/munki/-l", F_OK)));
// 	return (0);
// }
// int main(void)
// {
// 	char str[] = "ls 				-l";
// 	ft_printf("%s\n", str);
// 	// ft_striteri(str, *replace_spaces);
// 	// ft_printf("%s\n", str);
// 	split_command(str);
// 	return (0);
// }