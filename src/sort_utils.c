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

void	bubble_sort_rev(t_stack *s)
{
	size_t	i;
	int		is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = 0;
		while (i < s->len - 1)
		{
			if (s->data[i] < s->data[i + 1])
			{
				swap_ints(s->data + (i + 1), s->data + i);
				is_sorted = 0;
			}
			i++;
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

int	stack_min_max(t_stack *s, int direction)
{
	size_t	i;
	int		val;

	i = 0;
	val = s->data[i++];
	while (i < s->len)
	{
		if (direction == 0 && s->data[i] < val)
			val = s->data[i];
		if (direction == 1 && s->data[i] > val)
			val = s->data[i];
		i++;
	}
	return (val);
}

int	stack_find_bg(t_stack *s)
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
