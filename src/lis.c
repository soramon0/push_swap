/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max(int num1, int num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

int	*init_lis(size_t size)
{
	int		*lis;
	size_t	i;

	if (size == 0)
		return (NULL);
	lis = malloc(sizeof(int) * size);
	if (lis == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		lis[i++] = 1;
	return (lis);
}

ssize_t	lis_max(int lis[], size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (i < size)
		len = max(lis[i++], len);
	return (len);
}

ssize_t	lis_length(int data[], size_t size)
{
	int		*lis;
	ssize_t	len;
	size_t	i;
	size_t	j;

	lis = init_lis(size);
	if (lis == NULL)
		return (-1);
	len = 1;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < i)
		{
			if (data[i] > data[j])
				lis[i] = max(lis[i], lis[j] + 1);
			j++;
		}
		i++;
	}
	len = lis_max(lis, size);
	free(lis);
	return (len);
}
