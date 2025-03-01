/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

ssize_t	is_sorted(t_stack *s)
{
	size_t	start;

	start = s->len - 1;
	while (start >= 1)
	{
		if (s->data[start] > s->data[start - 1])
			return (-1);
		start--;
	}
	return (0);
}

void	bubble_sort(t_swapable *area)
{
	ssize_t	i;
	int		is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = area->a->len - 1;
		while (i >= 1)
		{
			if (area->a->data[i] > area->a->data[i - 1])
			{
				swap_ints(area->a->data + i, area->a->data + (i - 1));
				is_sorted = 0;
			}
			i--;
		}
	}
}

ssize_t	move_unsorted(t_swapable *area)
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
		if (lis_has(lis, area->a->data[area->a->len - 1]) == -1)
		{
			stack_do_op(area, OP_PB);
			diff--;
		}
		else
			stack_do_op(area, OP_RA);
	}
	return (stack_free(lis), 0);
}

ssize_t	sort(t_swapable *area)
{
	stack_print(area->a, "A");
	stack_print(area->b, "B");
	if (area->a->len <= 1 || is_sorted(area->a) == 0)
		return (0);
	if (move_unsorted(area) != 0)
		return (-1);
	stack_print(area->a, "A");
	stack_print(area->b, "B");
	debug_msg("Ops done = %d\n", area->ops_done);
	return (0);
}
