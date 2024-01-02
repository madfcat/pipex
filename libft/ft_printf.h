/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:59:22 by vshchuki          #+#    #+#             */
/*   Updated: 2023/12/12 19:01:37 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

int	ft_handle_format(const char *format, va_list *ptr);
int	ft_printf(const char *str, ...);
int	ft_printf_logic(const char **str, va_list *ptr, int *count);

int	ft_putchar(char c, int fd);
int	ft_putstr(char *s, int fd);
int	ft_putnbr(int n, int fd);
int	ft_u_putnbr_fd(unsigned int nbr, int fd);

int	ft_format_string(va_list *ptr);
int	ft_format_number(va_list *ptr);
int	ft_format_u_number(va_list *ptr);
int	ft_format_pointer(va_list *ptr, int *count);

int	ft_find_oom_(long n);
int	ft_b10to16(unsigned long n, char *dict, int isnum, int *count);

#endif