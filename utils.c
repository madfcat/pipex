/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:22:47 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/12 18:56:42 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	real_join(char **string1, char *string2, char *shell_name)
{
	char	*temp;

	temp = *string1;
	*string1 = ft_strjoin(temp, string2);
	allocation_check(string2, shell_name);
	free(temp);
}

int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

void	allocation_check(void *ptr, char *shell_name)
{
	if (ptr == NULL)
	{
		print_error_msg(shell_name, 12, "");
		exit(EXIT_FAILURE);
	}
}
