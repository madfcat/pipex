/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:18:14 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/03 18:29:33 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Locates the first occurrence of the null-terminated string needle in the
 * string haystack, where not more than len characters are searched.
 * Characters that appear after a `\0' character are not searched.
 * 
 * If needle is an empty string, haystack is returned; if needle occurs nowhere
 * in haystack, NULL is returned; otherwise a pointer to the first character of
 * the first occurrence of needle is returned.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_l;

	if (len == 0 && (!haystack || !needle))
		return ((void *)0);
	if (*needle == '\0')
		return ((char *)haystack);
	needle_l = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i < len)
	{
		if (len - i < needle_l)
			break ;
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0' )
			return ((char *)&haystack[i]);
		i++;
	}
	return ((void *)0);
}
