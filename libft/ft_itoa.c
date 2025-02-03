/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_zerocase(void)
{
	char	*ret;

	ret = malloc(sizeof(char) * 2);
	if (ret == NULL)
		return (NULL);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

static size_t	ft_get_nbr_size(long num)
{
	size_t	i;

	i = 0;
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	num;
	size_t	i;

	if (n == 0)
		return (ft_zerocase());
	num = n;
	i = ft_get_nbr_size(num);
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	ret[i] = '\0';
	if (num < 0)
	{
		ret[0] = '-';
		num *= -1;
	}
	while (num)
	{
		ret[--i] = (num % 10) + '0';
		num /= 10;
	}
	return (ret);
}
