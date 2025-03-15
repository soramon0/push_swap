/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

ssize_t	find_insert_pos_rev(t_stack *pivot, t_stack *haystack, int needle)
{
	ssize_t	index;
	ssize_t	needle_index;
	int		target;

	if (stack_push(pivot, needle) != 0)
		return (-1);
	bubble_sort_rev(pivot);
	index = stack_find_index(pivot, needle);
	needle_index = index;
	if (index == (ssize_t)pivot->len - 1)
		index = 0;
	else
		index++;
	target = pivot->data[index];
	index = stack_find_index(haystack, target);
	if (index == -1)
		return (-1);
	pivot->data[needle_index] = pivot->data[--pivot->len];
	return (index);
}

ssize_t	push_unsorted(t_swapable *area)
{
	t_stack	*lis;
	size_t	diff;

	lis = create_lis_stack(area->a);
	stack_print(lis, "LIS");
	if (lis == NULL)
		return (-1);
	diff = area->a->len - lis->len;
	while (diff > 0)
	{
		if (stack_find_index(lis, area->a->data[area->a->len - 1]) == -1)
		{
			stack_do_op(area, OP_PB, 1);
			diff--;
		}
		else if (stack_find_index(lis, area->a->data[0]) == -1)
		{
			stack_do_op(area, OP_RRA, 1);
			stack_do_op(area, OP_PB, 1);
			diff--;
		}
		else
			stack_do_op(area, OP_RA, 1);
	}
	return (stack_free(lis), 0);
}

ssize_t	push_top(t_swapable *area)
{
	int			sm;
	size_t		index;
	t_stack_op	op;

	sm = stack_min_max(area->a, 0);
	index = stack_find_index(area->a, sm);
	if (index >= (area->a->len) / 2)
	{
		index = area->a->len - 1 - index;
		op = OP_RA;
	}
	else
	{
		++index;
		op = OP_RRA;
	}
	while (index > 0)
	{
		if (stack_do_op(area, op, 1) != 0)
			return (-1);
		index--;
	}
	return (0);
}
