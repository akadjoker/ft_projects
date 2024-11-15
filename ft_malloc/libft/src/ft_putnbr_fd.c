/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoker <djoker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:17:52 by lrosa-do          #+#    #+#             */
/*   Updated: 2024/11/15 10:04:46 by djoker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	else
		ft_putchar_fd((n + '0'), fd);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}


void ft_putnbr_base(size_t nbr, char *base, int base_len)
{
	if (nbr >= (size_t)base_len)
	{
		ft_putnbr_base(nbr / base_len, base, base_len);
		ft_putnbr_base(nbr % base_len, base, base_len);
	}
	else
	{
		ft_putchar(base[nbr]);
	}
}

void ft_putaddr(void *ptr)
{
	ft_putstr("0x");
	ft_putnbr_base((size_t)ptr, "0123456789ABCDEF", 16);
}

