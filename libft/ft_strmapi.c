/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:11:46 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/03 18:26:24 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applies the function ’f’ to each character of the string ’s’, and passing
 * its index as first argument to create a new string (with malloc(3))
 * resulting from successive applications of ’f’.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;
	size_t	res_len;

	if (s && f)
	{
		res_len = ft_strlen(s);
		res = (char *)malloc((res_len + 1) * sizeof(char));
		if (!res)
			return ((char *)0);
		res[res_len] = '\0';
		i = 0;
		while (s[i])
		{
			res[i] = f(i, s[i]);
			i++;
		}
		return (res);
	}
	return ((char *)0);
}
