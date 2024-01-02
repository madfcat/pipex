/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:23:40 by vshchuki          #+#    #+#             */
/*   Updated: 2023/12/12 19:01:39 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_find_oom_(long n)
{
	int		oom;

	oom = 0;
	if (n < 0)
		n = -n;
	while (n > 9)
	{
		n /= 10;
		oom++;
	}
	return (oom);
}

int	ft_b10to16(unsigned long n, char *dict, int isnum, int *count)
{
	unsigned long	num;

	num = n;
	if (isnum)
		num = (unsigned int)n;
	if (num < 16)
	{
		*count = *count + 1;
		if (ft_putchar(dict[num], 1) < 0)
			return (-1);
	}
	else
	{
		if (ft_b10to16(num / 16, dict, isnum, count) < 0)
			return (-1);
		if (ft_b10to16(num % 16, dict, isnum, count) < 0)
			return (-1);
	}
	return (*count);
}
