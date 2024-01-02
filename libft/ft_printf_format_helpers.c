/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:22:09 by vshchuki          #+#    #+#             */
/*   Updated: 2023/12/12 19:01:53 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_null_string(char	*string, int len)
{
	string = ft_strdup("(null)");
	if (ft_putstr(string, 1) < 0)
	{
		free(string);
		return (-1);
	}
	len = ft_strlen(string);
	free(string);
	return (len);
}

int	ft_format_string(va_list *ptr)
{
	char	*string;
	int		len;

	len = 0;
	string = va_arg(*ptr, char *);
	if (!string)
	{
		return (ft_null_string(string, len));
	}
	else if (!string[0])
		return (len);
	else
		string = ft_strdup(string);
	if (ft_putstr(string, 1) < 0)
	{
		free(string);
		return (-1);
	}
	if (string)
		len = ft_strlen(string);
	free(string);
	return (len);
}

int	ft_format_number(va_list *ptr)
{
	int		number;
	int		sign;

	sign = 0;
	number = va_arg(*ptr, int);
	if (number < 0)
		sign = 1;
	if (ft_putnbr(number, 1) < 0)
		return (-1);
	return (ft_find_oom_(number) + 1 + sign);
}

int	ft_format_u_number(va_list *ptr)
{
	unsigned int	number;

	number = va_arg(*ptr, unsigned int);
	if (ft_u_putnbr_fd(number, 1) < 0)
		return (-1);
	return (ft_find_oom_(number) + 1);
}

int	ft_format_pointer(va_list *ptr, int *count)
{
	unsigned long	n;

	n = va_arg(*ptr, unsigned long);
	if (ft_putstr("0x", 1) < 0)
		return (-1);
	*count += 2;
	return (ft_b10to16(n, "0123456789abcdef", 0, count));
}
