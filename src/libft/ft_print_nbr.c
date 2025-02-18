/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex(unsigned long num, int uppercase)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (uppercase == 1)
		hex = "0123456789ABCDEF";
	if (num > 15)
		return (ft_putnbr_hex(num / 16, uppercase) + ft_putchr(hex[num % 16]));
	else
		return (ft_putchr(hex[num]));
}

int	ft_putptr(void *num)
{
	if (num == NULL)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x") + ft_putnbr_hex((unsigned long)num, 0));
}

int	ft_putunbr(unsigned int n)
{
	if (n > 9)
		return (ft_putunbr(n / 10) + ft_putchr(n % 10 + '0'));
	else
		return (ft_putchr(n + '0'));
}

int	ft_putnbr(int n)
{
	long	num;
	int		i;

	num = n;
	i = 0;
	if (num < 0)
	{
		i += ft_putchr('-');
		num *= -1;
	}
	if (num > 9)
	{
		i += ft_putnbr(num / 10);
		return (i + ft_putchr(num % 10 + '0'));
	}
	else
		return (i + ft_putchr(num + '0'));
}
