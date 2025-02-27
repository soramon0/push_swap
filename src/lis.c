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

int	*lis_gen(int data[], size_t size)
{
	int		*lis;
	ssize_t	i;
	ssize_t	j;

	if (size == 0)
		return (NULL);
	lis = malloc(sizeof(int) * size);
	if (lis == NULL)
		return (NULL);
	i = 0;
	while (i < (ssize_t)size)
		lis[i++] = 1;
	i = size - 1;
	while (i >= 0)
	{
		j = size - 1;
		while (j > i)
		{
			if (data[i] < data[j] && lis[i] < lis[j] + 1)
				lis[i] = lis[j] + 1;
			j--;
		}
		i--;
	}
	return (lis);
}

static size_t	lis_max(int lis[], size_t size, size_t *pos)
{
	ssize_t	i;
	size_t	len;

	i = size - 1;
	len = 0;
	while (i >= 0)
	{
		if (lis[i] > (int)len)
		{
			len = lis[i];
			*pos = i;
		}
		i--;
	}
	return (len);
}

void	fill_lis_stack(t_stack *s, int data[], int lis[], size_t size)
{
	size_t	pos;
	size_t	i;
	size_t	j;

	i = 0;
	pos = 0;
	lis_max(lis, size, &pos);
	while (i < s->len)
	{
		s->data[i] = data[pos];
		j = pos + 1;
		while (j < size)
		{
			if (lis[j] == lis[pos] - 1 && data[j] > data[pos])
			{
				pos = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

t_stack	*lis_length(int data[], size_t size)
{
	t_stack	*s;
	int		*lis;
	size_t	pos;

	lis = lis_gen(data, size);
	if (lis == NULL)
		return (NULL);
	pos = 0;
	s = stack_init(lis_max(lis, size, &pos));
	if (s == NULL)
		return (free(lis), NULL);
	s->len = s->cap;
	fill_lis_stack(s, data, lis, size);
	free(lis);
	return (s);
}
