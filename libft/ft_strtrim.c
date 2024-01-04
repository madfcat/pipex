/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:44:41 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/04 16:04:18 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count_rem_start(char const *s1, char const *set)
{
	int	i;	

	i = 0;
	while (s1[i])
	{
		if (ft_isinset(s1[i], set))
			i++;
		else
			break ;
	}
	return (i);
}

static int	ft_count_rem_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i)
	{
		if (ft_isinset(s1[i], set))
			i--;
		else
			break ;
	}
	i++;
	return (i);
}
/**
 * Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
 * specified in ’set’ removed from the beginning and the end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_rem_len;
	size_t	end_rem_len;
	size_t	len;
	char	*new_s1;

	if (s1 && set)
	{
		len = ft_strlen(s1);
		start_rem_len = ft_count_rem_start(s1, set);
		end_rem_len = len - ft_count_rem_end(s1, set);
		len = len - start_rem_len - end_rem_len;
		new_s1 = ft_substr(s1, start_rem_len, len);
		return (new_s1);
	}
	return ((char *)0);
}
