/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	bubble_sort(t_stack *s)
{
	ssize_t	i;
	int		is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = s->len - 1;
		while (i >= 1)
		{
			if (s->data[i] > s->data[i - 1])
			{
				swap_ints(s->data + i, s->data + (i - 1));
				is_sorted = 0;
			}
			i--;
		}
	}
}

ssize_t	stack_equal(t_stack *a, t_stack *b)
{
	size_t	i;

	if (a->len != b->len)
		return (-1);
	i = 0;
	while (i < a->len)
	{
		if (a->data[i] != b->data[i])
			return (-1);
		i++;
	}
	return (0);
}

int	stack_find_sm(t_stack *s)
{
	size_t	i;
	int		sm;

	i = 0;
	sm = s->data[i++];
	while (i < s->len)
	{
		if (s->data[i] < sm)
			sm = s->data[i];
		i++;
	}
	return (sm);
}

ssize_t	find_insert_pos(t_stack *pivot, t_stack *haystack, int needle)
{
	ssize_t	index;
	ssize_t	needle_index;
	int		target;

	if (stack_push(pivot, needle) != 0)
		return (-1);
	bubble_sort(pivot);
	index = stack_find_index(pivot, needle);
	needle_index = index;
	if (index == 0)
		index = pivot->len - 1;
	else
		index--;
	target = pivot->data[index];
	index = stack_find_index(haystack, target);
	if (index == -1)
		return (-1);
	pivot->data[needle_index] = pivot->data[--pivot->len];
	return (haystack->len - 1 - index);
}
