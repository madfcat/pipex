/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:45:28 by vshchuki          #+#    #+#             */
/*   Updated: 2023/11/23 15:50:29 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_format(const char *format, va_list *ptr)
{
	int		count;

	count = 0;
	if (*format == 'c')
		return (ft_putchar(va_arg(*ptr, int), 1));
	else if (*format == 's')
		return (ft_format_string(ptr));
	else if (*format == 'd' || *format == 'i')
		return (ft_format_number(ptr));
	else if (*format == 'u')
		return (ft_format_u_number(ptr));
	else if (*format == 'p')
		return (ft_format_pointer(ptr, &count));
	else if (*format == 'x')
		return (ft_b10to16(va_arg(*ptr, int), "0123456789abcdef", 1, &count));
	else if (*format == 'X')
		return (ft_b10to16(va_arg(*ptr, int), "0123456789ABCDEF", 1, &count));
	else if (*format == '%')
		return (ft_putchar(*format, 1));
	else
		return (-1);
	return (count);
}

int	ft_printf_logic(const char **str, va_list *ptr, int *count)
{
	int		result;

	if ((**str == '%' && *(*str + 1) != '\0') && ++(*str))
	{
		result = ft_handle_format(*str, ptr);
		if (result < 0)
			return (-1);
		*count += result;
	}
	else if (**str != '%' && (*(*str + 1) != '\0' || *(*str + 1) != '%'))
	{
		if (ft_putchar(**str, 1) < 0)
			return (-1);
		*count += 1;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		count;

	va_start(ptr, str);
	count = 0;
	while (*str)
	{
		if (ft_printf_logic(&str, &ptr, &count) < 0)
		{
			va_end(ptr);
			return (-1);
		}
		str++;
	}
	va_end(ptr);
	return (count);
}
