/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*add_none_lis_sorted(t_stack *lis, t_stack *src)
{
	t_stack	*s;
	size_t	i;
	size_t	diff;

	if (lis == NULL)
		return (NULL);
	diff = src->len - lis->len;
	s = stack_init(diff);
	if (s == NULL)
		return (NULL);
	i = src->len - 1;
	while (diff > 0)
	{
		if (stack_find_index(lis, src->data[i]) == -1)
		{
			if (stack_push(s, src->data[i]) != 0)
				return (stack_free(s), NULL);
			diff--;
			i--;
		}
		else
			i--;
	}
	bubble_sort(s);
	return (s);
}

size_t	best_bound(size_t len)
{
	ssize_t	bound;

	if (len <= 50)
		bound = len;
	else if (len <= 100)
		bound = len / 4;
	else
		bound = len / 8;
	return (bound);
}

ssize_t	move_chunk(t_swapable *area, ssize_t end, int needle)
{
	ssize_t	r;

	if (needle <= area->c->data[end])
	{
		r = stack_do_op(area, OP_PB, 1);
		if (r != 0)
			return (-1);
		return (1);
	}
	else if (needle >= area->c->data[best_bound(area->c->len)])
	{
		r = stack_do_op(area, OP_PB, 1);
		if (r != 0)
			return (-1);
		r = stack_do_op(area, OP_RB, 1);
		if (r != 0)
			return (-1);
		return (1);
	}
	else
		r = stack_do_op(area, OP_RA, 1);
	return (r);
}

size_t	move_chunks(t_swapable *area, size_t diff, ssize_t end, int bound)
{
	int		needle;
	ssize_t	result;

	while (diff > 0)
	{
		needle = area->a->data[area->a->len - 1];
		if (stack_find_index(area->c, needle) == -1)
		{
			stack_do_op(area, OP_RA, 1);
			continue ;
		}
		result = move_chunk(area, end, needle);
		if (result == -1)
			return (-1);
		if (result == 1)
			diff--;
		if (area->b->len >= (size_t)bound)
		{
			end = ft_max(0, end - best_bound(area->c->len));
			bound = ft_min(area->c->len - 1, bound + best_bound(area->c->len));
		}
	}
	return (0);
}

ssize_t	push_unsorted_chunks(t_swapable *area)
{
	t_stack	*lis;
	size_t	diff;
	ssize_t	end;
	int		bound;

	lis = create_lis_stack(area->a);
	area->c = add_none_lis_sorted(lis, area->a);
	if (area->c == NULL)
		return (stack_free(lis), -1);
	bound = best_bound(area->c->len);
	end = area->c->len - bound;
	diff = area->a->len - lis->len;
	move_chunks(area, diff, end, bound);
	return (stack_free(lis), stack_free(area->c), 0);
}
