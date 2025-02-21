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

ssize_t	sort(t_swapable *area)
{
	stack_print(area->a);
	stack_print(area->b);
	if (is_sorted(area->a) == 0)
		return (0);
	stack_do_op(area, OP_RRA);
	stack_do_op(area, OP_PB);
	stack_do_op(area, OP_SA);
	stack_do_op(area, OP_RRA);
	stack_do_op(area, OP_PA);
	stack_print(area->a);
	stack_print(area->b);
	return (0);
}
