/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	process(va_list args, char **format, char specifier)
{
	int	bytes;

	bytes = 0;
	if (specifier == '%')
		bytes = ft_putchr('%');
	else if (specifier == 'c')
		bytes = ft_putchr(va_arg(args, int));
	else if (specifier == 's')
		bytes = ft_putstr(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		bytes = ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
		bytes = ft_putunbr(va_arg(args, int));
	else if (specifier == 'x' || specifier == 'X')
		bytes = ft_putnbr_hex(va_arg(args, unsigned int), specifier == 'X');
	else if (specifier == 'p')
		bytes = ft_putptr(va_arg(args, void *));
	*format += 2;
	return (bytes);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		bytes;
	char	*specifier;
	char	*s;

	if (!format)
		return (-1);
	bytes = 0;
	s = (char *)format;
	va_start(args, format);
	while (*s)
	{
		if (*s != '%' && ++bytes)
		{
			write(1, s++, 1);
			continue ;
		}
		specifier = ft_strchr("cspdiuxX%", *(s + 1));
		if (!specifier && ++bytes && ++s)
			write(1, "%", 1);
		else
			bytes += process(args, &s, *specifier);
	}
	va_end(args);
	return (bytes);
}

int	ft_vprintf(va_list args, const char *format, ...)
{
	int		bytes;
	char	*specifier;
	char	*s;

	if (!format)
		return (-1);
	bytes = 0;
	s = (char *)format;
	while (*s)
	{
		if (*s != '%' && ++bytes)
		{
			write(1, s++, 1);
			continue ;
		}
		specifier = ft_strchr("cspdiuxX%", *(s + 1));
		if (!specifier && ++bytes && ++s)
			write(1, "%", 1);
		else
			bytes += process(args, &s, *specifier);
	}
	return (bytes);
}
