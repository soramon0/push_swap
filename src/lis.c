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

int	*save_seqs(int data[], size_t size)
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

static void	lis_cal_max(t_lis *lis)
{
	ssize_t	i;

	i = lis->seq_size - 1;
	lis->max = 0;
	while (i >= 0)
	{
		if (lis->seq_count[i] > lis->max)
		{
			lis->max = lis->seq_count[i];
			lis->max_pos = i;
		}
		i--;
	}
}

void	lis_to_stack(t_lis *lis, t_stack *s)
{
	int	pos;
	int	i;
	int	j;
	int	*count;

	count = lis->seq_count;
	pos = lis->max_pos;
	i = 0;
	while (i < lis->max)
	{
		s->data[i] = lis->seq[pos];
		j = pos + 1;
		while (j < lis->seq_size)
		{
			if (count[j] == count[pos] - 1 && lis->seq[j] > lis->seq[pos])
			{
				pos = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

t_stack	*create_lis_stack(t_stack *src)
{
	t_stack	*s;
	t_lis	*lis;

	lis = malloc(sizeof(t_lis));
	if (lis == NULL)
		return (NULL);
	lis->seq = src->data;
	lis->seq_size = src->len;
	lis->seq_count = save_seqs(src->data, src->len);
	lis_cal_max(lis);
	s = stack_init(lis->max);
	if (s == NULL)
		return (free(lis->seq_count), free(lis), NULL);
	s->len = s->cap;
	lis_to_stack(lis, s);
	free(lis->seq_count);
	free(lis);
	return (s);
}
