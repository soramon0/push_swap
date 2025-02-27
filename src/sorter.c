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

int	find_lis(t_stack *s, int num)
{
	size_t	i;
	int		found;

	i = 0;
	found = 0;
	while (i < s->len)
	{
		if (s->data[i] == num)
		{
			found = 1;
			break ;
		}
		i++;
	}
	return (found);
}

ssize_t	sort(t_swapable *area)
{
	t_stack	*lis;
	size_t	diff;

	stack_print(area->a);
	stack_print(area->b);
	if (area->a->len <= 1 || is_sorted(area->a) == 0)
		return (0);
	lis = create_lis_stack(area->a);
	stack_print(lis);
	diff = area->a->len - lis->len;
	while (diff > 0)
	{
		if (find_lis(lis, area->a->data[area->a->len - 1]) == 0)
		{
			stack_do_op(area, OP_PB);
			diff--;
		}
		stack_do_op(area, OP_RA);
	}
	bubble_sort(area);
	stack_print(area->a);
	stack_print(area->b);
	debug_msg("Ops done = %d\n", area->ops_done);
	return (0);
}
