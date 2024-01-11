/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:22:47 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/11 19:50:18 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	real_join(char **string1, char *string2)
{
	char	*temp;

	temp = *string1;
	*string1 = ft_strjoin(temp, string2);
	free(temp);
}

int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}
