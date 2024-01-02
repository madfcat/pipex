/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:19:31 by vshchuki          #+#    #+#             */
/*   Updated: 2023/11/10 14:02:24 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr(char *s, int fd)
{
	size_t	len;
	int		res;

	res = -1;
	if (s)
	{
		len = ft_strlen(s);
		res = write(fd, s, len);
	}
	return (res);
}

int	ft_putnbr(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		if (ft_putchar('-', fd) < 0)
			return (-1);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		if (ft_putnbr(nbr / 10, fd) < 0)
			return (-1);
		if (ft_putnbr(nbr % 10, fd) < 0)
			return (-1);
	}
	else
		if (ft_putchar(nbr + '0', fd) < 0)
			return (-1);
	return (0);
}

int	ft_u_putnbr_fd(unsigned int nbr, int fd)
{
	if (nbr > 9)
	{
		if (ft_u_putnbr_fd(nbr / 10, fd) < 0)
			return (-1);
		if (ft_u_putnbr_fd(nbr % 10, fd) < 0)
			return (-1);
	}
	else
	{
		if (ft_putchar(nbr + '0', fd) < 0)
			return (-1);
	}
	return (0);
}
