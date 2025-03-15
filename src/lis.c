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

static int	*count_seq(int data[], size_t size)
{
	int		*lis;
	size_t	i;
	size_t	j;

	if (size == 0)
		return (NULL);
	lis = malloc(sizeof(int) * size);
	if (lis == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		lis[i++] = 1;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < i)
		{
			if (data[j] > data[i] && lis[i] < lis[j] + 1)
				lis[i] = lis[j] + 1;
			j++;
		}
		i++;
	}
	return (lis);
}

static void	save_lis_length(t_lis *lis)
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

static void	move_lis(t_lis *lis, t_stack *s)
{
	int	pos;
	int	i;
	int	j;
	int	*count;
	int	stack_pos;

	count = lis->seq_count;
	pos = lis->max_pos;
	stack_pos = s->len - 1;
	i = 0;
	while (i < lis->max)
	{
		s->data[stack_pos--] = lis->seq[pos];
		j = pos - 1;
		while (j >= 0)
		{
			if (count[j] == count[pos] - 1 && lis->seq[j] > lis->seq[pos])
			{
				pos = j;
				break ;
			}
			j--;
		}
		i++;
	}
}

t_stack	*create_lis_stack(t_stack *src)
{
	t_stack	*s;
	t_lis	*lis;

	if (src == NULL)
		return (NULL);
	lis = malloc(sizeof(t_lis));
	if (lis == NULL)
		return (NULL);
	lis->seq = src->data;
	lis->seq_size = src->len;
	lis->seq_count = count_seq(src->data, src->len);
	if (lis->seq_count == NULL)
		return (free(lis), NULL);
	save_lis_length(lis);
	s = stack_init(lis->max);
	if (s == NULL)
		return (free(lis->seq_count), free(lis), NULL);
	s->len = s->cap;
	move_lis(lis, s);
	return (free(lis->seq_count), free(lis), s);
}

t_stack	*get_best_lis(t_swapable *area)
{
	t_stack	*lis;
	size_t	best;
	size_t	index;
	ssize_t	rotation;

	best = 0;
	index = -1;
	while (++index < area->a->len)
	{
		lis = create_lis_stack(area->a);
		if (lis == NULL)
			return (NULL);
		if (lis->len > best)
		{
			rotation = index;
			best = lis->len;
		}
		stack_do_op(area, OP_RA, 0);
		stack_free(lis);
	}
	while (index--)
		stack_do_op(area, OP_RRA, 0);
	while (rotation--)
		stack_do_op(area, OP_RA, 1);
	return (create_lis_stack(area->a));
}
